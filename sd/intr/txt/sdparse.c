/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * sd source code.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/tokens/user/umaps.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/tree/ot.h>
#include <sd/lang/lang.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/tree/ptree.h>
#include <sd/intr/utils/literal.h>
#include <sd/intr/txt/sdparse.h>

uint t;

uint litsize_offset (uint* i, char* data) {
	uint offset = *i;

	char c = data[offset];

	while ( NUMBER (c) ) {
		offset++;
		c = data[offset];
	}

	/* this is called as soon as `c`
	 * is a literal, meaning `i`
	 * is at least itself */
	return (*i = (offset - 1));
}

void next (char* data,
           uint* i,
           uint* wstart_i,
           bool* e,
           const uint lnsize) {

	char* word;

	switch (*e) {

	case not_found:
		H_RESET (t);

		offset_i (i, data, lnsize);

		word = calloc ((*i - *wstart_i)+2, sizeof (char));
		strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);

		*wstart_i = *i+1;

		au_hook (word);
		free (word);

		return;
		break;

	case found:

		/* it might be the case that a token cuts a repetition keyword short */
		if (tfind_def (*(data+*i)) == ttoken) {
			word = calloc ((*i - *wstart_i)+2, sizeof (char));
			strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);
			*wstart_i = *i+1;

			au_hook (word);
			free (word);
			goto utdiff_token;
		}

		offset_i (i, data, lnsize);

		word = calloc ((*i - *wstart_i)+2, sizeof (char));
		strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);

		*wstart_i = *i+1;

		if (! (uint) strcmp (word, keyword_manifest[t].kw))
			akw_hook (keyword_manifest[t]);
		else
			au_hook (word);

		free (word);
		H_RESET (t);
		break;

	case ttoken: /// handle token
	utdiff_token: {
		++*wstart_i;

		at_hook (token_manifest[t]);

		H_RESET (t);
		return;
	} break;

	case literal: /// handle literal

		*i = litsize_offset (i, data);
		*wstart_i = *i+1;

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
	char* literal_string;

	Obj c_obj;

	// Expr e;
	// expr_reset (&e);

	bool e_status = (bool) 0;
	bool trailing = true;

	const uint lnsize = strlen (data);

	for (i = 0; data[i] != '\0'; i++) {

		if (lock_stream)

			if (gs_ctxt.cmt) { // after `"` is tokenized
				rstream (H_RESET (gs_ctxt.cmt));
				break;
			}

			else if (gs_ctxt.str) {

				char* closing_quote;

				if ((closing_quote = strchr (data+i, '"')) != NULL) {
					rstream (H_RESET (gs_ctxt.str));

					i = (uint) (closing_quote - data);
					cat (closing_quote, literal_string);

					// assign_bytes (literal_string, &c_obj);

					free (literal_string);

					continue;
				}
				else {
					cat (literal_string, data+i);
					break;
				}
			}

		c = data[i];

		if (trailing && WHITESPACE (c)) {
			wstart_i++;
			continue;
		}
		else if (trailing)
			H_RESET (trailing);

		if (e_status == repeats && c == '\n' ||
		   !e_status && c == '\n') /// unfinished word == `not_found`
			goto parser_not_found;

		e_status = nfind_def (c);

		if (e_status != repeats)
			H_LOCK (trailing);
		else
			continue;

		next (data, &i, &wstart_i, &e_status, lnsize);

		if (0) parser_not_found: {

			char* word;
			offset_i (&i, data, lnsize);

			word = calloc ((i - wstart_i)+2, sizeof (char));
			strncpy (word, (data + wstart_i), (i - wstart_i)+1);

			au_hook (word);
			H_RESET (t);
		}

	}

	/// TODO: THIS IS VERY IMPORTANT
	/// newline (g_ctxt, gr_ctxt);

}

/* this wraps around `parser_stream` to use `fgets`
 * and define module roots */
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	e_set (txtruntime);

	Obj l_root;

	l_root.pr = NULL;

	mkchild (&g_root, l_root);

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (data, &l_root);

}
