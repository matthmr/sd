#!/usr/bin/env bash
case $1 in
	'-h'|'--help')
		printf 'Usage:       scripts/make-sources.sh
Description: Generates a list of source files to compile (SD)
Variables:   FIND="find-like command"
Note:        Make sure to call this script from the repository root
'
		exit 1
		;;
esac

[[ -z $FIND ]] && FIND=find

echo '[ .. ] Finding C sources'
echo "[ INFO ] FIND=$FIND"

{
	$FIND sd arg utils -type f -name '*.c' > make/sources/sd-sources.txt
} && {
	echo '[ OK ] Done. Saved to make/sources/sd-sources.txt'
} || {
	echo "[ !! ] Could not run \`find' command"
	exit 1
}
exit 0
