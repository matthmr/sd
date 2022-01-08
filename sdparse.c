/**
 * This file contains all logic needed
 * for parsing and executing plain-text
 * sd source code.
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils/sharedtypes.h"
#include "utils/utils.h"

#include "lang/tokens.h"
#include "lang/langutils.h"
#include "lang/bytecode/bytecode_tokens.h"

#include "sdparse.h"

/// The last element tracks the number of elements
static uint t_start, t_end;

/**
 * This function is static,
 * it needs manual update
 * when recompiling
 */

bool t_find_def (char c, uint* m_index) {

	bool exit_status;
	char prev_match_t = (char) 0;

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

			if (
			     (direction == up_down && c < *(Keyword_manifest[t_start])) || /// might not EVER be the case, but just to be sure ...
			     (direction == down_up && c > *(Keyword_manifest[t_start]))
			   )
				return not_found;

			r_repeats: {
			for (uint t = t_start; s_comp (t, t_end); s_advance (t)) {
				if (c == Keyword_manifest[t][offset]) {
					if (!prev_match_t)
						prev_match_t = Keyword_manifest[t][offset];
					else
						goto s_repeats;
				}
				else if (prev_match_t)
					goto s_found;
			}

			if (prev_match_t) /// in case of fall-thru
				goto s_found;
			}
		}
		/**
		 * if `c` is not letter, compared it
		 * against `Token_manifest`. if it
		 * is not found, then `c` is a
		 * number.
		 */
		else {

			for (uint t = 0; t < Token_manifest_len; t++)
				if (c == Token_manifest[t])
					return token;
			return number;

		}
	}

	else /// resolute `repeats`
		goto r_repeats;

	s_found: {
		H_RESET (direction);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		return found;
	}
	s_repeats: {
		H_RESET (prev_match_t);
		s_regress (t);
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

		if ( exit_status = t_find_def (c) == repeats)
			continue;

		switch (exit_status) {
			case not_found: /// handle unknown token (as literal)
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

