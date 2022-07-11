s/((.*?\/(.*?)\.o): .*)$/\0\n\t@echo "[ CC \2 ]"\n\t@${CC} -I${C_INCLUDE_PATH} -c M4FLAG_mk_\3 ${CFLAGS} $< -o $@/g
