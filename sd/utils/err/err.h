/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#ifndef LOCK_ERR
#  define LOCK_ERR

#  define NO_INFO "\n"
#  define NO_LINEINFO ""

#  define POINT_TO '^'
#  define EXTEND '~'

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
