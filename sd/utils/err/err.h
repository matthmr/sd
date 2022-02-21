/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#ifndef LOCK_ERR
#  define LOCK_ERR

typedef enum time {
	TIME_ARG,
	TIME_TXT,
	TIME_BYTE,
	TIME_COMP,
} Time;

extern const char* errmsg[];
extern char* fmt;

void Err (int, char*);
void e_set (Time);
#endif
