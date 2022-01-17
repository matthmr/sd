/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#ifndef LOCK_ERR
#  define LOCK_ERR

enum env {
	argtime,
	txtruntime,
	byteruntime,
	cmptime,
	asmtime,
	lntime
};

typedef enum env Env;

void Err (int, char*);
void Set (Env);
#endif

