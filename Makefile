# Made by mH (https://github.com/matthmr)

### COMPILER ###
CC?=gcc
CCFLAG?=

### ARCHIVER ###
AR?=ar
ARFLAG?=rc
RANLIB?=ranlib

### GUNZIP ###
GZ?=gzip

### INSTALLATION ###
PREFIX?=/usr/local

### BEGIN BASE ###
default: install

clean:
	@echo [ .. ] Cleaning working directory
	@rm -rf intr/**/*.o intr/libsdparse.a intr/txt/utils/*.o utils/*.o utils/**/*.o man/**/*.gz

install: log-clean language parser binary-parser compiler linker man
	@echo [ .. ] Moving the sd language module to '${PREFIX}/bin'
	@mv bin/sdread bin/sdcomp bin/sdexec bin/sdlink ${PREFIX}/bin || echo [ !! ] No permission to move binaries to ${PREFIX}/bin
	@echo [ .. ] Moving the sd language libraries to '${PREFIX}/lib'
	@mv libsdlang.so ${PREFIX}/lib || echo [ !! ] No permission to move backend to ${PREFIX}/lib
	@echo [ .. ] Moving man pages to '${PREFIX}/man'
	@mkdir -p ${PREFIX}/man/man1/ && mv man/* ${PREFIX}/man/man1 || echo [ !! ] No permission to move backend to ${PREFIX}/man
### END BASE ###

### BEGIN COMPILING ###
parser: intr/limits.h\
	utils/utils.o\
	utils/err/err.o\
	intr/txt/sdparse.o intr/exec/sdread.o\
	intr/libsdparse.a\
	language
	@echo [ .. ] Linking to 'sdread'
	@${CC} ${CCFLAG} intr/exec/sdread.o -Llib -lsdparse -o bin/sdread
	@echo [ .. ] Finished compilation

man: man/man1/sdread.1
	@echo [ .. ] Compressing 'sdread' man page
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz

### TODO ###
binary-parser:

compiler:

language:

linker:
### TODO ###

intr/exec/sdread.o: utils/utils.h utils/types/shared.h utils/err/err.h\
	intr/exec/sdread.c
	@echo [ .. ] Compiling 'sdread.o'
	@${CC} -c ${CCFLAG} intr/exec/sdread.c -o intr/exec/sdread.o 

intr/txt/sdparse.o: utils/types/shared.h utils/utils.h\
	intr/txt/sdparse.c intr/txt/sdparse.h\
	intr/txt/utils/txtutils.h\
	utils/err/err.h\
	lang/tokens.h
	@echo [ .. ] Compiling 'sdparse.o'
	@${CC} -c ${CCFLAG} intr/txt/sdparse.c -o intr/txt/sdparse.o

intr/txt/utils/txtutils.o: intr/txt/utils/txtutils.c intr/txt/utils/txtutils.h
	@echo [ .. ] Compiling 'txtutils.o'
	@${CC} -c ${CCFLAG} intr/txt/utils/txtutils.c -o intr/txt/utils/txtutils.o

utils/utils.o: utils/utils.c utils/utils.h utils/types/shared.h
	@echo [ .. ] Compiling 'utils.o'
	@${CC} -c ${CCFLAG} utils/utils.c -o utils/utils.o

utils/err/err.o: utils/err/err.c utils/err/err.h
	@echo [ .. ] Compiling 'err.o'
	@${CC} -c ${CCFLAG} utils/err/err.c -o utils/err/err.o
### END COMPILING ###

### BEGIN ARCHIVING ###
intr/libsdparse.a: utils/utils.o utils/err/err.o intr/txt/sdparse.o intr/txt/utils/txtutils.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	@${AR} ${ARFLAG} lib/libsdparse.a $?
### END ARCHIVING ###

### BEGIN OPTIONAL ###
tags:
	@echo [ .. ] Updating tags file
	@ctags -R .
### END OPTIONAL ###

.PHONY: tags
