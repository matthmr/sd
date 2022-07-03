/**
 * @file err.c
 *
 * @brief standard error formatting
 *
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#include <stdlib.h>

#include "utils/verbose/colors.h" // TODO: ignore colors at runtime
#include "utils/err/err.h"

char ERROR = '\0';

/// @brief standard error exitter
/// @param code exit code
/// @param finfo file info
/// @param einfo error info
void Err (int ecode, function header, function body) {

	if (header) header ();
	if (body) body ();

	exit (ecode);
}

void ErrPromise (int ecode, function header, function body) {
	if (header) header ();
	if (body) body ();
}
