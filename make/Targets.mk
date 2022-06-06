interpreter-objects=sd/intr/txt/sdparse.o
interpreter-libraries=lib/libsdparse.a \
	lib/libsdutils.a \
	lib/libsdlang.a \
	lib/libsdvm.a

compiler-objects=sd/comp/sdc.o
compiler-libraries=lib/libsdparse.a \
	lib/libsdutils.a \
	lib/libsdlang.a \
	lib/libsdvm.a

libsdutils-objects= sd/utils/utils.o \
	sd/intr/txt/utils/txtutils.o \
	sd/utils/err/verr.o \
	sd/utils/err/err.o
libsdparse-objects= sd/lang/hooks/txt/txthooks.o \
	sd/intr/txt/ptree/op/precedence.o \
	sd/lang/expr/drivers/drivers.o \
	sd/intr/bytecode/sdbcparse.o \
	sd/lang/hooks/txt/kwhooks.o \
	sd/lang/hooks/txt/thooks.o \
	sd/intr/txt/ptree/ptree.o \
	sd/intr/txt/sdparse.o
libsdlang-objects= sd/lang/hooks/txt/literal.o \
	sd/lang/tokens/virtual/match.o \
	sd/lang/tokens/virtual/comp.o \
	sd/lang/tokens/virtual/mask.o \
	sd/lang/tokens/virtual/vt.o \
	sd/lang/tokens/txt.o \
	sd/lang/expr/expr.o \
	sd/lang/obj/ot.o
libsdvm-objects= sd/lang/vm/vm.o \
	sd/lang/vm/tab/tab.o
libsd-objects=
