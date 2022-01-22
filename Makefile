# Made by mH (https://github.com/matthmr)

### COMPILER ###
CC?=gcc
INCLUDE?=-I${PWD}
CCFLAG?=

### ARCHIVER ###
AR?=ar
ARFLAG?=rc

### COMMANDS ###
GZ?=gzip
FIND?=find
XARGS?=xargs
CTAGS?=ctags

### INSTALLATION ###
PREFIX?=/usr/local

### INFO ###
SDLANG_MAJOR=0
SDLANG_MINOR=3
SDLANG_PATCH=0

### BEGIN BASE ###
default: install

clean:
	@echo [ .. ] Cleaning working directory
	${FIND} -type f -name '*.[oa]' | ${XARGS} rm -rf man/**/*.gz

install: language parser compiler man
	@echo [ .. ] Moving the sd language module to '${PREFIX}/bin'
	mv bin/sdread bin/sd bin/sdc ${PREFIX}/bin || echo [ !! ] No permission to move binaries to ${PREFIX}/bin
	@echo [ .. ] Moving the sd language library to '${PREFIX}/lib'
	mv libsdlang.so ${PREFIX}/lib || echo [ !! ] No permission to move backend to ${PREFIX}/lib
	@echo [ .. ] Moving man pages to '${PREFIX}/man'
	mkdir -p ${PREFIX}/man/man1/ && mv man/* ${PREFIX}/man/man1 || echo [ !! ] No permission to move backend to ${PREFIX}/man
### END BASE ###

### BEGIN TARGETS ###
help:
	@echo \[\[ available targets \]\]
	@echo   - parser: main parser for SD \(sdread\)
	@echo   - compiler: main compiler for SD \(sdc\)
	@echo   - language: main library for SD \(libsdlang.so\)
	@echo   - man: compresses man pages
	@echo   - install: runs all of the above and moves files to the appropiate locations
	@echo   - clean: cleans working directory \(\*.o, \*.a and \*.gz files\)
	@echo   - tags: produces \`tags\` file for editors that use it
	@echo   - help: displays this message
	@echo
	@echo \[\[ available variables \]\]
	@echo   - CC: C compiler \(${CC}\)
	@echo   - INCLUDE: include path \(${INCLUDE}\)
	@echo   - CCFLAG: CC flags \(${CCFLAG}\)
	@echo   - AR: archiver \(${AR}\)
	@echo   - ARFLAG: archiver flags \(${ARFLAG}\)
	@echo   - GZ: gzip compresser \(${GZ}\)
	@echo   - FIND: find-like command \(${FIND}\)
	@echo   - XARGS: xargs-like command \(${XARGS}\)
	@echo   - CTAGS: ctags-like command \(${CTAGS}\)
	@echo   - PREFIX: prefix for installation \(${PREFIX}\)

## TODO: make `-lsdlang` shared instead of static

parser: sd/intr/exec/sdread.o\
	lib/libsdparse.a\
	lib/libsdlang.a
	@echo [ .. ] Linking to 'sdread'
	${CC} ${CCFLAG} -o bin/sdread sd/intr/exec/sdread.o -Llib -lsdparse -lsdlang
	@echo [ .. ] Finished compilation

man: man/man1/sdread.1
	@echo [ .. ] Compressing 'sdread' man page
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz

compiler:

language: lib/libsdlang.so
### END TARGETS ###

### BEGIN COMPILING ###
sd/intr/exec/sdread.o: sd/intr/exec/sdread.c sd/intr/exec/sdread.h\
	sd/utils/types/shared.h\
	sd/utils/err/err.h\
	sd/utils/utils.h
	@echo [ .. ] Compiling 'sdread.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/exec/sdread.c -o sd/intr/exec/sdread.o

sd/intr/txt/sdparse.o: sd/intr/txt/sdparse.c sd/intr/txt/sdparse.h\
	sd/lang/tokens.h\
	sd/lang/core/obj.h\
	sd/utils/types/shared.h\
	sd/lang/langutils.h\
	sd/intr/txt/utils/txtutils.o\
	sd/lang/hooks.o\
	sd/lang/langutils.o\
	sd/utils/utils.o\
	sd/utils/err/err.o
	@echo [ .. ] Compiling 'sdparse.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/txt/sdparse.c -o sd/intr/txt/sdparse.o

sd/lang/hooks.o: sd/lang/hooks.c sd/lang/hooks.h
	@echo [ .. ] Compiling 'hooks.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/hooks.c -o sd/lang/hooks.o
### END COMPILING ###

### BEGIN COMPILING UTILS ###
sd/lang/langutils.o: sd/lang/langutils.c sd/lang/langutils.h\
	sd/utils/types/shared.h
	@echo [ .. ] Compiling 'langutils.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/langutils.c -o sd/lang/langutils.o

sd/intr/txt/utils/txtutils.o: sd/intr/txt/utils/txtutils.c sd/intr/txt/utils/txtutils.h\
	sd/utils/utils.o\
	sd/utils/types/shared.h
	@echo [ .. ] Compiling 'txtutils.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/txt/utils/txtutils.c -o sd/intr/txt/utils/txtutils.o

sd/utils/utils.o: sd/utils/utils.c sd/utils/utils.h\
	sd/utils/types/shared.h
	@echo [ .. ] Compiling 'utils.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/utils/utils.c -o sd/utils/utils.o

sd/utils/err/err.o: sd/utils/err/err.c sd/utils/err/err.h
	@echo [ .. ] Compiling 'err.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/utils/err/err.c -o sd/utils/err/err.o
### END COMPILING UTILS ###

### BEGIN ARCHIVING ###
lib/libsdparse.a: sd/utils/utils.o\
	sd/utils/err/err.o\
	sd/intr/txt/sdparse.o\
	sd/intr/txt/utils/txtutils.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	${AR} ${ARFLAG} lib/libsdparse.a $?

lib/libsdlang.a: sd/lang/langutils.o sd/lang/hooks.o
	@echo [ .. ] Archiving to 'libsdlang.a'
	${AR} ${ARFLAG} lib/libsdlang.a $?

lib/libsdlang.so:
	@echo [ .. ] Compiling to 'libsdlang.so'
	@echo [ .. ] major version: ${SDLANG_MAJOR}
	@echo [ .. ] minor version: ${SDLANG_MINOR}
	@echo [ .. ] patch: ${SDLANG_PATCH}
### END ARCHIVING ###

### BEGIN OPTIONAL ###
tags:
	@echo [ .. ] Updating tags file
	${CTAGS} -R .
### END OPTIONAL ###

.PHONY: tags parser man compiler language
