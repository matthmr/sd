/**
 * @file kwid.h
 *
 * @brief generic virtual keyword id
 *
 * This file contains generic virtual
 * keyword identification, meant to be
 * included by whatever file uses
 * virtual keywords
 */

#ifndef LOCK_VKWID ///< lock: standard lock
#  define LOCK_VKWID

/// @brief virtual keyword definition
enum vkwid {

	// these types can be suffixed or prefixed
	_CHAR,
	_SHORT,
	_INT,
	_LONG,
	_FLOAT,
	_DOUBLE,

	// these mask the types before, except for
	// float-like types
	__UNSIGNED,
	__SIGNED,

};

typedef enum vkwid vkwid;

//extern const char kwprefix[];

#endif
