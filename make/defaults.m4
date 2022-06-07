define(default, `ifdef(`M4FLAG_conf_$1',, `define(`M4FLAG_conf_$1', `$2')')')dnl
dnl
default(`BITS', `64')dnl
default(`CC', `cc')dnl
default(`C_INCLUDE_PATH', `.')dnl
default(`CFLAGS', `-Wall')dnl
default(`AR', `ar')dnl
default(`ARFLAGS', `rc')dnl
default(`GZ', `gzip')dnl
default(`CTAGS', `ctags')dnl
default(`STRIP', `strip')dnl
default(`PREFIX', `/usr/local')dnl
default(`DOCS', `no')dnl
default(`SRCDOCS', `no')dnl
default(`TEST', `yes')dnl
dnl
undefine(`default')dnl
