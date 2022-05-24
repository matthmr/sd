### COMPILER ###
CC?=cc
C_INCLUDE_PATH?=${PWD}
BITS?=`getconf LONG_BIT`
CCFLAGS?='-Wall'
AR?=ar
ARFLAGS?=rc
### COMMANDS ###
GZ?=gzip
CTAGS?=ctags
DOXYGEN?=doxygen
STRIP?=strip
### INSTALLATION ###
PREFIX?=/usr/local
### INSTALLATION CONDITIONALS ###
DOCS?=no
### INFO ###
SDLANG_MAJOR=0
SDLANG_MINOR=3
SDLANG_PATCH=2
### BEGIN BASE ###
default: install
clean:
	@echo [ .. ] Cleaning working directory
	find -type f -name '*.[oa]' | xargs rm -f
clean-docs:
	@echo [ .. ] Cleaning documentation
	rm -rf man/**/*.gz && rm -rf docs/html/*
install: language parser compiler man docs
	@echo [ .. ] Stripping symbols off of 'sdread' and 'sdc'
	pushd bin
	${STRIP} sdread
	${STRIP} sdc
	popd
	@echo [ .. ] Symlinking to 'sdread'
	ln -sf sdread bin/sd
	@echo [ .. ] Moving the sd language module to '${PREFIX}/bin'
	mv bin/sdread bin/sd bin/sdc ${PREFIX}/bin || echo [ !! ] No permission to move binaries to ${PREFIX}/bin
	@echo [ .. ] Moving the sd language library to '${PREFIX}/lib'
	mv libsd.so ${PREFIX}/lib || echo [ !! ] No permission to move backend to ${PREFIX}/lib
	@echo [ .. ] Moving man pages to '${PREFIX}/man'
	mkdir -p ${PREFIX}/man/man1/
	mv man/* ${PREFIX}/man/man1 || echo [ !! ] No permission to move documentation to ${PREFIX}/man
	ifeq (${DOCS},yes)
		@echo [ .. ] Moving html documentation to '${PREFIX}/share/doc/sd'
		mkdir -p ${PREFIX}/share/doc/sd
		mv docs/html/* ${PREFIX}/share/doc/sd || echo [ !! ] No permission to move documentation to ${PREFIX}/share/doc/sd
	else
		@echo [ .. ] Ignoring html documentation
	endif
help:
	@echo \[\[ available targets \]\]
	@echo   - parser: main parser for SD \(sdread\)
	@echo   - compiler: main compiler for SD \(sdc\)
	@echo   - language: main library for SD \(libsd.so\)
	@echo   - man: compresses man pages
	@echo   - install: runs all of the above and moves files to the appropiate locations
	@echo   - clean: cleans working directory \(\*.o and \*.a files\)
	@echo   - clean-docs: cleans documentation \(\*.gz files and files under /docs/html/\)
	@echo   - tags: produces \`tags\` file for editors that use it
	@echo   - help: displays this message
	@echo
	@echo \[\[ available variables \]\]
	@echo   - CC: C compiler \(${CC}\)
	@echo   - C_INCLUDE_PATH: include path \(-I${C_INCLUDE_PATH}\)
	@echo   - BITS: machine memmory address bit length \(e.g 32, 64\) \(${BITS}\)
	@echo   - CCFLAGS: CC flags \(${CCFLAGS}\)
	@echo   - AR: archiver \(${AR}\)
	@echo   - ARFLAGS: archiver flags \(${ARFLAGS}\)
	@echo   - GZ: gzip compressor \(${GZ}\)
	@echo   - CTAGS: ctags-like command \(${CTAGS}\)
	@echo   - DOXYGEN: doxygen command \(${DOXYGEN}\)
	@echo   - PREFIX: prefix for installation \(${PREFIX}\)
	@echo   - SRIP: strip-like command \(${STRIP}\)
	@echo   - DOCS: set to \<yes\> to install language syntax html documentation, otherwise set to \<no\> \(${DOCS}\)
### END BASE ###
### BEGIN TARGETS ###
parser: sd/intr/exec/sdread.o\
	lib/libsdparse.a\
	lib/libsdutils.a\
	lib/libsdlang.a\
	lib/libsdvm.a
	@echo CC sdread
	@${CC} ${CCFLAGS} -o bin/sdread sd/intr/exec/sdread.o -Llib -lsdparse -lsdlang -lsdutils -lsdvm
	@echo [ .. ] Finished compilation
compiler: sd/comp/sdc.o\
	lib/libsdparse.a\
	lib/libsdutils.a\
	lib/libsdlang.a\
	lib/libsdvm.a
	@echo CC sdc
	@${CC} ${CCFLAGS} -o bin/sdc sd/comp/sdc.o
	@echo [ .. ] Finished compilation
#language: lib/libsd.so
man: man/man1/sdread.1 man/man1/sdc.1
	@echo [ .. ] Compressing 'sdread' man page
	${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz
	@echo [ .. ] Compressing 'sdc' man page
	${GZ} -c man/man1/sdc.1 > man/man1/sdc.1.gz
### END TARGETS ###
### BEGIN COMPILING ###
sd/comp/sdc.o: sd/comp/sdc.c sd/comp/sdc.h
	@echo CC sdc.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/comp/sdc.c -o sd/comp/sdc.o
sd/intr/bytecode/sdbcparse.o: sd/intr/bytecode/sdbcparse.c sd/intr/bytecode/sdbcparse.h\
	sd/utils/types/shared.h
	@echo CC sdbcparse.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/intr/bytecode/sdbcparse.c -o sd/intr/bytecode/sdbcparse.o
sd/intr/exec/sdread.o: sd/intr/exec/sdread.c sd/intr/exec/sdread.h\
	sd/utils/types/shared.h\
	sd/utils/err/err.h\
	sd/utils/utils.h
	@echo CC sdread.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/intr/exec/sdread.c -o sd/intr/exec/sdread.o
sd/lang/obj/ot.o: sd/lang/obj/ot.c sd/lang/obj/ot.h
	@echo CC ot.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/obj/ot.c -o sd/lang/obj/ot.o
sd/intr/txt/sdparse.o: sd/intr/txt/sdparse.c sd/intr/txt/sdparse.h\
	sd/utils/types/shared.h\
	sd/lang/core/statement.h\
	sd/intr/limits.h
	@echo CC sdparse.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} -DADDR_BITS=${BITS} sd/intr/txt/sdparse.c -o sd/intr/txt/sdparse.o
sd/lang/hooks/txt/thooks.o: sd/lang/hooks/txt/thooks.c sd/lang/hooks/txt/txthooks.h
	@echo CC thooks.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/hooks/txt/thooks.c -o sd/lang/hooks/txt/thooks.o
sd/lang/hooks/txt/kwhooks.o: sd/lang/hooks/txt/kwhooks.c sd/lang/hooks/txt/txthooks.h
	@echo CC kwhooks.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/hooks/txt/kwhooks.c -o sd/lang/hooks/txt/kwhooks.o
sd/lang/hooks/txt/txthooks.o: sd/lang/hooks/txt/txthooks.h sd/lang/hooks/txt/txthooks.c
	@echo CC txthooks.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/hooks/txt/txthooks.c -o sd/lang/hooks/txt/txthooks.o
sd/lang/vm/tab/tab.o: sd/lang/vm/tab/tab.h sd/lang/vm/tab/tab.c
	@echo CC tab.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/vm/tab/tab.c -o sd/lang/vm/tab/tab.o
sd/lang/expr/expr.o: sd/lang/expr/expr.c sd/lang/expr/expr.h
	@echo CC expr.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/expr/expr.c -o sd/lang/expr/expr.o
sd/intr/txt/ptree/ptree.o: sd/intr/txt/ptree/ptree.c sd/intr/txt/ptree/ptree.h
	@echo CC ptree.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/intr/txt/ptree/ptree.c -o sd/intr/txt/ptree/ptree.o
sd/lang/hooks/txt/literal.o: sd/lang/hooks/txt/literal.c sd/lang/hooks/txt/literal.h
	@echo CC literal.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} -DADDR_BITS=${BITS} sd/lang/hooks/txt/literal.c -o sd/lang/hooks/txt/literal.o
sd/intr/txt/ptree/op/precedence.o: sd/intr/txt/ptree/op/precedence.c sd/intr/txt/ptree/op/precedence.h
	@echo CC precedence.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} -DADDR_BITS=${BITS} sd/intr/txt/ptree/op/precedence.c -o sd/intr/txt/ptree/op/precedence.o
sd/lang/vm/vm.o: sd/lang/vm/vm.c sd/lang/vm/vm.h
	@echo CC vm.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} -DADDR_BITS=${BITS} sd/lang/vm/vm.c -o sd/lang/vm/vm.o
sd/lang/atom/atom.o: sd/lang/atom/atom.c sd/lang/atom/atom.h
	@echo CC atom.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/atom/atom.c -o sd/lang/atom/atom.o
sd/lang/expr/drivers/drivers.o: sd/lang/expr/drivers/drivers.c sd/lang/expr/drivers/drivers.h
	@echo CC drivers.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/expr/drivers/drivers.c -o sd/lang/expr/drivers/drivers.o
sd/lang/tokens/virtual/vt.o: sd/lang/tokens/virtual/vt.c sd/lang/tokens/virtual/vt.h
	@echo CC vt.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/tokens/virtual/vt.c -o sd/lang/tokens/virtual/vt.o
sd/lang/tokens/virtual/comp.o: sd/lang/tokens/virtual/comp.c sd/lang/tokens/virtual/comp.h
	@echo CC comp.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/tokens/virtual/comp.c -o sd/lang/tokens/virtual/comp.o
sd/lang/tokens/virtual/mask.o: sd/lang/tokens/virtual/mask.c sd/lang/tokens/virtual/mask.h
	@echo CC mask.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/tokens/virtual/mask.c -o sd/lang/tokens/virtual/mask.o
sd/lang/tokens/virtual/match.o: sd/lang/tokens/virtual/match.c sd/lang/tokens/virtual/match.h
	@echo CC match.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/tokens/virtual/match.c -o sd/lang/tokens/virtual/match.o
### END COMPILING ###
### BEGIN COMPILING UTILS ###
sd/lang/tokens/txt.o: sd/lang/tokens/txt.c sd/lang/tokens/txt.h
	@echo CC txt.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/lang/tokens/txt.c -o sd/lang/tokens/txt.o
sd/intr/txt/utils/txtutils.o: sd/intr/txt/utils/txtutils.c sd/intr/txt/utils/txtutils.h\
	sd/utils/utils.o\
	sd/utils/types/shared.h
	@echo CC txtutils.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/intr/txt/utils/txtutils.c -o sd/intr/txt/utils/txtutils.o
sd/utils/utils.o: sd/utils/utils.c sd/utils/utils.h\
	sd/utils/types/shared.h
	@echo CC utils.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/utils/utils.c -o sd/utils/utils.o
sd/utils/err/err.o: sd/utils/err/err.c sd/utils/err/err.h
	@echo CC err.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/utils/err/err.c -o sd/utils/err/err.o
sd/utils/err/verr.o: sd/utils/err/verr.c sd/utils/err/verr.h
	@echo CC verr.c
	@${CC} -I${C_INCLUDE_PATH} -c ${CCFLAGS} sd/utils/err/verr.c -o sd/utils/err/verr.o
### END COMPILING UTILS ###
### BEGIN ARCHIVING ###
lib/libsdutils.a: sd/utils/utils.o\
	sd/intr/txt/utils/txtutils.o\
	sd/utils/err/verr.o\
	sd/utils/err/err.o
	@echo AR libsdutils.a
	@${AR} ${ARFLAGS} lib/libsdutils.a $?
lib/libsdparse.a: sd/lang/hooks/txt/txthooks.o\
	sd/intr/txt/ptree/op/precedence.o\
	sd/lang/expr/drivers/drivers.o\
	sd/intr/bytecode/sdbcparse.o\
	sd/lang/hooks/txt/kwhooks.o\
	sd/lang/hooks/txt/thooks.o\
	sd/intr/txt/ptree/ptree.o\
	sd/intr/txt/sdparse.o
	@echo AR libsdparse.a
	@${AR} ${ARFLAGS} lib/libsdparse.a $?
lib/libsdlang.a: sd/lang/hooks/txt/literal.o\
	sd/lang/tokens/virtual/match.o\
	sd/lang/tokens/virtual/comp.o\
	sd/lang/tokens/virtual/mask.o\
	sd/lang/tokens/virtual/vt.o\
	sd/lang/tokens/txt.o\
	sd/lang/expr/expr.o\
	sd/lang/obj/ot.o
	@echo AR libsdlang.a
	@${AR} ${ARFLAGS} lib/libsdlang.a $?
lib/libsdvm.a: sd/lang/vm/vm.o\
	sd/lang/vm/tab/tab.o
	@echo AR libsdvm.a
	@${AR} ${ARFLAGS} lib/libsdvm.a $?
#TODO:
lib/libsd.so:
	@echo [ .. ] Compiling to 'libsd.so' \(v${SDLANG_MAJOR}.${SDLANG_MINOR}.${SDLANG_PATCH}\)
### END ARCHIVING ###
### BEGIN OPTIONAL ###
tags:
	@echo [ .. ] Updating tags file
	${CTAGS} -R .
### END OPTIONAL ###
.PHONY: tags parser man compiler language docs clean clean-docs help
