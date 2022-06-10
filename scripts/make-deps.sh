#!/usr/bin/env bash
case $1 in
	'-h'|'--help')
		printf 'Usage:       scripts/make-deps.sh
Description: Makes generic make targets for GNU make
Variables:   CC="C compiler"
Note:        Make sure to call this script from the repository root
'
		exit 1
		;;
esac

[[ ! -f make/sources/sd-sources.txt ]] && {
	echo "[ !! ] No \`sd-sources.txt' file found. Did you run \`make-sources.sh'?"
	exit 1
}
[[ -z $CC ]] && CC=cc

echo '[ .. ] Making dependencies'

echo "[ INFO ] CC=$CC"

cache=make/Sources.mk.m4.in
if [[ -f $cache ]]
then
	printf ''>$cache
else
	touch $cache
fi

while read src
do
	echo "[ CC -MM $src ]"
	$CC -I. -MM $src >>$cache
done < make/sources/sd-sources.txt

echo '[ OK ] Done'
