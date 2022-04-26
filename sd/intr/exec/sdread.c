/**
 * This file is a WRAPPER arround functionality
 * regarding the SD language. It makes it possible
 * to parse and interpret plain-text source code
 * and execute it on the fly
 */

#include <stdio.h>

#include <sd/lang/callback/vmcb.h>
#include <sd/lang/tree/ot.h>
#include <sd/lang/vm/vm.h>

#include <sd/intr/bytecode/sdbcparse.h>
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>
#include <sd/intr/limits.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

#undef LOCK_DATA
#include <sd/intr/exec/sdread.h>

byte data[BUFFER];
promise p;
exit RET = EXIT_OK;

arg parseargs (int margc, char** margv) {

	p.file = stdin;
	p.ftype = SOURCE_DISK;

	char c;

	if (margc == 1)
		return ARG_DEF;

	else for (uint i = 1; i < margc; i++) {

		// resolve promise
		if (p.PFILE) {

			if (p.HFILE)
				goto _arg_err;

			else if (margv[i][0] == '-' && margv[i][1] == '\0') {
				p.file = stdin;
				H_RESET (p.PFILE);
				H_LOCK (p.HFILE);
			}

			else if (! (p.file = fopen (margv[i], "rb")))
				Err (0x01, margv[i]);

		}

		// set promise
		else if (margv[i][0] == '-') {

			if (margv[i][1] && margv[i][2]) // -**
				goto _arg_err;

			switch (margv[i][1]) {

			// info
			case 'v':
				fputs ("sdread " VERSION "\n", stdout);
				return ARG_INFO;
				break;
			case 'h':
				fputs (HELP, stdout);
				return ARG_INFO;
				break;

			// set promise -- `BYTECODE_DISK`
			case 's':
				LOCK (p.PFILE);
				p.ftype = BYTECODE_DISK;
				break;

			// skip promise -- `SOURCE_DISK` : stdin
			case '\0':
				p.ftype = SOURCE_DISK;
				p.file = stdin;
				H_LOCK (p.HFILE);
				break;

			default: _arg_err: // -?
				fputs ("[ !! ] Bad usage. See sdread -h\n", stderr);
				return ARG_ERR;
				break;
			}

		}

		// resolve promise / skip promise
		else { /// argv[i][0] != '-'
			if (!p.HFILE) {
				p.ftype = p.PFILE? BYTECODE_DISK: SOURCE_DISK;
				if (! (p.file = fopen (margv[i], "rb")))
					Err (0x01, margv[i]);
			}
			else
				goto _arg_err;
		}

	}

	if (p.PFILE && !p.HFILE)
		Err (0x02, "");

	return ARG_OK;

}

/// TODO: unhandled `<expr>`: parse it and execute within main file context
int main (int argc, char** argv) {

	e_set (TIME_ARG);
	arg ret = parseargs (argc, argv);

	if (ret == ARG_ERR)
		return ret;

	else if (ret == ARG_INFO)
		goto quit;

	pt_init ();

	/// TODO: maybe accept multiple files as modules? this would become a loop
	
	//Obj l_root;
	//mkchild (&g_root, &l_root);
	//g_self = CAST_addr l_root;

	mkvmstack;
	vm_init ();
	initvmstack;

	/// main callback loop (vm)
	if (FILE_IS_SOURCE (p.ftype)) {
		e_set (TIME_TXT);
		while (src_callback != SRC_END) {
			if (src_stack (src_callback))
				stack_callback (src_callback);
			parse_src (p.file, (char*)data, STDBUFFER);
		}
	}

	/// TODO: bytecode callback loop
	else if (FILE_IS_BYTECODE (p.ftype)) {
		e_set (TIME_BYTE);
		parse_bc (p.file, data, STDBUFFER);
	}

	/// close `file` on exit if not a pipe
	if (! FILE_IS_FIFO (p.ftype))
		fclose (p.file);

	quit: return RET;

}
