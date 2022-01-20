/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * sd source code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

#include <sd/lang/langutils.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/tokens.h>
#include <sd/lang/lang.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/intr/txt/sdparse.h>

#define _continue H_RESET (exit_status); continue

static uint t;
uint g_offset;

Kwty get_kwty (uint kw) {
	return 0;
}

uint litsize_offset (uint* i, char* data) {
	uint offset = *i;

	char c = data[offset];

	while ( NUMBER (c) ) {
		offset++;
		c = data[offset];
	}

	return (*i = (offset - 1));
}

bool nfind_def (uint* i, char c) {

	bool exit_status;
	bool rep_lock = false; /// masks `r_repeats` to directly resolute `t_end`

	uint _t = 0;
	uint _t_end = 0;

	static uint t_start;
	static uint t_end;

	static uint offset;
	
	if (!direction) {

		if (UPPER_ALPHA (c)) { /// all default keywords are lowcase
			return not_found;
		}

		if (LOWER_ALPHA (c)) { /// might also be a literal OR a token

			direction = (c > 'm')? down_up: up_down;

			t_start = (direction == down_up)?
				keyword_manifest_len - 1: 0;
			t_end = (direction == down_up)?
				0: keyword_manifest_len - 1;

			/// looks for out-of-bound chars
			if (
			     (direction == up_down && c < *(keyword_manifest[t_start].kw)) ||
			     (direction == down_up && c > *(keyword_manifest[t_start].kw))
			   )
				goto s_not_found;

			r_repeats: {

			_t_end = t_end;

			for (t = t_start; s_comp (t, t_end); s_advance (t)) {

				if (!rep_lock) {
					/// TODO: if the list of builtin objects gets bigger,
					///       make this faster by comparing it against
					///       character boundary
					if (c == keyword_manifest[t].kw[offset]) {
						H_LOCK (rep_lock);
						_t_end = _t = t;
					}
				}
				else { /// on lock
					if (c == keyword_manifest[t].kw[offset])
						s_advance (_t_end); /* shrink search time by shriking `t_end`:
						                       when this expression is false, `t_end`
						                       becomes a new upper bound */
					else if (_t_end != _t)
						goto s_repeats;
					else
						goto s_found;
				}
			}
				/// fall-through
				if (! rep_lock)
					goto s_not_found;
				else if (_t_end - _t > 0)
					goto s_repeats;
				else
					goto s_found;
			}
		}

		else { /// resolute literal or token

			if (c == '\n') /// whitespace
				goto s_not_found;

			if (NUMBER (c))
					return literal;

			for (t = 0; t < token_manifest_len; t++)
				if (c == token_manifest[t].t)
					return token;

			goto s_not_found;

		}
	}

	else /// resolute `repeats`
		goto r_repeats;

	s_not_found: {
		H_RESET (direction);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		return not_found;
	}

	s_found: {
		t = _t;

		H_RESET (direction);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		i += offset;

		return found;
	}

	s_repeats: {
		/* bound `t` between the first matching and the last matching token */
		t_start = _t;
		t_end = _t_end;

		offset++;
		return repeats;
	}

}

void parser_stream (char** data, Obj* root) {

	char c;

	bool exit_status;
	bool trailing = true;

	uint lnsize = strlen (*data);
	Obj* c_obj = root;
	Obj* c_objpr = root->pr;

	for (uint i = 0; (*data)[i] != '\0'; i++) {
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

		exit_status = nfind_def (&i, c);

		if (exit_status != repeats)
			LOCK (trailing);
		else {
			g_offset++;
			continue;
		}

		switch (exit_status) {

		case not_found:
		case_not_found: {
			puts ("[ DEBUG#TAKEOUT: not_found ]\n");
			/// TODO: HERE: make the `uobj` table
			// getuname (/* TODO, */ &i, *data, lnsize, DELIMITER);
			_continue;
		} break;

		/**
		 * it might be the case that a string is consired equal
		 * to a keyword if the conditions are right. in that
		 * case, we implement the same table as `getuname`
		 */
		case found:
		case_found: {

			puts ("[ DEBUG#TAKEOUT: found ]\n");

			uint _i = g_offset = i;
			getinptr (&i, *data, lnsize, DELIMITER);

			if (g_offset == i) {
				_continue;
			}

			char* name = calloc ((g_offset-_i), 1);
			strncpy (name, *data+_i, g_offset-_i);

			_bool notKw = (_bool)
				strcmp (name, keyword_manifest[t].kw);

			if (! notKw /* if keyword */)
				; // kw_handle (&keyword_manifest[t]);
			else {
				/// TODO: handle name with the default name handler
				// u_handle (name, ...);
			}

			free (name);

		} break;

		case token: /// handle token
			puts ("[ DEBUG#TAKEOUT: token ]\n");
			g_offset++;
			_continue;
			break;

		case literal: /// handle literal

			puts ("[ DEBUG#TAKEOUT: literal ]\n");

			/// TODO: resolute literal data
			uint i_start = i;
			g_offset = litsize_offset (&i, *data);

			_continue;
			break;
		}

	}

	RESET (g_offset);

}

/* this wraps around `parser_stream` to use `fgets`
 * and define module roots */
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	Set (txtruntime);

	Obj root = {
		.cdno = 0,
		.ref = NULL,
		.pr = NULL,
		.cd = NULL
	};

	/* the way we know if we hit root
	 * is to see if the parent `pr`
	 * of `obj` is itself*/
	root.pr = &root;

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (&data, &root);
}
