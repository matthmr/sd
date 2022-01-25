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

#define _continue H_RESET (exit_status); continue

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

void parser_stream (char** data, Obj* root) {

	char c;

	bool exit_status;
	bool trailing = true;

	uint wi = 0;
	uint lnsize = strlen (*data);
	Obj* c_obj = root;

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
					if (strchr (*data+i, '"') != NULL);
					break;
				case SQSTR:
					if (strchr (*data+i, '\'') != NULL);
					break;
			}

		}

		c = (*data)[i];

		if (trailing && WHITESPACE (c)) {
			g_offset++;
			continue;
		}
		else if (trailing)
			H_RESET (trailing);

		if (exit_status == repeats && c == '\n' ||
		   !exit_status && c == '\n') /// equivalent to `not_found`
			goto case_not_found;

		exit_status = nfind_def (c);

		if (exit_status != repeats)
			LOCK (trailing);
		else {
			g_offset++;
			continue;
		}

		switch (exit_status) {

		case not_found:
		case_not_found: {
			puts ("!! not_found");
			_continue;
		} break;

		case found:
		case_found: {

			puts (":: found");

			g_offset = i;

			/* this is done because it might be
			   the case that this word is equal
			   to a keyword up to diffing */
			offset_i (&i, &g_offset, *data, lnsize, DELIMITER);

			if (g_offset == i) {
				_continue;
			}

			char* name = calloc ((g_offset-wi), 1);
			strncpy (name, *data+wi, g_offset-wi);
			uint notKw = (uint)
				strcmp (name, keyword_manifest[t].kw);

			/// TODO: properly handle this
			wi = g_offset;

			if (! notKw)
				; // akw_hook (keyword_manifest[t]);
			else
				; // au_hook (name);

			free (name);
			H_RESET (t);

		} break;

		case ttoken: /// handle token
			puts ("~~ token");
			g_offset++;
			at_hook (token_manifest[t]);
			H_RESET (t);
			_continue;
			break;

		case literal: /// handle literal

			puts (".. literal");

			/// TODO: resolute literal data
			uint i_start = i;
			g_offset = litsize_offset (&i, *data);

			_continue;
			break;
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
