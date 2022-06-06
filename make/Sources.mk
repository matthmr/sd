sd/lib/std/std.o: sd/lib/std/std.c
	@echo "[ CC sd/lib/std/std.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/txt.o: sd/lang/tokens/txt.c sd/lang/tokens/gen/txtmaps.hsd/lang/core/statement.h sd/utils/types/shared.h sd/intr/limits.hsd/lang/tokens/groups.h sd/intr/txt/tokens/form.hsd/lang/tokens/interface/vti.h sd/utils/utils.h
	@echo "[ CC sd/lang/tokens/txt.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/virtual/comp.o: sd/lang/tokens/virtual/comp.c sd/lang/tokens/virtual/gen/id.hsd/lang/tokens/interface/vti.h sd/lang/tokens/groups.h sd/utils/utils.hsd/lang/tokens/gen/txtmaps.h sd/lang/tokens/virtual/comp.h
	@echo "[ CC sd/lang/tokens/virtual/comp.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/virtual/mask.o: sd/lang/tokens/virtual/mask.c sd/lang/tokens/interface/vti.hsd/lang/tokens/groups.h sd/utils/utils.h sd/lang/tokens/virtual/mask.hsd/lang/tokens/virtual/gen/id.h sd/lang/tokens/gen/txtmaps.h
	@echo "[ CC sd/lang/tokens/virtual/mask.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/virtual/vt.o: sd/lang/tokens/virtual/vt.c sd/lang/tokens/virtual/vt.hsd/lang/tokens/virtual/gen/id.h sd/lang/tokens/interface/vti.hsd/lang/tokens/groups.h sd/utils/utils.h sd/lang/tokens/gen/txtmaps.hsd/lang/tokens/virtual/match.h sd/lang/tokens/virtual/comp.hsd/lang/tokens/virtual/mask.h
	@echo "[ CC sd/lang/tokens/virtual/vt.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/virtual/match.o: sd/lang/tokens/virtual/match.c sd/lang/tokens/virtual/gen/id.hsd/lang/tokens/interface/vti.h sd/lang/tokens/groups.h sd/utils/utils.hsd/lang/tokens/gen/txtmaps.h sd/lang/tokens/virtual/match.h
	@echo "[ CC sd/lang/tokens/virtual/match.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/tokens/ctxt/sfix.o: sd/lang/tokens/ctxt/sfix.c
	@echo "[ CC sd/lang/tokens/ctxt/sfix.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/callback/vmcb.o: sd/lang/callback/vmcb.c sd/lang/callback/vmcb.h
	@echo "[ CC sd/lang/callback/vmcb.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/uword/umaps.o: sd/lang/uword/umaps.c sd/utils/types/shared.h sd/intr/limits.h
	@echo "[ CC sd/lang/uword/umaps.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/uword/utils/uutils.o: sd/lang/uword/utils/uutils.c
	@echo "[ CC sd/lang/uword/utils/uutils.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/uword/utils/txt/utxtutils.o: sd/lang/uword/utils/txt/utxtutils.c
	@echo "[ CC sd/lang/uword/utils/txt/utxtutils.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/hooks/txt/thooks.o: sd/lang/hooks/txt/thooks.c sd/lang/hooks/txt/txthooks.hsd/lang/tokens/groups.h sd/intr/txt/tokens/form.hsd/lang/tokens/interface/vti.h sd/utils/utils.hsd/lang/tokens/gen/txtmaps.h sd/utils/types/shared.h sd/intr/limits.hsd/lang/expr/expr.h sd/lang/vm/vm.h sd/intr/txt/ptree/ptree.hsd/lang/expr/drivers/drivers.h sd/intr/txt/sdparse.h sd/utils/err/verr.hsd/utils/err/err.h
	@echo "[ CC sd/lang/hooks/txt/thooks.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/hooks/txt/kwhooks.o: sd/lang/hooks/txt/kwhooks.c sd/lang/tokens/gen/txtmaps.hsd/lang/hooks/txt/txthooks.h sd/lang/tokens/groups.hsd/intr/txt/tokens/form.h sd/lang/tokens/interface/vti.hsd/utils/utils.h sd/utils/types/shared.h sd/intr/limits.hsd/utils/err/verr.h sd/utils/err/err.h sd/intr/txt/ptree/ptree.hsd/lang/expr/drivers/drivers.h sd/lang/expr/expr.h sd/lang/vm/vm.hsd/intr/txt/sdparse.h
	@echo "[ CC sd/lang/hooks/txt/kwhooks.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/hooks/txt/literal.o: sd/lang/hooks/txt/literal.c sd/intr/txt/ptree/ptree.hsd/lang/expr/drivers/drivers.h sd/lang/expr/expr.hsd/utils/types/shared.h sd/intr/limits.h sd/lang/vm/vm.hsd/utils/utils.h sd/lang/hooks/txt/txthooks.h sd/lang/tokens/groups.hsd/intr/txt/tokens/form.h sd/lang/tokens/interface/vti.hsd/lang/tokens/gen/txtmaps.h sd/lang/hooks/txt/literal.hsd/utils/err/verr.h sd/utils/err/err.h
	@echo "[ CC sd/lang/hooks/txt/literal.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/hooks/txt/txthooks.o: sd/lang/hooks/txt/txthooks.c sd/lang/tokens/gen/txtmaps.hsd/lang/hooks/txt/txthooks.h sd/lang/tokens/groups.hsd/intr/txt/tokens/form.h sd/lang/tokens/interface/vti.hsd/utils/utils.h sd/utils/types/shared.h sd/intr/limits.hsd/lang/vm/vm.h
	@echo "[ CC sd/lang/hooks/txt/txthooks.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/hooks/bytecode/bchooks.o: sd/lang/hooks/bytecode/bchooks.c
	@echo "[ CC sd/lang/hooks/bytecode/bchooks.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/obj/ot.o: sd/lang/obj/ot.c sd/utils/types/shared.h sd/intr/limits.hsd/utils/types/cast.h sd/lang/tokens/groups.h sd/lang/obj/ot.h
	@echo "[ CC sd/lang/obj/ot.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/vm/vm.o: sd/lang/vm/vm.c sd/intr/limits.h sd/utils/types/shared.hsd/utils/utils.h sd/utils/types/cast.h sd/lang/vm/tab/tab.hsd/lang/expr/expr.h sd/lang/vm/vm.h
	@echo "[ CC sd/lang/vm/vm.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c -DADDR_BITS=64 ${CFLAGS} $< -o $@
