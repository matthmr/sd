include(make/defaults.m4)dnl
define(makeflag, `$1?=M4FLAG_conf_$1')dnl
dnl
makeflag(`CC')
makeflag(`C_INCLUDE_PATH')
makeflag(`BITS')
makeflag(`CFLAGS')
makeflag(`AR')
makeflag(`ARFLAGS')
makeflag(`GZ')
makeflag(`CTAGS')
makeflag(`STRIP')
makeflag(`PREFIX')
makeflag(`DOCS')
makeflag(`SRCDOCS')
makeflag(`TEST')
dnl
undefine(`makeflag')dnl
