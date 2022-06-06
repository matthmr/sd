include make/Flags.mk
include make/Targets.mk
-include make/Sources.mk

VERSION:='v0.4.0'

default: install

### BEGIN BASE ###
sources: make/sources.txt
	@echo "[ .. ] Making sources.txt file"
	@CC=${CC} scripts/make-sources.sh
make/sources.txt:
clean:
	@echo "[ .. ] Cleaning working directory"
	@find -type f -name '*.[oa]' | xargs rm -rvf
clean-docs:
	@echo "[ .. ] Cleaning documentation"
	@rm -vrf man/**/*.gz
	@rm -vrf docs/html/*
install: language interpreter compiler man docs src-docs test
	@echo "[ .. ] Stripping symbols off of 'sdread' and 'sdc'"
	@pushd bin
	@${STRIP} sdread
	@${STRIP} sdc
	@popd
	@echo "[ .. ] Symlinking to 'sdread'"
	ln -svf sdread bin/sd
	@echo "[ .. ] Moving the sd language module to '${PREFIX}/bin'"
	@mkdir -v ${PREFIX}/bin 2>/dev/null
	@cp -v bin/sdread bin/sd bin/sdc ${PREFIX}/bin || echo [ !! ] No permission to move binaries to ${PREFIX}/bin
	@echo "[ .. ] Moving the sd language library to '${PREFIX}/lib'"
	mkdir -v ${PREFIX}/lib 2>/dev/null
	@cp -v libsd.so ${PREFIX}/lib || echo [ !! ] No permission to move backend to ${PREFIX}/lib
	@echo "[ .. ] Moving man(1) pages to '${PREFIX}/man/man1'"
	@mkdir -vp ${PREFIX}/man/man1 2>/dev/null
	@cp -vR man/man1/*.1.gz ${PREFIX}/man/man1 || echo [ !! ] No permission to move man pages to ${PREFIX}/man
	@echo "[ .. ] Moving man(3) pages to '${PREFIX}/man/man3'"
	@mkdir -vp ${PREFIX}/man/man3 2>/dev/null
	@cp -vR man/man3/*.3.gz ${PREFIX}/man/man3 || echo [ !! ] No permission to move man pages to ${PREFIX}/man
	@echo "[ OK ] Done!"
help:
	@echo -e "[ targets available ] \n\
	  - interpreter: main interpreter for SD (sdread) \n\
	  - compiler: main compiler for SD (sdc) \n\
	  - language: main library for SD (libsd.so) \n\
	  - man: compresses man pages \n\
	  - install: runs all of the above and moves files to the appropiate locations \n\
	  - clean: cleans working directory (*.o and *.a files) \n\
	  - clean-docs: cleans documentation (*.gz files and files under /docs/html/) \n\
	  - tags: produces tags file for editors that use it \n\
	  - docs: generates and install doxygen html documentation \n\
	  - src-docs: install plain-text source code documentation \n\
	  - help: displays this message \n\
	 \n\
	[ variables available ] \n\
	  - CC: C compiler (${CC}) \n\
	  - C_INCLUDE_PATH: include path (-I${C_INCLUDE_PATH}) \n\
	  - BITS: machine memmory address bit length (e.g 32, 64) (${BITS}) \n\
	  - CFLAGS: CC flags (${CFLAGS}) \n\
	  - AR: archiver (${AR}) \n\
	  - ARFLAGS: archiver flags (${ARFLAGS}) \n\
	  - GZ: gzip compressor (${GZ}) \n\
	  - CTAGS: ctags-like command (${CTAGS}) \n\
	  - PREFIX: prefix for installation (${PREFIX}) \n\
	  - STRIP: strip-like command (${STRIP}) \n\
	 \n\
	[ booleans available ] \n\
	  - DOCS: set to <yes> to install doxygen documentation, otherwise set to <no> (${DOCS}) \n\
	  - SRCDOCS: set to <yes> to install source documentation, otherwise set to <no> (${SRCDOCS}) \n\
	  - TEST: set to <yes> to run test suite, otherwise set to <no> (${TEST})"
### END BASE ###

### BEGIN TARGETS ###
interpreter: ${interpreter-objects} ${interpreter-libraries}
	@echo "[ CC -o sdread ]"
	@${CC} ${CFLAGS} -o bin/sdread $< -Llib -lsdparse -lsdlang -lsdutils -lsdvm
	@echo "[ OK ] Finished compiling interpreter"
compiler: ${compiler-objects} ${compiler-libraries}
	@echo "[ CC -o sdc ]"
	@${CC} ${CFLAGS} -o bin/sdc $< -Llib -lsdparse -lsdlang -lsdutils -lsdvm
	@echo "[ OK ] Finished compiling compiler"
man: man/man1/sdread.1 man/man1/sdc.1
	@echo "[ .. ] Compressing 'sdread' man page"
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz
	@ln -vsf man/man1/sdread.1.gz man/man1/sd.1.gz
	@echo "[ .. ] Compressing 'sdc' man page"
	@${GZ} -c man/man1/sdc.1 > man/man1/sdc.1.gz
language: lib/libsd.so
	@echo "[ TODO ] this is not implemented yet"
### END TARGETS ###

### BEGIN LIBRARIES ###
lib/libsdutils.a: ${libsdutils-objects}
	@echo "[ AR libsdutils.a ]"
	@${AR} ${ARFLAGS} $@ $?
lib/libsdparse.a: ${libsdparse-objects}
	@echo "[ AR libsdparse.a ]"
	@${AR} ${ARFLAGS} $@ $?
lib/libsdlang.a: ${libsdlang-objects}
	@echo "[ AR libsdlang.a ]"
	@${AR} ${ARFLAGS} $@ $?
lib/libsdvm.a: ${libsdvm-objects}
	@echo "[ AR libsdvm.a ]"
	@${AR} ${ARFLAGS} $@ $?
lib/libsd.so:
	@echo "[ .. ] Compiling to 'libsd.so' \(${VERSION}\)"
### END LIBRARIES ###

### BEGIN OPTIONAL ###
tags:
	@echo "[ .. ] Updating tags file"
	@${CTAGS} -R .
docs:
ifeq (${DOCS},yes)
	@echo "[ .. ] Making html documentation with doxygen"
	doxygen
	@echo "[ .. ] Moving html documentation to '${PREFIX}/share/doc/sd'"
	@mkdir -vp ${PREFIX}/share/doc/sd/html 2>/dev/null
	@cp -vR docs/html/* ${PREFIX}/share/doc/sd/html || echo [ !! ] No permission to move documentation to ${PREFIX}/share/doc/sd
else
	@echo "[ .. ] Ignoring html documentation"
endif
src-docs:
ifeq (${SRCDOCS},yes)
	@echo "[ .. ] Moving source code documentation to '${PREFIX}/share/doc/sd'"
	@mkdir -vp ${PREFIX}/share/doc/sd/txt 2>/dev/null
	@cp -vR docs/txt/* ${PREFIX}/share/doc/sd/txt || echo [ !! ] No permission to move source code documentation to ${PREFIX}/share/doc/sd/txt
else
	@echo "[ .. ] Ignoring source code documentation"
endif
test:
ifeq (${TEST},yes)
	@echo "[ TODO ] this is not implemented yet"
else
	@echo "[ TODO ] this is not implemented yet"
endif
### END OPTIONAL ###

.PHONY: tags interpreter man compiler language docs src-docs clean clean-docs help test sources
