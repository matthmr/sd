/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * sd source code.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/types/shared.h"
#include "../../utils/utils.h"
#include "../../utils/err/err.h"

#include "../../lang/tokens.h"
#include "../../lang/langutils.h"
#include "../../lang/bytecode/bytecode_tokens.h"

#include "utils/txtutils.h"

#include "sdparse.h"

static uint t;
static uint t_start, t_end;

bool t_find_def (char c) {

	bool exit_status;
	bool rep_lock = false; /// masks `r_repeats` to directly resolute `t_end`

	uint _t = 0;
	uint _t_end = 0;
	
	if (!direction) {

		if (UPPER_ALPHA (c)) { /// all default keywords are lowcase
			return not_found;
		}

		if (LOWER_ALPHA (c)) { /// might also be a number OR a token

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
				return not_found;

			r_repeats: {

			_t_end = t_end;

			for (t = t_start; s_comp (t, t_end); s_advance (t)) {

				if (!rep_lock) {
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

		else { /// resolute number or token

			if (c == '\n') /// whitespace
				return not_found;

			if (NUMBER (c))
					return number;

			for (t = 0; t < Token_manifest_len; t++)
				if (c == Token_manifest[t])
					return token;

			return not_found;

		}
	}

	else /// resolute `repeats`
		goto r_repeats;

	s_not_found: {
		H_RESET (direction);
		H_RESET (offset);

		H_RESET (t);

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

void StreamParser (char** data) {

	char c;
	bool exit_status;
	bool trailing = true;

	for (uint i = 0; (*data)[i] != '\0'; i++) {
		c = (*data)[i];

		if (trailing && (c == '\x20' || c == '\x0a')) /// trailing whitespace
			continue;
		else if (trailing)
			H_RESET (trailing);

		if (exit_status == repeats && c == '\n' ||
			  !exit_status && c == '\n') /// equivalent to `not_found`
			goto _not_found;

		exit_status = t_find_def (c);

		switch (exit_status) {
			case repeats:
				break;

			case not_found: _not_found: { /// handle unknown token
				printf ("[ DEBUG#TAKEOUT: not_found ]\n");
				return;
			} break;
			case found: /// handle known token
				printf ("[ DEBUG#TAKEOUT: found ]\n");
				return;
				break;

			case token: /// handle token
				printf ("[ DEBUG#TAKEOUT: token ]\n");
				return;
				break;
			case number: /// handle number
				printf ("[ DEBUG#TAKEOUT: number ]\n");
				return;
				break;
		}

	}

}

/* This wraps around `StreamParser` to use `fgets`*/
void StartParse (FILE* file, char* data, const uint LINE_LIMIT, int argc, char** argv) {

	line: {
		if (fgets (data, LINE_LIMIT, file) == NULL)
			goto start_parse_done;

		StreamParser (&data);

		goto line;
	}

	start_parse_done: return;

}

