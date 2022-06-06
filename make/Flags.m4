define(ADDR_BITS, `-DADDR_BITS=64')dnl
dnl
define(M4FLAG_limits, ADDR_BITS)dnl
define(M4FLAG_precedence, ADDR_BITS)dnl
define(M4FLAG_vm, ADDR_BITS)dnl
define(M4FLAG_sdparse, ADDR_BITS)dnl
undefine(ADDR_BITS)dnl
include(make/Sources.mk.m4)
