#!/usr/bin/env bash
case $1 in
	'-h'|'--help')
		printf 'Usage:       scripts/make-deps-makefile.sh
Description: Adds target commands to the output of make-deps.sh
Variables:   SED="sed-like command"
             M4="m4-like command"
Note:        Make sure to call this script from the repository root
'
		exit 1
		;;
esac

[[ ! -f make/sources/sd.txt ]] && {
	echo "[ !! ] No \`sd.txt' file found. Did you run \`make-sources.sh'?"
	exit 1
}
[[ -z $SED ]] && SED=sed
[[ -z $M4 ]] && M4=m4

echo "[ INFO ] SED=$SED"
echo "[ INFO ] M4=$M4"

echo "[ .. ] Flattening target output"
$SED -E 's/.*\.o: (.*)\.c/\1.o: \1.c/g' make/Sources.mk.m4.in |\
$SED -z 's/ \\\n//g' > make/Sources.mk.m4

echo "[ .. ] Setting up make template"
$SED -Ei 's/((.*?\/(.*?)\.o): .*)$/\0\n\t@echo "[ CC \2 ]"\n\t@${CC} -I${C_INCLUDE_PATH} -c M4FLAG_mk_\3 ${CFLAGS} $< -o $@/g' make/Sources.mk.m4

echo "[ .. ] Applying preprocessor flags from \`make/Flags.m4'"
$M4 make/Sources.m4 | $SED -E 's/M4FLAG_mk_[A-Za-z]* / /g' > make/Sources.mk

echo "[ OK ] Done"
