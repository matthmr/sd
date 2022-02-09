/**
 * This file contains functionality
 * for literal assignment/reference
 */

#include <string.h>

#include <sd/intr/utils/literal.h>

inline void cat (char* literal, char* data) {
	(void) strcat (literal, data);
}
