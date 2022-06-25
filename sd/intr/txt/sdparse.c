/**
 * @file sdparse.c
 *
 * @brief `sdread`'s plain-text source code backend
 *
 * This file contains entry logic needed
 * for parsing and executing plain-text
 * SD source code.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/macros.h>

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/tokens/groups.h>
#include <sd/lang/uword/umaps.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/obj/ot.h>
#include <sd/lang/vm/vm.h>

#define LOCK_READ
#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>
#include <sd/intr/exec/sdread.h>
#include <sd/intr/limits.h>

uint e_eof; ///< counter: counts how many characters until `EOF` OR until the end of the file buffer
uint ln = 1; ///< indexer: indexes the current line
uint wstart_i = 0; ///< indexer: indexes the start of a *probable* word
uint wsize = 0; ///< counter: counts the size of a word that is in the @p word buffer
uint t; ///< indexer: indexes the current element in one of manifests; defined in `txtutils`

char gbuffer[STDBUFFER]; ///< buffer: as in "Global BUFFER"; main text buffer for sdparse
char uword[STDUWORD]; ///< buffer: as in "User WORD"; main user word (variable name) buffer for sdparse, lengthed by @p STDUWORD
char word[STDWORD]; ///< buffer: main word buffer, lengthed by @p STDWORD

static uint gbuffer_size = BUFFER; ///< @p gbuffer size, mostly constant
static char* ins_p = gbuffer;

/// @brief advances the current buffer index to the next word
///
/// Hooks with whichever action is most feasible. Some hardcoded syntax
/// errors such the 64 character name rule are caught by this function.
///
/// It hooks first `e`-wise then context-wise.
///
/// @param data current buffer
/// @param i points to current buffer index
/// @param wstart_i points to the start of a word in the current buffer
/// @param e points to the current exit status of nfind_def
/// @param lnsize same as e_eof
void next (char* data, uint* i, uint* wstart_i, bool* e, const uint lnsize) {

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

		// it might be the case that a token cuts a repetition keyword short
		if (tfind_def (*(data+*i)) == ttoken) { // faux

			wsize = (*i - *wstart_i)+1;
			strncpy (gbuffer, (data + *wstart_i), wsize);
			*wstart_i = *i+1;

			//au_hook (gbuffer, wsize);

			goto utdiff_token;
		}

		offset_i (i, data, lnsize);
		wsize = (*i - *wstart_i)+1;

		if (wsize > STDWORD) { // mismatch(1)

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

		uint tcp = t;
		H_RESET (t);
		return at_hook (token_manifest[tcp]);

	} break;

	case number:
		number_offset (i, data);
		wsize = (*i - *wstart_i)+1;

		if (wsize > STDWORD)
			;

		strncpy (word, (data + *wstart_i), wsize);

		*wstart_i = *i+1;
		H_RESET (t);

		return aint_hook (word, wsize);

		break;
	}

	H_RESET (*e);
	return;
}

/// @brief main parser function for receiving direct buffer content
///
/// This function deals with stream promises and hooks. For example,
/// a open # means the stream up to a newline is ignored.
/// It also uses @p nfind_def to differentiate between
///   - words
///   - uwords
///   - literal
///   - comments
///   - tokens
///
/// local variables:
///   - `leading`: lock: the leading content before a gword (mostly whitespace)
///
/// @param data the main buffer
/// @param e_eof the buffer length
void parser_stream (char* data, uint e_eof) {

	uint i = 0;

	char c;

	bool e_status = false;
	bool leading = true;

	const uint lnsize = (const uint) e_eof;

	// main parsing loop
	for (i = 0; i < lnsize; i++) {

		// main stream locker
		if (lock_stream) {

			if (gs_ctxt.cmt) {
				rstream (H_RESET (gs_ctxt.cmt));
				break; // FIXME: it should't break, it should seek for a newline
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

		if (c == '\n' && (e_status == repeats || !e_status))
			goto parser_not_found;

		e_status = nfind_def (c);

		if (e_status != repeats)
			H_LOCK (leading);
		else
			continue;

		next (data, &i, &wstart_i, &e_status, lnsize);

		if (0) parser_not_found: { // TODO: this doesn't fit in with my callback schema
			offset_i (&i, data, lnsize);
			wsize = (i - wstart_i)+1;
			strncpy (uword, (data + wstart_i), wsize);

			//au_hook (gbuffer, wsize);
			H_RESET (t);
		}

	}

}

/// @brief the main `sdparse` **exposed** interface
///
/// This is called by `sdread`.
/// This wraps around @ref parser_stream(char*,uint) to buffer
/// to `data` and define module roots.
///
/// @param file the file descriptor to be read
/// @param _data the buffer to buff the file to
/// @param buffer_size the buffer size
void parse_src (FILE* file, char* _data, const uint buffer_size) {

	// vm callback handle
	if (1)
		;//
	else // if not on callback, act as if being called for the first time
		ln = 1;

	do {
		e_eof = fread (_data, 1, buffer_size, file);
		parser_stream (_data, e_eof);
	} while (e_eof == buffer_size);

}
