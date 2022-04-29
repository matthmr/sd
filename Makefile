# Made by mH (https://github.com/matthmr)
### COMPILER ###
CC?=clang
INCLUDE?=-I${PWD}
BITS?=64
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
SDLANG_PATCH=2
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
	@echo   - BITS: machine memmory address bit length \(e.g 32, 64\) \(${BITS}\)
	@echo   - CCFLAG: CC flags \(${CCFLAG}\)
	@echo   - AR: archiver \(${AR}\)
	@echo   - ARFLAG: archiver flags \(${ARFLAG}\)
	@echo   - GZ: gzip compressor \(${GZ}\)
	@echo   - FIND: find-like command \(${FIND}\)
	@echo   - XARGS: xargs-like command \(${XARGS}\)
	@echo   - CTAGS: ctags-like command \(${CTAGS}\)
	@echo   - PREFIX: prefix for installation \(${PREFIX}\)
	@echo   - SRIP: strip-like command \(${STRIP}\)
parser: sd/intr/exec/sdread.o\
	lib/libsdparse.a\
	lib/libsdutils.a\
	lib/libsdlang.a\
	lib/libsdvm.a
	@echo [ .. ] Linking to 'sdread'
	${CC} ${CCFLAG} -o bin/sdread sd/intr/exec/sdread.o -Llib -lsdparse -lsdlang -lsdutils -lsdvm
	@echo [ .. ] Finished compilation
