# Made by mH (https://github.com/matthmr)

### COMPILER ###
CC?=clang12
CCFLAG?=

### ARCHIVER ###
AR?=ar
ARFLAG?=rcs

### GUNZIP ###
GZ=gzip

### INSTALLATION ###
PREFIX?=/usr/local

### BEGIN BASE ###
default: install

clean:
	@echo \[ .. \] Cleaning working directory
	@rm -rf *.a *.o **/*.a **/*.o man/**/*.gz && echo \[ OK \] Done!

install: language parser binary-parser compiler linker man
	@echo \[ .. \] Moving the sd language module to '${PREFIX}/bin'
	@mv sdread sdcomp sdexec sdlink ${PREFIX}/bin || echo \[ \!\! \] No permission to move binaries to ${PREFIX}/bin.
	@echo \[ .. \] Moving the sd language libraries to '${PREFIX}/lib'
	@mv libsdlang.so ${PREFIX}/lib || echo \[ \!\! \] No permission to move backend to ${PREFIX}/lib.
	@echo \[ .. \] Moving man pages to '${PREFIX}/man'
	@mkdir -p ${PREFIX}/man/man1/ && mv man/* ${PREFIX}/man/man1 || echo \[ \!\! \] No permission to move backend to ${PREFIX}/man.
### END BASE ###

### BEGIN COMPILING ###
parser: intr/limits.h utils/utils.o sdparse.o sdread.o\
	language parser-static
	@echo [ .. ] Linking to 'sdread'
	@${CC} utils/utils.o sdparse.o sdread.o -o sdread && echo [ OK ] Done!

man: man/man1/sdread.1
	@echo [ .. ] Compressing \'sdread\' man page
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz && echo [ OK ] Done!

binary-parser:

compiler:

language:

linker:

sdread.o: utils/utils.h utils/sharedtypes.h sdread.c
	@echo [ .. ] Compiling 'sdread.o'
	@${CC} -c ${CCFLAG} sdread.c -o sdread.o && echo [ OK ] Done!

sdparse.o: utils/sharedtypes.h utils/utils.h lang/tokens.h sdparse.c sdparse.h
	@echo [ .. ] Compiling 'sdparse.o'
	@${CC} -c ${CCFLAG} sdparse.c -o sdparse.o && echo [ OK ] Done!

utils/utils.o: utils/utils.c utils/utils.h utils/sharedtypes.h
	@echo [ .. ] Compiling 'utils.o'
	@${CC} -c ${CCFLAG} utils/utils.c -o utils/utils.o && echo [ OK ] Done!
### END COMPILING ###

### BEGIN ARCHIVING ###
parser-static: utils/utils.o sdparse.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	@${AR} ${ARFLAG} libsdparse.a $? && echo [ OK ] Done!
### END ARCHIVING ###

tags:
	@echo [ .. ] Updating tags file
	@ctags -R . && echo [ OK ] Done!

.PHONY: tags
