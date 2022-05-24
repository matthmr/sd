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

#  define NO_INFO "\n" ///< format field for no-info error
#  define NO_LINEINFO "" ///< format field for no-line-info error

#  define POINT_TO '^' ///< format field for error pointer
#  define EXTEND '~' ///< format field for error pointer extend

// TODO: change this?
/// @brief error time definition
typedef enum time {
	TIME_ARG,
	TIME_TXT,
	TIME_BYTE,
	TIME_COMP,
} Time;

extern const char* errmsg[];

extern char* fmt;
extern char* vfmt;

void Err (int, char*);
void e_set (Time);
#endif
