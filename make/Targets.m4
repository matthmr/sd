include(make/m4/targets.m4)dnl
dnl BEGIN interpreter
target(`interpreter')dnl
target_bin(`bin/sdread')dnl
target_obj(`sd/intr/exec/sdread.o')dnl
target_lib(`sdparse', `sdutils', `sdlang', `sdvm', `sddata')dnl
target_gen
dnl END interpreter
dnl
dnl BEGIN compiler
target(`compiler')dnl
target_bin(`bin/sdc')
target_obj(`sd/comp/sdc.o')dnl
target_lib(`sdparse', `sdutils', `sdlang', `sdvm', `sddata')dnl
target_gen
dnl END compiler
dnl
dnl BEGIN LIBRARIES
library(`sdparse')dnl
library_obj(
`sd/lang/hooks/txt/txthooks.o',
`sd/lang/expr/drivers/drivers.o',
`sd/intr/bytecode/sdbcparse.o',
`sd/lang/hooks/txt/kwhooks.o',
`sd/lang/hooks/txt/literal.o',
`sd/lang/hooks/txt/thooks.o',
`sd/intr/txt/ptree/ptree.o',
`sd/intr/txt/sdparse.o'
)dnl
library_gen
dnl
library(`sdlang')dnl
library_obj(
`sd/lang/expr/expr.o',
`sd/intr/txt/ptree/op/precedence.o',
`sd/lang/obj/ot.o'
)dnl
library_gen
dnl
library(`sdutils')dnl
library_obj(
`sd/intr/txt/utils/txtutils.o',
`sd/utils/err/err.o'
)dnl
library_gen
dnl
library(`sdvm')dnl
library_obj(
`sd/lang/vm/vm.o',
`sd/lang/vm/tab/tab.o'
)dnl
library_gen
dnl
library(`sddata')
library_obj(
`sd/lang/tokens/txt.o',
`sd/lang/tokens/virtual/kw/kwcomp.o',
)dnl
library_gen
dnl
library(`sd')dnl <- TODO
library_obj(`')dnl    <- TODO
library_gen
dnl
dnl END LIRARIES
dnl
