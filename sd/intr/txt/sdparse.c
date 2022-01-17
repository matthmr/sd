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

#define H_RESET_TEXIT H_RESET(t);\
                      H_RESET(exit_status)

static uint t;
uint offset;

uint litsize_offset (uint* i, char* data) {
	uint offset = *i;

	char c = data[offset];

	while ( NUMBER (c)) {
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
				Keyword_manifest_len - 1: 0;
			t_end = (direction == down_up)?
				0: Keyword_manifest_len - 1;

			/// looks for out-of-bound chars
			if (
			     (direction == up_down && c < *(Keyword_manifest[t_start])) ||
			     (direction == down_up && c > *(Keyword_manifest[t_start]))
			   )
				goto s_not_found;

			r_repeats: {

			_t_end = t_end;

			for (t = t_start; s_comp (t, t_end); s_advance (t)) {

				if (!rep_lock) {
					/// TODO: if the list of builtin objects gets bigger,
					///       make this faster by comparing it against
					///       character boundary
					if (c == Keyword_manifest[t][offset]) {
						H_LOCK (rep_lock);
						_t_end = _t = t;
					}
				}
				else { /// on lock
					if (c == Keyword_manifest[t][offset])
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

			for (t = 0; t < Token_manifest_len; t++)
				if (c == Token_manifest[t])
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

void parser_stream (char** data) {

	char c;

	bool exit_status;
	bool trailing = true;

	uint lnsize = strlen (*data);

	for (uint i = 0; (*data)[i] != '\0'; i++) {
		c = (*data)[i];

		if (trailing && (c == 0x20 || c == 0x0a || c == 0x09)) { /// trailing whitespace
			offset++;
			continue;
		}
		else if (trailing)
			H_RESET (trailing);

		if (exit_status == repeats && c == '\n' ||
		   !exit_status && c == '\n') /// equivalent to `not_found`
			goto case_not_found;

		exit_status = nfind_def (&i, c);

		switch (exit_status) {

			case repeats:
				offset++;
				break;

			case not_found:
			case_not_found: {
				printf ("[ DEBUG#TAKEOUT: not_found ]\n");
				H_LOCK (trailing);
				H_RESET_TEXIT;
				/// TODO: HERE: make the `uobj` table
				// getuname (/* TODO, */ &i, *data, lnsize, DELIMITER);
				continue;
			} break;

			/**
			 * it might be the case that a string is consired equal
			 * to a keyword if the conditions are right. in that
			 * case, we implement the same table as `getuname`
			 */
			case found:
			case_found: {

				printf ("[ DEBUG#TAKEOUT: found ]\n");

				offset = i;

				uint kw_len = strlen (Keyword_manifest[t]);
				char* name = malloc (kw_len);

				getname (&name, &i, *data, lnsize, DELIMITER);

				_bool _isKw = (_bool) strcmp (name, Keyword_manifest[t]);

				H_RESET_TEXIT;
				H_LOCK (trailing);

				if (! _isKw) {
					/// TODO: handle keyword as an object reference
				}
				else {
					/// TODO: handle name with the default name handler
				}

			} break;

			case token: /// handle token
				printf ("[ DEBUG#TAKEOUT: token ]\n");
				H_LOCK (trailing);
				H_RESET_TEXIT;
				offset++;
				continue;
				break;

			case literal: /// handle literal
				printf ("[ DEBUG#TAKEOUT: literal ]\n");

				H_LOCK (trailing);
				H_RESET_TEXIT;

				/// TODO: resolute literal data
				uint i_start = i;
				offset = litsize_offset (&i, *data);

				continue;
				break;
		}

	}

	RESET (offset);

}

/* This wraps around `parser_stream` to use `fgets`*/
void parse_src (FILE* file, char* data, const uint LINE_LIMIT) {

	Set (txtruntime);

	Obj root = {
		.data = NULL,
		.parent = NULL,
		.children = NULL,
		.childrenno = 0
	};

	root.parent = &root;

	while (fgets (data, LINE_LIMIT, file) != NULL)
		parser_stream (&data);
}
