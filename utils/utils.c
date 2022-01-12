/**
 * This file contains basic / useful
 * functionality that are used throughout
 * the resolution of symbols; context
 * agnostic
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void Die (char* fmt,
          const char* msg,
          char* info,
          int e_code) {
	fprintf (stderr, fmt, msg, info);
	exit (e_code);
}

void War (char* fmt,
          const char* msg,
          char* info) {
	fprintf (stderr, fmt, msg, info);
}
