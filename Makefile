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
STRIP?=strip

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
	@echo [ .. ] Stripping symbols off of 'sdread' and 'sdc'
	pushd bin
	${STRIP} sdread
	${STRIP} sdc
	popd
	@echo [ .. ] Symlinking to 'sdread'
	ln -sfn sdread bin/sd
	@echo [ .. ] Moving the sd language module to '${PREFIX}/bin'
	mv bin/sdread bin/sd bin/sdc ${PREFIX}/bin || echo [ !! ] No permission to move binaries to ${PREFIX}/bin
	@echo [ .. ] Moving the sd language library to '${PREFIX}/lib'
	mv libsdlang.so ${PREFIX}/lib || echo [ !! ] No permission to move backend to ${PREFIX}/lib
	@echo [ .. ] Moving man pages to '${PREFIX}/man'
	mkdir -p ${PREFIX}/man/man1/ && mv man/* ${PREFIX}/man/man1 || echo [ !! ] No permission to move documentation to ${PREFIX}/man
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
	@echo   - SRIP: strip-like command \(${STRIP}\)

## TODO: make `-lsdlang` shared instead of static

parser: sd/intr/exec/sdread.o\
	lib/libsdparse.a\
	lib/libsdlang.a
	@echo [ .. ] Linking to 'sdread'
	${CC} ${CCFLAG} -o bin/sdread sd/intr/exec/sdread.o -Llib -lsdparse -lsdlang
	@echo [ .. ] Finished compilation

man: man/man1/sdread.1 man/man1/sdc.1
	@echo [ .. ] Compressing 'sdread' man page
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz
	@echo [ .. ] Compressing 'sdc' man page
	@${GZ} -c man/man1/sdc.1 > man/man1/sdc.1.gz

compiler: sd/comp/sdc.o
	@echo [ .. ] Linking to 'sdc'
	${CC} ${CCFLAG} -o bin/sdc sd/comp/sdc.o
	@echo [ .. ] Finished compilation

language: lib/libsdlang.so
### END TARGETS ###

### BEGIN COMPILING ###
sd/comp/sdc.o: sd/comp/sdc.c sd/comp/sdc.h

sd/intr/bytecode/sdbcparse.o: sd/intr/bytecode/sdbcparse.c sd/intr/bytecode/sdbcparse.h\
	sd/utils/types/shared.h\
	sd/lang/tokens/bytecode.h
	@echo [ .. ] Compiling 'sdbcparse.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/bytecode/sdbcparse.c -o sd/intr/bytecode/sdbcparse.o

sd/intr/exec/sdread.o: sd/intr/exec/sdread.c sd/intr/exec/sdread.h\
	sd/utils/types/shared.h\
	sd/utils/err/err.h\
	sd/utils/utils.h
	@echo [ .. ] Compiling 'sdread.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/exec/sdread.c -o sd/intr/exec/sdread.o

sd/intr/txt/sdparse.o: sd/intr/txt/sdparse.c sd/intr/txt/sdparse.h\
	sd/lang/core/obj.h\
	sd/lang/utils/langutils.o\
	sd/intr/txt/utils/txtutils.o\
	sd/lang/hooks/txthooks.o\
	sd/utils/types/shared.h\
	sd/lang/tokens/txt.o\
	sd/utils/utils.o\
	sd/utils/err/err.o
	@echo [ .. ] Compiling 'sdparse.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/txt/sdparse.c -o sd/intr/txt/sdparse.o

sd/lang/hooks/txthooks.o: sd/lang/hooks/txthooks.c sd/lang/hooks/txthooks.h
	@echo [ .. ] Compiling 'txthooks.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/hooks/txthooks.c -o sd/lang/hooks/txthooks.o
### END COMPILING ###

### BEGIN COMPILING UTILS ###
sd/lang/tokens/txt.o: sd/lang/tokens/txt.c sd/lang/tokens/txt.h
	@echo [ .. ] Compiling 'txt.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/tokens/txt.c -o sd/lang/tokens/txt.o

sd/lang/utils/langutils.o: sd/lang/utils/langutils.c sd/lang/utils/langutils.h\
	sd/utils/types/shared.h
	@echo [ .. ] Compiling 'langutils.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/utils/langutils.c -o sd/lang/utils/langutils.o

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
	sd/intr/bytecode/sdbcparse.o\
	sd/intr/txt/utils/txtutils.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	${AR} ${ARFLAG} lib/libsdparse.a $?

lib/libsdlang.a: sd/lang/utils/langutils.o\
	sd/lang/hooks/txthooks.o\
	sd/lang/tokens/txt.o
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
