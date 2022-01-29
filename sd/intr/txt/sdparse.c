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

#include <sd/lang/utils/langutils.h>
#include <sd/lang/hooks/txthooks.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/lang.h>

#include <sd/intr/txt/utils/txtutils.h>
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
	uint _i;

	switch (*e) {

	case not_found:
		H_RESET (t);
		puts ("!! not_found");

		_i = *i;
		offset_i (i, data, lnsize);

		word = calloc ((*i - *wstart_i)+2, sizeof (char));
		strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);

		*wstart_i = *i+1;

		// au_hook (word)
		free (word);

		return;
		break;

	case found:

		if (tfind_def (*(data+*i)) == ttoken) { /* it might be the case that
		                                           a token cuts a repetition
		                                           keyword short */
			word = calloc ((*i - *wstart_i)+2, sizeof (char));
			strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);
			*wstart_i = *i+1;

			// au_hook (word)
			free (word);
			goto utdiff_token;
		}

		puts (":: found");

		_i = *i;
		offset_i (i, data, lnsize);

		word = calloc ((*i - *wstart_i)+2, sizeof (char));
		strncpy (word, (data + *wstart_i), (*i - *wstart_i)+1);

		*wstart_i = *i+1;

		/* this is done because it might be
			 the case that this word is equal
			 to a keyword only up to diffing */
		uint notKw = (uint) strcmp (word, keyword_manifest[t].kw);

		if (! notKw)
			;
			// akw_hook (keyword_manifest[t]);
		else
			;
			// au_hook (name);

		free (word);
		H_RESET (t);
		break;

	case ttoken: /// handle token
	utdiff_token: {
		puts ("~~ token");
		++*wstart_i;

		at_hook (token_manifest[t]);

		H_RESET (t);
		return;
	} break;

	case literal: /// handle literal
		puts (".. literal");

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

	bool e_status = (bool) 0;
	bool trailing = true;

	const uint lnsize = strlen (data);
	Obj* c_obj = root;

	for (i = 0; data[i] != '\0'; i++) {

		if (lock_stream) {
			if (g_ctxt.cmt) {
				rstream (H_RESET (g_ctxt.cmt));
				break;
			}
			else if (g_ctxt.str) {
				char* cstr;
				if ((cstr = strchr (data+i, '"')) != NULL) {
					i = (uint) (cstr - data);
					// g_ctxt.found->str (root);
					rstream (H_RESET (g_ctxt.str));
					continue;
				} else break;
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
		   !e_status && c == '\n') /// unfinished word = `not_found`
			goto parser_not_found;

		e_status = nfind_def (c);

		if (e_status != repeats)
			H_LOCK (trailing);
		else
			continue;

		next (data, &i, &wstart_i, &e_status, lnsize);

		if (0) parser_not_found: {
			puts ("!! not_found");
			// au_hook (name);
			H_RESET (t);
		}

	}

	/// TODO: THIS IS VERY IMPORTANT
	/// callback (void);

}

/* this wraps around `parser_stream` to use `fgets`
 * and define module roots */
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	e_set (txtruntime);

	Obj* root = mod_root.pr = &mod_root;

	/* the way we know if we hit root
	 * is to see if the parent `pr`
	 * of the object `obj` is itself*/
	root->pr = &mod_root;

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (data, root);

}