sd/lang/vm/tab/tab.o: sd/lang/vm/tab/tab.c sd/utils/types/shared.h sd/intr/limits.hsd/lang/core/bitmap/bitmap.h sd/lang/vm/tab/tab.h sd/lang/vm/vm.hsd/utils/utils.h
	@echo "[ CC sd/lang/vm/tab/tab.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/expr/drivers/drivers.o: sd/lang/expr/drivers/drivers.c sd/lang/expr/drivers/drivers.hsd/lang/expr/expr.h sd/utils/types/shared.h sd/intr/limits.hsd/lang/vm/vm.h sd/utils/utils.h sd/lang/tokens/gen/txtmaps.h
	@echo "[ CC sd/lang/expr/drivers/drivers.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/expr/drivers/template.o: sd/lang/expr/drivers/template.c
	@echo "[ CC sd/lang/expr/drivers/template.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/expr/expr.o: sd/lang/expr/expr.c sd/lang/core/bitmap/masks.hsd/utils/types/shared.h sd/intr/limits.h sd/lang/expr/expr.hsd/lang/vm/vm.h sd/utils/utils.h sd/lang/vm/tab/tab.h
	@echo "[ CC sd/lang/expr/expr.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/lang/atom/atom.o: sd/lang/atom/atom.c sd/utils/types/shared.h sd/intr/limits.hsd/lang/atom/atom.h sd/lang/vm/vm.h sd/utils/utils.h
	@echo "[ CC sd/lang/atom/atom.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/intr/txt/sdparse.o: sd/intr/txt/sdparse.c sd/utils/types/shared.h sd/intr/limits.hsd/utils/err/verr.h sd/utils/err/err.h sd/utils/utils.hsd/lang/hooks/txt/txthooks.h sd/lang/tokens/groups.hsd/intr/txt/tokens/form.h sd/lang/tokens/interface/vti.hsd/lang/tokens/gen/txtmaps.h sd/lang/hooks/txt/literal.hsd/lang/uword/umaps.h sd/lang/tokens/txt.h sd/lang/obj/ot.hsd/lang/vm/vm.h sd/intr/txt/utils/txtutils.h sd/intr/txt/ptree/ptree.hsd/lang/expr/drivers/drivers.h sd/lang/expr/expr.h sd/intr/txt/sdparse.hsd/intr/exec/sdread.h
	@echo "[ CC sd/intr/txt/sdparse.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c -DADDR_BITS=64 ${CFLAGS} $< -o $@
