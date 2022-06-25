#!/usr/bin/env bash
case $1 in
	'-h'|'--help')
		printf 'Usage:       scripts/make-targets.sh
Description: Generates a list of targets to compile (SD)
Variables:   M4="m4-like command"
Note:        Make sure to call this script from the repository root
'
		exit 1
		;;
esac

[[ -z $M4 ]] && M4=m4

echo "[ INFO ] M4=$M4"

echo "[ .. ] Setting up make template for targets"
$M4 make/Targets.m4 > make/Targets.mk

echo "[ OK ] Done"
