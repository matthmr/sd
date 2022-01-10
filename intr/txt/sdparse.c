/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * sd source code.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/sharedtypes.h"
#include "../../utils/utils.h"

#include "../../lang/tokens.h"
#include "../../lang/langutils.h"
#include "../../lang/bytecode/bytecode_tokens.h"

#include "utils/txtutils.h"

#include "sdparse.h"

static uint t;
static uint t_start, t_end;

bool t_find_def (char c) {

	bool exit_status;
	bool rep_mask = false; /// mask `r_repeats` to directly resolute `t_end`

	uint match_T = 0; /// one up from the real index `t`
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

			/// OUT
			printf ("[global] direction: %d\n", direction);
			printf ("[global] c: %c\n", c);

			if (
			     (direction == up_down && c < *(Keyword_manifest[t_start])) || /// might not EVER be the case, but just to be sure ...
			     (direction == down_up && c > *(Keyword_manifest[t_start]))
			   )
				return not_found;

			r_repeats: {

			/// OUT
			printf ("[r_repeats] t_start: %d\n", t_start);
			printf ("[r_repeats] t_end: %d\n", t_end);
			printf ("[r_repeats] match_T: %d\n", match_T);
			printf ("[r_repeats] offset: %d\n", offset);

			_t_end = t_end;

			for (t = t_start; s_comp (t, t_end); s_advance (t)) {
				/// OUT
				printf ("[for@r_repeats] t: %d\n", t);
				printf ("[for@r_repeats] match_T: %d\n", match_T);

				if (c == Keyword_manifest[t][offset] && !rep_mask) {
					if (!match_T) {
						/// OUT
						printf ("[!match_T@for@r_repeats]: hit\n");

						H_LOCK (rep_mask);
						_t_end = match_T = t+1;
					}
					else {
						_t_end++;

						/// OUT
						printf ("[else !match_T@for@r_repeats] _t_end: %d\n", _t_end);
					}
				}
				else if (match_T && !rep_mask) { /// stop: unique
					/// OUT
					printf ("[match_T AND !rep_mask]: hit\n");

					goto s_found;
				}
				else if (match_T && rep_mask) /// stop: repeats
					/// OUT
					printf ("[match_T AND rep_mask] hit\n");

					if (match_T == _t_end)
						goto s_found;
					else
						goto s_repeats;
			}

			if (match_T && !rep_mask) /// fall-through: repeats
				goto s_found;
			else if (match_T && rep_mask) /// fall-through: unique
				goto s_repeats;
			}
		}

		else {

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

	s_found: {
		

		/// OUT
		printf ("[s_found] hit\n");

		t = match_T-1;

		H_RESET (direction);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		return found;
	}

	s_repeats: {
		/// OUT
		printf ("[s_repeats] hit\n");

		t_end = _t_end;
		offset++;
		return repeats;
	}
}

void StreamParser (char** data) {

	char c;
	bool exit_status;

	/// loop until a manifest type is found
	for (uint i = 0; (*data)[i] != '\0'; i++) {
		c = (*data)[i];

		exit_status = t_find_def (c);

		switch (exit_status) {
			case repeats:
				break;

			case not_found: /// handle unknown token
				printf ("[ DEBUG#TAKEOUT: not_found ]\n");
				exit (0);
				break;
			case found: /// handle known token
				printf ("[ DEBUG#TAKEOUT: found ]\n");
				exit (0);
				break;

			case token: /// handle token
				printf ("[ DEBUG#TAKEOUT: token ]\n");
				exit (0);
				break;
			case number: /// handle number
				printf ("[ DEBUG#TAKEOUT: number ]\n");
				exit (0);
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

