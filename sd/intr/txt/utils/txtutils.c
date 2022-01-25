/**
 * This files contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#include <string.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/utils/types/shared.h>
#include <sd/lang/core/obj.h>
#include <sd/utils/utils.h>
#include <sd/lang/tokens.h>

void offset_i (uint* i, uint* g_offset, char* line, uint lnsize, char del) {
	char c;
	uint len = 0;

	while ((len+*g_offset) < lnsize) {
		c = line[len+*g_offset];
		if (c == del || WHITESPACE (c) ||
		!  ( VALID (c) || NUMBER (c) ))
			break;
		else
			len++;
	}

	if (!len) /// fall-through
		return;
	
	*g_offset += len; /// point to `i` of an adjancent name...
	*i = (*g_offset-1); /// ... counting for incremental loop
}

bool tfind_def (char c) {

	uint size = token_manifest_len;
	uint block = size/2;

	/// odd-sized token array
	if (size % 2)
		if (c == token_manifest[size/2].t)
			return ttoken;

	for (t = 0; t < block; t++)
		if (c == token_manifest[t].t ||
		    c == token_manifest[(size-1)-t].t) {

			t = (c == token_manifest[(size-1)-t].t)?
				(size-1)-t: t;
			return ttoken;

		}

}

bool nfind_def (char c) {

	bool exit_status;
	bool rep_lock = false;

	static bool _call;

	static uint t_start, t_end;
	static uint t_block;
	static uint offset;

	uint _t = 0;

	if (!_call) {

		H_LOCK (_call);
		H_RESET (t);

		if (UPPER_ALPHA (c)) /// all default keywords are lowercase
			return not_found;

		if (LOWER_ALPHA (c)) {

			t_start = 0;
			t_end = keyword_manifest_len-1;

			/// looks for out-of-bound chars
			if (
			    c < *(keyword_manifest[t_start].kw) ||
			    c > *(keyword_manifest[t_end].kw)
			) goto s_not_found;

			if (! rep_lock) {

				uint t_size = keyword_manifest_len-1;
				uint l_offset = 0;

				c_opt_bound: {

				t_block = t_size/2;
				if (t_block <= 4) { /// min block size of 4
					H_LOCK (rep_lock);
					goto c_opt_seek;
				}

				char _c = *keyword_manifest[t_block + l_offset].kw;

				if (c > _c) {
					l_offset +=
						t_start = t_size = t_block;
					goto c_opt_bound;
				}
				else if (c < _c) {
					t_size = t_block;
					_t = t_end = (t_block + l_offset);
					goto c_opt_bound;
				}
				else if (c == _c) {
					H_LOCK (rep_lock);
					t_start = t_block;
					goto c_opt_seek;
				}

				}

			}

			else c_opt_seek: { /// if (! rep_lock)

				for (uint st = t_start; st <= t_end; st++) /// standard seek
					if (c == keyword_manifest[st].kw[offset])
						if (!t)
							_t = t = st;
						else _t++;
					else if (t) break;

				if (!t) /// fall-through
					goto s_not_found;

				c_opt_backward_seek: { /// backward seek
				for (uint st = t_start; st >= 0; st--)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_forward_seek;
					else
						t--;
				}

				c_opt_forward_seek: { /// foward seek
				for (uint st = t_end; st <= keyword_manifest_len; st++)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_ret;
					else
						_t++;
				}

				c_opt_ret: if (_t - t)
					goto s_repeats;
				else
					goto s_found;

			}

		} else { /// resolute literal or token

			if (c == '\n') /// whitespace
				goto s_not_found;

			if (NUMBER (c)) {
				H_RESET (_call);
				return literal;
			}

			if (tfind_def (c) == ttoken) {
				H_RESET (_call);
				return ttoken;
			}

			goto s_not_found;

		}

	} else {

		_t = t = t_start;

		bool lock;

		for (uint st = t_start; st <= t_end; st++) {
			if (c != keyword_manifest[st].kw[offset])
				continue;
			else
				if (!lock) {
					H_LOCK (lock);
					_t = t = st;
				}
				else
					_t = st;
		}

		if (_t - t)
			goto s_repeats;
		else
			goto s_found;

	}

	s_not_found: {
		H_RESET (_call);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);
		H_RESET (t_block);

		return not_found;
	}

	s_found: {

		H_RESET (_call);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);
		H_RESET (t_block);

		return found;
	}

	s_repeats: {
		/* bound `t` between the first matching and the last matching token */
		t_start = t;
		t_end = _t;

		offset++;
		return repeats;
	}

}

