/**
 * This file contains functionality
 * for literal integer-like
 * assignment/reference
 */

#ifndef LOCK_LITERAL
#  define LOCK_LITERAL

#  include <sd/lang/callback/ptreecb.h>
#  include <sd/utils/types/shared.h>

#  define HEX_INT_HEADER(x) (x[0] == '0' && x[1] == 'x')
#  define BIN_INT_HEADER(x) (x[0] == '0' && x[1] == 'b')

#  ifndef LOCK_LITERALFN
#    define LOCK_LITERALFN
void astring_hook (char*);
ptree_cb aint_hook (char*, uint);

d_addr get_num_with_base (char*, uint, u8);
float get_fnum (char*, uint);
#  endif

#endif
