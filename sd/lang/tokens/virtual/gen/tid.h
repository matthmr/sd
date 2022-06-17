/**
 * @file tid.h
 *
 * @brief generic virtual token id
 *
 * This file contains generic virtual
 * token identification, meant to be
 * included by whatever file uses
 * virtual tokens
 */

#ifndef LOCK_VTID ///< lock: standard lock
#  define LOCK_VTID

#  include <sd/lang/tokens/interface/vti.h>
#  include <sd/lang/tokens/gen/txtmaps.h>
#  include <sd/lang/tokens/groups.h>

#  define vtid_append(x) _TID_BOUND+x

// TODO: the macros shbang
/// @brief virtual token definition
enum vtid {

	/* `ttoken`-defined direct compounds:
	 *    <<, >>,        (bitwise)
	 *    //, %%,        (math)
	 *    $$, $(), $<>$, (macros (compiled only))
	 *    ..,            (object)
	 *    ++, --,        (unary)
	 *    &&, ||, ^^,    (boolean)
	 *    ??, !!, ::     (inlined)
	 */
	_BIT_LS = vtid_append (0x0001),
	_BIT_RS = vtid_append (0x0002),
	_MATH_DIV = vtid_append (0x0003),
	_MATH_MOD = vtid_append (0x0004),
	_MACRO_LIT = vtid_append (0x0005),
	_MACRO_FN = vtid_append (0x0006),
	_MACRO_SYN = vtid_append (0x0007),
	_OBJ_PARENT = vtid_append (0x0008),
	_MATH_INC = vtid_append (0x0009),
	_MATH_DEC = vtid_append (0x000a),
	_BOOL_AND = vtid_append (0x000b),
	_BOOL_OR = vtid_append (0x000c),
	_BIT_XOR = vtid_append (0x000d),
	_WHILE = vtid_append (0x000e),
	_IN_WHILE = vtid_append (0x000f),
	_IN_IF = vtid_append (0x0010),
	_IN_ASSIGN = vtid_append (0x0011),

	/* `ttoken`-defined indirect compounds:
	 *    <=, >=, !=,     (boolean)
	 *    +:, -:, *:,     (assign)
	 *    |:, &:
	 */
	_BOOL_LTEQ = vtid_append (0x0012),
	_BOOL_GTEQ = vtid_append (0x0013),
	_BOOL_NEQ = vtid_append (0x0014),
	_ASSIGN_PLUS = vtid_append (0x0015),
	_ASSIGN_MINUS = vtid_append (0x0016),
	_ASSIGN_TIMES = vtid_append (0x0017),
	_ASSIGN_BWOR = vtid_append (0x0018),
	_ASSIGN_BWAND = vtid_append (0x0019),

	/* `comp`-defined indirect compounds:
	 *    (assign)
	 *    %%:, //:,
	 *    &&:, ||:, ^|:
	 *    ^^:, >>:, <<:,
	 */
	_ASSIGN_MOD = vtid_append (0x0020),
	_ASSIGN_AND = vtid_append (0x0021),
	_ASSIGN_OR = vtid_append (0x0022),
	_ASSIGN_DIV = vtid_append (0x0023),
	_ASSIGN_BWXOR = vtid_append (0x0024),
	_ASSIGN_BWRS = vtid_append (0x0025),
	_ASSIGN_BWLS = vtid_append (0x0026),

	/* mask:
	 *    <, >, (array)
	 *    <, >, (module)
	 *    +, -  (unary)
	 */
	_ARR_BEGIN = vtid_append (0x0027),
	_ARR_END = vtid_append (0x0028),
	_MOD_BEGIN = vtid_append (0x0029),
	_MOD_END = vtid_append (0x002a),
	_MATH_UPLUS = vtid_append (0x002b),
	_MATH_UMINUS = vtid_append (0x002c),

};

typedef enum vtid Vtid;

#endif
