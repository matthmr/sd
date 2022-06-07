include(make/defaults.m4)dnl
dnl
define(bits_flag, `-DADDR_BITS=${BITS}')dnl
define(file, `define(`M4FLAG_mk_$1', `$2')')dnl
define(M4FLAG_mk, ADDR_BITS)dnl
dnl
file(`precedence', bits_flag)dnl
file(`vm', bits_flag)dnl
file(`sdparse', bits_flag)dnl
undefine(bits_flag)dnl
undefine(file)dnl
include(make/Sources.mk.m4)
