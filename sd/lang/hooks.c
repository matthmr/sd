/**
 * This file contains the
 * implementations for
 * built-in object hooks
 */

#include <string.h>

#include <sd/lang/langutils.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/hooks.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>
#include <sd/utils/err/err.h>

bool lock_stream = false;
Ctxt g_ctxt;

// -- `tty` -- //
void tty_obj_ref_del (_T _t) { }

void tty_obj_ref (_T _t) { }

void tty_obj_def (_T _t) { }

void tty_expr_hook (_T _t) { }

void tty_syn_hook (_T _t) {

	/* comment */
	static uint cmt_ctr, cmt_sctr;

	switch (_t.t) {
	case '-':
		if (! cmt_ctr)
			cmt_sctr = cmt_ctr;
		else {

			if (cmt_ctr - cmt_sctr == 1) {
				sstream (H_LOCK (g_ctxt.cmtl));
			}

			cmt_ctr = -1;
			H_RESET (cmt_sctr);

		} break;
	case '"':
		sstream (g_ctxt.str = DQSTR);
		break;
	case '\'':
		sstream (g_ctxt.str = SQSTR);
		break;
	}

	cmt_ctr++;

}

_at_handler at_handler[5] = {
	[TTY_OBJ_REF_DEL] = &tty_obj_ref_del,
	[TTY_OBJ_REF] = &tty_obj_ref,
	[TTY_OBJ_DEF] = &tty_obj_def,
	[TTY_EXPR] = &tty_expr_hook,
	[TTY_SYN] = &tty_syn_hook
};
// -- `tty` -- //

// -- `kwty` -- //
// _akw_handler akw_handler[] {  };
// -- `kwty` -- //

/* `ct_close` returns `true` if the comment
 * block was successfully closed, otherwise
 * `false` */
bool ct_close (uint* i, char* line) {

	char* c;
	char* _c = line + *i;

	static bool ctr;

	if ((c = strchr (line+*i, '-')) == NULL)
		return false;

	do {

		c += 1;

		switch (ctr) {
		case 0: case 1:
			if (*c == '-') {
				ctr++;
				continue;
			}
			else {
				H_RESET (ctr);
			}
			break;

		case 2: case 3:
			if (*c == ']') {
				ctr++;
				continue;
			}
			else {
				H_RESET (ctr);
			}
			break;
		case 4:
			break;
			break;
		}

	} while (*c != '\0');

	if (ctr == 3) {
		cstream (H_RESET (g_ctxt.cmtl));
		cstream (H_RESET (g_ctxt.cmtb));
		*i = ((uint) (c-_c)) - *i;
		return true;
	}
	else {
		H_RESET (ctr);
	}

}

/* `s_ignore` returns `false` if a comment
 *  block was opened, otherwise `true` if
 *  a comment line was opened */
bool s_ignore (uint* i, uint lnsize, char* line) {

	/// new-line fall-trough
	if (g_ctxt.cmtb)
		return false;

	if ((lnsize - *i) < 2)
		goto cmt_close;

	if (line[*i] == '[' && line[*i+1] == '[') {
		sstream (H_LOCK (g_ctxt.cmtb));
		H_RESET (g_ctxt.cmtl);
		*i+=2;
		return false;
	}
	else cmt_close: {
		cstream (H_RESET (g_ctxt.cmtl));
		return true;
	}

}
