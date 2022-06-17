define(`librec', `ifelse($1, `', ,`lib/lib$1.a librec(shift($@))')')dnl
define(`libsorec', `ifelse($1, `', ,`-l$1 libsorec(shift($@))')')dnl
define(`rec', `ifelse($1, `', ,`$1 rec(shift($@))')')dnl
dnl
dnl
define(`target_lib', `dnl
__target__`-libraries':= librec($@)
__target__`-libraries-soname':= libsorec($@)
')dnl
define(`target_obj', `dnl
__target__`-objects':= rec($@)
')dnl
define(`target', `define(`__target__', `$1')')dnl
define(`target_bin', `define(`__target_bin__', `$1')')dnl
define(`target_gen', `dnl
__target__: ${__target__`-objects'} ${__target__`-libraries'}
	@echo "[ CC -o __target_bin__ ]"
	${CC} ${CFLAGS} ${__target__`-objects'} -o __target_bin__ -Llib ${__target__`-libraries-soname'}
	@echo "[ OK ] Finish compiling __target__"
')dnl
dnl
dnl
define(`library_obj', `dnl
`lib'__library__`-objects':= rec($@)
')dnl
define(`library', `define(`__library__', `$1')')dnl
define(`library_gen', `dnl
`lib/lib'__library__`.a': ${`lib'__library__`-objects'}
	@echo "[ AR `lib/lib'__library__`.a' ]"
	@${AR} ${ARFLAGS} $`@' $?
')dnl
