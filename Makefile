# Made by mH (https://github.com/matthmr)

### COMPILER ###
CC?=clang # TODO: change to gcc
CCFLAG?=

### ARCHIVER ###
AR?=ar
ARFLAG?=rcs

### GUNZIP ###
GZ?=gzip

### INSTALLATION ###
PREFIX?=/usr/local

### BEGIN BASE ###
default: install

clean:
	@echo \[ .. \] Cleaning working directory
	@printf '' > error.log
	@rm -rf intr/**/*.o intr/**/*.a utils/*.o utils/**/*.o man/**/*.gz

install: log-clean language parser binary-parser compiler linker man
	@echo \[ .. \] Moving the sd language module to '${PREFIX}/bin'
	@mv sdread sdcomp sdexec sdlink ${PREFIX}/bin || echo \[ \!\! \] No permission to move binaries to ${PREFIX}/bin.
	@echo \[ .. \] Moving the sd language libraries to '${PREFIX}/lib'
	@mv libsdlang.so ${PREFIX}/lib || echo \[ \!\! \] No permission to move backend to ${PREFIX}/lib.
	@echo \[ .. \] Moving man pages to '${PREFIX}/man'
	@mkdir -p ${PREFIX}/man/man1/ && mv man/* ${PREFIX}/man/man1 || echo \[ \!\! \] No permission to move backend to ${PREFIX}/man.

log-clean:
	@echo \[ .. \] Cleaning log file
	@printf '' > error.log
### END BASE ###

### BEGIN COMPILING ###
parser: log-clean\
	sdread\
	intr/limits.h utils/utils.o intr/txt/sdparse.o intr/exec/sdread.o intr/libsdparse.a\
	language
	@echo [ .. ] Linking to 'sdread'
	@${CC} intr/libsdparse.a intr/exec/sdread.o -o sdread 2>>error.log

man: man/man1/sdread.1
	@echo [ .. ] Compressing 'sdread' man page
	@${GZ} -c man/man1/sdread.1 > man/man1/sdread.1.gz

### TODO ###
binary-parser:

compiler:

language:

linker:
### TODO ###

intr/exec/sdread.o: utils/utils.h utils/sharedtypes.h intr/exec/sdread.c
	@echo [ .. ] Compiling 'sdread.o'
	@${CC} -c ${CCFLAG} intr/exec/sdread.c -o intr/exec/sdread.o 2>>error.log

intr/txt/sdparse.o: utils/sharedtypes.h utils/utils.h\
	intr/txt/sdparse.c intr/txt/sdparse.h\
	intr/txt/utils/txtutils.h\
	lang/tokens.h
	@echo [ .. ] Compiling 'sdparse.o'
	@${CC} -c ${CCFLAG} intr/txt/sdparse.c -o intr/txt/sdparse.o 2>>error.log

intr/txt/utils/txtutils.o: intr/txt/utils/txtutils.c intr/txt/utils/txtutils.h
	@echo [ .. ] Compiling 'txtutils.o'
	@${CC} -c ${CCFLAG} intr/txt/utils/txtutils.c -o intr/txt/utils/txtutils.o 2>>error.log

utils/utils.o: utils/utils.c utils/utils.h utils/sharedtypes.h
	@echo [ .. ] Compiling 'utils.o'
	@${CC} -c ${CCFLAG} utils/utils.c -o utils/utils.o 2>>error.log
### END COMPILING ###

### BEGIN ARCHIVING ###
intr/libsdparse.a: utils/utils.o intr/txt/sdparse.o intr/txt/utils/txtutils.o
	@echo [ .. ] Archiving to 'libsdparse.a'
	@${AR} ${ARFLAG} intr/libsdparse.a $? 2>>error.log
### END ARCHIVING ###

### BEGIN OPTIONAL ###
tags:
	@echo [ .. ] Updating tags file
	@ctags -R .
### END OPTIONAL ###
