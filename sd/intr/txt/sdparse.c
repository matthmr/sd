/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * SD source code.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/verr.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/tokens/user/umaps.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/tree/ot.h>
#include <sd/lang/vm/vm.h>
#include <sd/lang/lang.h>

#define LOCK_READ
#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>
#include <sd/intr/exec/sdread.h>
#include <sd/intr/limits.h>

uint ln = 1;
uint wstart_i = 0;
uint wsize = 0;
uint t;

char gbuffer[STDBUFFER];
char uword[STDUWORD];
char word[STDWORD];

static uint gbuffer_size = BUFFER;
static char* ins_p = gbuffer;

void next (char* data,
           uint* i,
           uint* wstart_i,
           bool* e,
           const uint lnsize) {

	switch (*e) {

	case not_found:
		H_RESET (t);

		offset_i (i, data, lnsize);
		wsize = (*i - *wstart_i)+1;

		if (wsize > STDUWORD) {
			NO_INFO_ERR (0x06, vErr_verbose (data, ln, *wstart_i, wsize));
		}

		strncpy (uword, (data + *wstart_i), wsize);

		*wstart_i = *i+1;

		//au_hook (uword, wsize);

		return;
		break;

	case found:

		/// it might be the case that a token cuts a repetition keyword short
		if (tfind_def (*(data+*i)) == ttoken) {

			wsize = (*i - *wstart_i)+1;
			strncpy (gbuffer, (data + *wstart_i), wsize);
			*wstart_i = *i+1;

			//au_hook (gbuffer, wsize);

			goto utdiff_token;
		}

		offset_i (i, data, lnsize);
		wsize = (*i - *wstart_i)+1;

		if (wsize > STDWORD) { /// mismatch(1)

			strncpy (uword, (data + *wstart_i), wsize);
			goto _au_hook;

			H_RESET (t);
			*wstart_i = *i+1;
			break;
		}
		else {
			strncpy (word, (data + *wstart_i), wsize);

			if (! (uint) strcmp (word, keyword_manifest[t].kw))
				akw_hook (keyword_manifest[t]);
			else _au_hook: // mismatch(2)
				;//au_hook (word, wsize);
		}

		*wstart_i = *i+1;
		H_RESET (t);
		break;

	case ttoken:
	utdiff_token: {
		++*wstart_i;

		at_hook (token_manifest[t]);

		H_RESET (t);
		return;
	} break;

	case number:
		number_offset (i, data);
		wsize = (*i - *wstart_i)+1;

		if (wsize > STDWORD)
			;

		strncpy (word, (data + *wstart_i), wsize);

		*wstart_i = *i+1;
		aint_hook (word, wsize);

		H_RESET (t);
		return;
		break;
	}

	H_RESET (*e);
	return;
}

void parser_stream (char* data, Obj* m_root, uint e_eof) {

	uint i = 0;

	char c;

	bool e_status = false;
	bool leading = true;

	const uint lnsize = (const uint) e_eof;

	for (i = 0; i < lnsize; i++) {

		if (lock_stream)

			if (gs_ctxt.cmt) {
				rstream (H_RESET (gs_ctxt.cmt));
				break;
			}

			else if (gs_ctxt.str) {

				char* closing_quote;

				if ((closing_quote = strchr (data+i, '"')) != NULL) {
					rstream (H_RESET (gs_ctxt.str));

					i = (uint) (closing_quote - data);
					// gbuffer_cat (ins_p, data+i);

					astring_hook (gbuffer /*,size */);

					continue;
				}
				else {
					// gbuffer_cat (ins_p, data+i);
					break;
				}
			}

		c = data[i];

		if (leading && WHITESPACE (c)) {
			if (c == '\n')
				ln++;
			wstart_i++;
			continue;
		}
		else if (leading)
			H_RESET (leading);

		if (e_status == repeats && c == '\n' ||
		   !e_status && c == '\n')
			goto parser_not_found;

		e_status = nfind_def (c);

		if (e_status != repeats)
			H_LOCK (leading);
		else
			continue;

		next (data, &i, &wstart_i, &e_status, lnsize);

		if (0) parser_not_found: {

			offset_i (&i, data, lnsize);
			wsize = (i - wstart_i)+1;
			strncpy (uword, (data + wstart_i), wsize);

			//au_hook (gbuffer, wsize);
			H_RESET (t);
		}

	}

}

/* this wraps around `parser_stream` to buffer
 * to `data` and define module roots
 */
void parse_src (FILE* file, char* _data, const uint buffer_size) {

	uint e_eof;
	e_set (TIME_TXT);

	Obj l_root;
	mkchild (&g_root, &l_root);
	// g_self = CAST_addr l_root;

	ln = 1;

	do {
		e_eof = fread (_data, 1, buffer_size, file);
		parser_stream (_data, &l_root, e_eof);
	} while (e_eof == buffer_size);

}
