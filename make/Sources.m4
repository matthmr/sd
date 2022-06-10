include(make/m4/defaults.m4)dnl
dnl
define(daddr_bits_flag, `-DADDR_BITS=${BITS}')dnl
define(file, `define(`M4FLAG_mk_$1', `$2')')dnl
define(M4FLAG_mk, ADDR_BITS)dnl
dnl
file(`precedence', daddr_bits_flag)dnl
file(`vm', daddr_bits_flag)dnl
file(`sdparse', daddr_bits_flag)dnl
undefine(daddr_bits_flag)dnl
undefine(file)dnl
include(make/Sources.mk.m4)
