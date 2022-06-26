/**
 * @file err.h
 *
 * @brief standard error formatting
 *
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#ifndef LOCK_ERR
#  define LOCK_ERR ///< lock: standard lock

#  define POINT '^' ///< @brief format field for error pointer
#  define EXTEND '~' ///<  @brief format field for error pointer extend

/// @brief error identifier
/// @note at parse/execution level,
///       errors can double as exit
///       code, so they start as 1
///       in the enum
enum err {
	EDRIVCAST=1, // driver cast
	EBADINT, // bad integer constr
	EOOBID, // out-of-bound-identifier length
	EOOBN, // out-of-bound number
	EUNDEFID, // undefined identifier
	EKWID, // keyword as identifier
	EUNHOID, // unhookable identifier
	EMISSMATCH, // missing matcher
	EUNHOL, // unhookable literal
};

struct file_info {
	char* filename;
	char* line;
	char* column;
};

struct error_info {
	char* line;
	char* ptr;
};

typedef struct file_info FInfo;
typedef struct error_info EInfo;

extern const char* errmsg[];

void Err (int, FInfo, EInfo);
#endif
