/**
 * This file contains the
 * implementations for
 * the SD vm table
 */

#ifndef LOCK_TAB
#  define LOCK_TAB

#include <sd/utils/types/shared.h>

typedef unsigned char Normal;

struct tab {
	Normal* (*let) (void);
	Normal* (*proc) (void);

	addr (*heap_data) (void);
	addr head;

	void (*chroot) (addr);
	void (*buffer) (byte);
};

typedef struct tab Tab;

extern Tab tab;

#endif
