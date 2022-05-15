/**
 * @file id.h
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

#  include <sd/lang/tokens/gen/txtmaps.h>
#  define vtid_append(x) _TID_BOUND+x

// TODO: maybe the idea of macros doesn't work in the SD paradigm?
/// @brief virtual token definition
enum vtid {

	/* compound:
	 *    <<, >>, //, $$, $(), $<>$,
	 *    .., ^^, ++, --, !!, ??, &&,
	 *    ||, %%
	 */
	_BIT_LS = vtid_append (0x0001),
	_BIT_RS = vtid_append (0x0002),
	_MATH_DIV = vtid_append (0x0003),
	_MACRO_LIT = vtid_append (0x0004),
	_MACRO_FN = vtid_append (0x0005),
	_MACRO_SYN = vtid_append (0x0006),
	_OBJ_PARENT = vtid_append (0x0007),
	_BIT_XOR = vtid_append (0x0008),
	_MATH_INC = vtid_append (0x0009),
	_MATH_DEC = vtid_append (0x000a),
	_WHILE_TRUE = vtid_append (0x000b),
	_IF_TRUE = vtid_append (0x000c),
	_BOOL_AND = vtid_append (0x000d),
	_BOOL_OR = vtid_append (0x000e),
	_MATH_MOD = vtid_append (0x000f),

	/* mask:
	 *    <, >, +, -, !
	 */
	_BOOL_LT = vtid_append (0x0010),
	_BOOL_GT = vtid_append (0x0011),
	_MATH_UPLUS = vtid_append (0x0012),
	_MATH_UMINUS = vtid_append (0x0013),
	_WHILE = vtid_append (0x0014),

	/* `ttoken`-defined indirect compounds:
	 *    <=, >=, !=, +:, -:, |:, *:,
	 *    !:, &:, ~:, =:
	 */
	_MATH_LTEQ = vtid_append (0x0015),
	_MATH_GTEQ = vtid_append (0x0016),
	_MATH_NEQ = vtid_append (0x0017),
	_ASSIGN_PLUS = vtid_append (0x0018),
	_ASSIGN_MINUS = vtid_append (0x0019),
	_ASSIGN_BWOR = vtid_append (0x0020),
	_ASSIGN_TIMES = vtid_append (0x0021),
	_ASSIGN_NOT = vtid_append (0x0022),
	_ASSIGN_BWAND = vtid_append (0x0023),
	_ASSIGN_BWNOT = vtid_append (0x0024),
	_ASSIGN_EQ = vtid_append (0x0025),

	/* `comp`-defined indirect compounds:
	 *    %%:, &&:, ||:, //:, ^^:, >>:,
	 *    <<:, <=:, >=:, !=:
	 */
	_ASSIGN_MOD = vtid_append (0x0026),
	_ASSIGN_AND = vtid_append (0x0027),
	_ASSIGN_OR = vtid_append (0x0028),
	_ASSIGN_DIV = vtid_append (0x0029),
	_ASSIGN_BWXOR = vtid_append (0x002a),
	_ASSIGN_BWRS = vtid_append (0x002b),
	_ASSIGN_BWLS = vtid_append (0x002c),
	_ASSIGN_LTEQ = vtid_append (0x002d),
	_ASSIGN_GTEQ = vtid_append (0x002e),
	_ASSIGN_NEQ = vtid_append (0x002f),

};

const unsigned short tdef_comp = _ASSIGN_PLUS;
const unsigned short cdef_comp = _ASSIGN_MOD;

#endif
