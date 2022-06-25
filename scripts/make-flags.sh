#!/usr/bin/env bash
case $1 in
	'-h'|'--help')
		printf 'Usage:       scripts/make-defaults.sh
Description: Makes defaults for the SD build
Variables:   M4="m4-like command"
             M4FLAGS="m4 flags"
Note:        Make sure to call this script from the repository root
'
		exit 1
		;;
esac

[[ -z $M4 ]] && M4=m4

echo "[ INFO ] M4=$M4"
echo "[ INFO ] M4FLAGS=$M4FLAGS"

echo "[ .. ] Applying configuration flags to build"
eval "$M4 $M4FLAGS make/Flags.m4" > make/Flags.mk
# an `eval' is needed because of the quotes inside the arguments of some
# of the macros

echo "[ OK ] Done"
