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

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>
#include <sd/intr/limits.h>

uint t;
uint ln;

uint gbuffer_size = GBUFFER_M1;

char nlft[NEWLINE_BUFFER_LIMIT]; // source buffer
char gbuffer[GBUFFER_M1]; // literal buffer
char word[10]; // keyword assertion buffer

void next (char* data,
           uint* i,
           uint* wstart_i,
           bool* e,
           const uint lnsize) {

	uint wsize;

	switch (*e) {

	case not_found:
		H_RESET (t);

		offset_i (i, data, lnsize);
		wsize = (*i - *wstart_i)+1;
		strncpy (gbuffer, (data + *wstart_i), wsize);

		*wstart_i = *i+1;

		au_hook (gbuffer, wsize);

		return;
		break;

	case found:

		/* it might be the case that a token cuts a repetition keyword short */
		if (tfind_def (*(data+*i)) == ttoken) {

			wsize = (*i - *wstart_i)+1;
			strncpy (gbuffer, (data + *wstart_i), wsize);
			*wstart_i = *i+1;

			au_hook (gbuffer, wsize);

			goto utdiff_token;
		}

		offset_i (i, data, lnsize);
		wsize = (*i - *wstart_i)+1;

		if (wsize > 20) {
			strncpy (gbuffer, (data + *wstart_i), wsize);
			au_hook (gbuffer, wsize);

			H_RESET (t);
			*wstart_i = *i+1;
			break;
		}
		else {
			strncpy (word, (data + *wstart_i), wsize);
		}

		*wstart_i = *i+1;

		if (! (uint) strcmp (word, keyword_manifest[t].kw))
			akw_hook (keyword_manifest[t]);
		else {
			au_hook (word, wsize);
		}

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

void parser_stream (char* data, Obj* root) {

	uint wstart_i = 0;
	uint i = 0;

	char c;

	char* lstring;

	Obj c_obj;

	bool e_status = (bool) 0;
	bool leading = true;

	const uint lnsize = strlen (data);
	ln++;

	for (i = 0; data[i] != '\0'; i++) {

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
					// strcat (lstring, data+i);

					astring_hook (lstring);

					free (lstring);

					continue;
				}
				else {
					// strcat (lstring, data+i);
					break;
				}
			}

		c = data[i];

		if (leading && WHITESPACE (c)) {
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
			uint wsize = (i - wstart_i)+1;
			strncpy (gbuffer, (data + wstart_i), wsize);

			au_hook (gbuffer, wsize);
			H_RESET (t);
		}

	}

	// expr_exec ();

}

/* this wraps around `parser_stream` to use `fgets`
 * and define module roots */
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	e_set (TIME_TXT);

	Obj l_root;
	mkchild (&g_root, &l_root);
	// expr_init ();

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (data, &l_root);

}
