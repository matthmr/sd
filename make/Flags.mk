# Configuration
CC?=cc
C_INCLUDE_PATH?=.
BITS?=`getconf LONG_BIT`
CFLAGS?='-Wall'
AR?=ar
ARFLAGS?=rc
GZ?=gzip
CTAGS?=ctags
STRIP?=strip
PREFIX?=/usr/local

# Booleans
DOCS?=no
SRCDOCS?=no
TEST?=yes

### NOTE: this configuration only applies to `Makefile's.
###       If you need any of these variables for ./configure,
###       pass them as environment variables
