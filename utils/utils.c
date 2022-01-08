/**
 * This file contains basic / useful
 * functionality that are used throughout
 * the resolution of symbols; context
 * agnostic
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

inline void Die (char* msg, int e_code) {
	fprintf (stderr, "%s\n", msg);
	exit (e_code);
}

inline void War (char* msg) {
	fprintf (stderr, "%s\n", msg);
}