sd/intr/txt/utils/txtutils.o: sd/intr/txt/utils/txtutils.c sd/intr/txt/utils/txtutils.hsd/utils/types/shared.h sd/intr/limits.h sd/lang/tokens/groups.hsd/utils/err/verr.h sd/utils/err/err.h sd/utils/utils.hsd/lang/hooks/txt/txthooks.h sd/intr/txt/tokens/form.hsd/lang/tokens/interface/vti.h sd/lang/tokens/gen/txtmaps.hsd/lang/core/statement.h sd/lang/tokens/txt.h
	@echo "[ CC sd/intr/txt/utils/txtutils.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/intr/txt/ptree/op/precedence.o: sd/intr/txt/ptree/op/precedence.csd/intr/txt/ptree/op/precedence.h sd/utils/types/shared.hsd/intr/limits.h sd/lang/expr/expr.h sd/lang/vm/vm.h sd/utils/utils.h
	@echo "[ CC sd/intr/txt/ptree/op/precedence.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c -DADDR_BITS=64 ${CFLAGS} $< -o $@
sd/intr/txt/ptree/ptree.o: sd/intr/txt/ptree/ptree.c sd/lang/expr/drivers/drivers.hsd/lang/expr/expr.h sd/utils/types/shared.h sd/intr/limits.hsd/lang/vm/vm.h sd/utils/utils.h sd/lang/tokens/gen/txtmaps.hsd/lang/hooks/txt/txthooks.h sd/lang/tokens/groups.hsd/intr/txt/tokens/form.h sd/lang/tokens/interface/vti.hsd/intr/txt/ptree/op/precedence.h sd/intr/txt/ptree/ptree.h
	@echo "[ CC sd/intr/txt/ptree/ptree.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/intr/bytecode/sdbcparse.o: sd/intr/bytecode/sdbcparse.c sd/intr/bytecode/sdbcparse.hsd/utils/types/shared.h sd/intr/limits.h sd/utils/err/err.h
	@echo "[ CC sd/intr/bytecode/sdbcparse.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/intr/exec/sdread.o: sd/intr/exec/sdread.c sd/lang/callback/vmcb.h sd/lang/obj/ot.hsd/utils/types/shared.h sd/intr/limits.h sd/lang/tokens/groups.hsd/lang/vm/vm.h sd/utils/utils.h sd/intr/bytecode/sdbcparse.hsd/intr/txt/ptree/ptree.h sd/lang/expr/drivers/drivers.hsd/lang/expr/expr.h sd/intr/txt/sdparse.h sd/utils/err/err.hsd/intr/exec/sdread.h
	@echo "[ CC sd/intr/exec/sdread.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/utils/err/verr.o: sd/utils/err/verr.c sd/lang/tokens/gen/txtmaps.hsd/utils/verbose/colors.h sd/utils/types/shared.h sd/intr/limits.hsd/utils/err/verr.h sd/utils/err/err.h
	@echo "[ CC sd/utils/err/verr.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/utils/err/err.o: sd/utils/err/err.c sd/utils/err/err.h sd/utils/utils.h
	@echo "[ CC sd/utils/err/err.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/utils/utils.o: sd/utils/utils.c sd/utils/utils.h
	@echo "[ CC sd/utils/utils.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/comp/sdc.o: sd/comp/sdc.c sd/utils/types/shared.h sd/intr/limits.hsd/utils/err/err.h sd/utils/utils.h sd/comp/sdc.h
	@echo "[ CC sd/comp/sdc.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@
sd/api/api.o: sd/api/api.c
	@echo "[ CC sd/api/api.o ]"
	@${CC} -I${C_INCLUDE_PATH} -c  ${CFLAGS} $< -o $@

