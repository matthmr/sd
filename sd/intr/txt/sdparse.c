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

#include <sd/lang/langutils.h>
#include <sd/lang/tokens.h>
#include <sd/lang/hooks.h>
#include <sd/lang/lang.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/sdparse.h>

#define _continue H_RESET (e_status); continue

static uint g_offset;
uint t;

uint litsize_offset (uint* i, char* data) {
	uint offset = *i;

	char c = data[offset];

	while ( NUMBER (c) ) {
		offset++;
		c = data[offset];
	}

	return (*i = (offset - 1));
}

inline void next (char** data,
                  uint* i,
                  uint* wi,
                  uint e,
                  const uint lnsize) {

	switch (e) {

	case not_found:
		H_RESET (t);
		puts ("!! not_found");

		offset_i (i, &g_offset, *data, lnsize, DELIMITER);

		if (g_offset == *i)
			return;

		*wi = g_offset;

		/*
		char* name = calloc ((g_offset-*wi+1), 1);
		strncpy (name, *data+*wi, g_offset-*wi);
		au_hook (name)
		*/

		return;
		break;

	case found:

		if (tfind_def (*(*data+*i)) == ttoken) { /* it might be the case that
		                                       a token cuts a keyword short */
			/*
			char* name = calloc ((g_offset-*wi+1), 1);
			strncpy (name, *data+*wi, g_offset-*wi);
			au_hook (name)
			free (name);
			*/
			goto utdiff_token;
		}

		puts (":: found");
		g_offset = *i;

		/* this is done because it might be
		   the case that this word is equal
		   to a keyword up to diffing */
		offset_i (i, &g_offset, *data, lnsize, DELIMITER);

		if (g_offset == *i)
			return;

		char* name = calloc ((g_offset-*wi+1), 1);
		strncpy (name, *data+*wi, g_offset-*wi);
		uint notKw = (uint) strcmp (name, keyword_manifest[t].kw);

		*wi = g_offset;

		if (! notKw)
			; // akw_hook (keyword_manifest[t]);
		else
			; // au_hook (name);

		free (name);
		H_RESET (t);
		break;

	case ttoken: /// handle token
	utdiff_token: {
		puts ("~~ token");
		g_offset++;
		at_hook (token_manifest[t]);
		H_RESET (t);
		return;
	} break;

	case literal: /// handle literal
		puts (".. literal");

		g_offset = litsize_offset (i, *data);
		*wi = g_offset;

		return;
		break;
	}

	return;
}

void parser_stream (char** data, Obj* root) {

	char c;

	bool e_status;
	bool trailing = true;

	const uint lnsize = strlen (*data);
	Obj* c_obj = root;
	uint wi = 0;

	for (uint i = 0; (*data)[i] != '\0'; i++) {

		/* locks the parser stream for:
		 *   * comment line
		 *   * comment block
		 *   * literals (mainly strings)
		 */
		if (lock_stream) {

			if (g_ctxt.cmtl || g_ctxt.cmtb) {
				if (s_ignore (&i, lnsize, *data))
					break;
				else if (ct_close (&i, *data))
					continue;
				else break;
			}

			else switch (g_ctxt.str) {
				case DQSTR:
					// ...
					break;
				case SQSTR:
					// ...
					break;
			}

		}

		c = (*data)[i];

		if (trailing && WHITESPACE (c)) {
			g_offset++;
			wi++;
			continue;
		}
		else if (trailing)
			H_RESET (trailing);

		if (e_status == repeats && c == '\n' ||
		   !e_status && c == '\n') /// equivalent to `not_found`
			goto parser_not_found;

		e_status = nfind_def (c);

		if (e_status != repeats)
			LOCK (trailing);
		else {
			g_offset++;
			wi++;
			continue;
		}

		next (data, &i, &wi, e_status, lnsize);
		_continue;

		parser_not_found: {
			puts ("!! not_found");
			H_RESET (t);
			_continue;
		}

	}

	RESET (g_offset);
	/// TODO:
	/// callback (c);

}

/* this wraps around `parser_stream` to use `fgets`
 * and define module roots */
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	e_set (txtruntime);

	Obj mod_root = {
		.cdno = 0,
		.ref = NULL,
		.pr = NULL,
		.cd = NULL
	};

	Obj* root = mod_root.pr = &mod_root;

	/* the way we know if we hit root
	 * is to see if the parent `pr`
	 * of the object `obj` is itself*/
	root->pr = &mod_root;

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (&data, root);

}