man: man/man1/sdread.1 man/man1/sdc.1
	@echo [ .. ] Compressing 'sdread' man page
	${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz
	@echo [ .. ] Compressing 'sdc' man page
	${GZ} -c man/man1/sdc.1 > man/man1/sdc.1.gz
compiler: sd/comp/sdc.o\
	lib/libsdparse.a\
	lib/libsdutils.a\
	lib/libsdlang.a\
	lib/libsdvm.a
	@echo [ .. ] Linking to 'sdc'
	${CC} ${CCFLAG} -o bin/sdc sd/comp/sdc.o
	@echo [ .. ] Finished compilation
#language: lib/libsdlang.so
### END TARGETS ###
### BEGIN COMPILING ###
sd/comp/sdc.o: sd/comp/sdc.c sd/comp/sdc.h
	@echo [ .. ] Compiling 'sdc.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/comp/sdc.c -o sd/comp/sdc.o
sd/intr/bytecode/sdbcparse.o: sd/intr/bytecode/sdbcparse.c sd/intr/bytecode/sdbcparse.h\
	sd/utils/types/shared.h
	@echo [ .. ] Compiling 'sdbcparse.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/bytecode/sdbcparse.c -o sd/intr/bytecode/sdbcparse.o
sd/intr/exec/sdread.o: sd/intr/exec/sdread.c sd/intr/exec/sdread.h\
	sd/utils/types/shared.h\
	sd/utils/err/err.h\
	sd/utils/utils.h
	@echo [ .. ] Compiling 'sdread.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/exec/sdread.c -o sd/intr/exec/sdread.o
sd/lang/fs/ot.o: sd/lang/fs/ot.c sd/lang/fs/ot.h
	@echo [ .. ] Compiling 'ot.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/fs/ot.c -o sd/lang/fs/ot.o
sd/intr/txt/sdparse.o: sd/intr/txt/sdparse.c sd/intr/txt/sdparse.h\
	sd/utils/types/shared.h\
	sd/lang/core/obj.h\
	sd/intr/limits.h
	@echo [ .. ] Compiling 'sdparse.o'
	${CC} ${INCLUDE} -c ${CCFLAG} -DADDR_BITS=${BITS} sd/intr/txt/sdparse.c -o sd/intr/txt/sdparse.o
sd/lang/hooks/txt/thooks.o: sd/lang/hooks/txt/thooks.c sd/lang/hooks/txt/txthooks.h
	@echo [ .. ] Compiling 'thooks.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/hooks/txt/thooks.c -o sd/lang/hooks/txt/thooks.o
sd/lang/hooks/txt/kwhooks.o: sd/lang/hooks/txt/kwhooks.c sd/lang/hooks/txt/txthooks.h
	@echo [ .. ] Compiling 'kwhooks.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/hooks/txt/kwhooks.c -o sd/lang/hooks/txt/kwhooks.o
sd/lang/hooks/txt/txthooks.o: sd/lang/hooks/txt/txthooks.h sd/lang/hooks/txt/txthooks.c
	@echo [ .. ] Compiling 'txthooks.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/hooks/txt/txthooks.c -o sd/lang/hooks/txt/txthooks.o
sd/lang/vm/tab/tab.o: sd/lang/vm/tab/tab.h sd/lang/vm/tab/tab.c
	@echo [ .. ] Compiling 'tab.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/vm/tab/tab.c -o sd/lang/vm/tab/tab.o
sd/lang/expr/expr.o: sd/lang/expr/expr.c sd/lang/expr/expr.h
	@echo [ .. ] Compiling 'expr.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/expr/expr.c -o sd/lang/expr/expr.o
sd/intr/txt/ptree/ptree.o: sd/intr/txt/ptree/ptree.c sd/intr/txt/ptree/ptree.h
	@echo [ .. ] Compiling 'ptree.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/intr/txt/ptree/ptree.c -o sd/intr/txt/ptree/ptree.o
sd/lang/hooks/txt/literal.o: sd/lang/hooks/txt/literal.c sd/lang/hooks/txt/literal.h
	@echo [ .. ] Compiling 'literal.o'
	${CC} ${INCLUDE} -c ${CCFLAG} -DADDR_BITS=${BITS} sd/lang/hooks/txt/literal.c -o sd/lang/hooks/txt/literal.o
sd/intr/txt/ptree/op/precedence.o: sd/intr/txt/ptree/op/precedence.c sd/intr/txt/ptree/op/precedence.h
	@echo [ .. ] Compiling 'precedence.o'
	${CC} ${INCLUDE} -c ${CCFLAG} -DADDR_BITS=${BITS} sd/intr/txt/ptree/op/precedence.c -o sd/intr/txt/ptree/op/precedence.o
sd/lang/vm/vm.o: sd/lang/vm/vm.c sd/lang/vm/vm.h
	@echo [ .. ] Compiling 'vm.o'
	${CC} ${INCLUDE} -c ${CCFLAG} -DADDR_BITS=${BITS} sd/lang/vm/vm.c -o sd/lang/vm/vm.o
sd/lang/atom/atom.o: sd/lang/atom/atom.c sd/lang/atom/atom.h
	@echo [ .. ] Compiling 'atom.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/atom/atom.c -o sd/lang/atom/atom.o
sd/lang/expr/drivers/drivers.o: sd/lang/expr/drivers/drivers.c sd/lang/expr/drivers/drivers.h
	@echo [ .. ] Compiling 'drivers.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/expr/drivers/drivers.c -o sd/lang/expr/drivers/drivers.o
sd/lang/tokens/virtual/vt.o: sd/lang/tokens/virtual/vt.c sd/lang/tokens/virtual/vt.h
	@echo [ .. ] Compiling 'vt.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/tokens/virtual/vt.c -o sd/lang/tokens/virtual/vt.o
### END COMPILING ###
### BEGIN COMPILING UTILS ###
sd/lang/tokens/txt.o: sd/lang/tokens/txt.c sd/lang/tokens/txt.h
	@echo [ .. ] Compiling 'txt.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/lang/tokens/txt.c -o sd/lang/tokens/txt.o
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
sd/utils/err/verr.o: sd/utils/err/verr.c sd/utils/err/verr.h
	@echo [ .. ] Compiling 'verr.o'
	${CC} ${INCLUDE} -c ${CCFLAG} sd/utils/err/verr.c -o sd/utils/err/verr.o
### END COMPILING UTILS ###
### BEGIN ARCHIVING ###
lib/libsdutils.a: sd/utils/utils.o\
	sd/intr/txt/utils/txtutils.o\
	sd/utils/err/verr.o\
	sd/utils/err/err.o
	@echo [ .. ] Archiving to 'libsdutils.a'
	${AR} ${ARFLAG} lib/libsdutils.a $?
lib/libsdparse.a: sd/lang/hooks/txt/txthooks.o\
	sd/intr/txt/ptree/op/precedence.o\
	sd/lang/expr/drivers/drivers.o\
	sd/intr/bytecode/sdbcparse.o\
	sd/lang/hooks/txt/kwhooks.o\
	sd/lang/hooks/txt/thooks.o\
	sd/intr/txt/ptree/ptree.o\
	sd/intr/txt/sdparse.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	${AR} ${ARFLAG} lib/libsdparse.a $?
lib/libsdlang.a: sd/lang/hooks/txt/literal.o\
	sd/lang/tokens/virtual/vt.o\
	sd/lang/tokens/txt.o\
	sd/lang/expr/expr.o\
	sd/lang/fs/ot.o
	@echo [ .. ] Archiving to 'libsdlang.a'
	${AR} ${ARFLAG} lib/libsdlang.a $?
lib/libsdvm.a: sd/lang/vm/vm.o\
	sd/lang/vm/tab/tab.o
	@echo [ .. ] Archiving to 'libsdvm.a'
	${AR} ${ARFLAG} lib/libsdvm.a $?
lib/libsd.so:
	@echo [ .. ] Compiling to 'libsd.so'
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
