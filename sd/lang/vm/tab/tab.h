/**
 * This file contains the
 * implementations for
 * the SD vm table
 */

#ifndef LOCK_TAB
#  define LOCK_TAB

#include <sd/utils/types/shared.h>

typedef byte tab_index;

struct tab {
	tab_index* root;
	tab_index* head;
	uint gidn;
	uint gid;
};

typedef struct tab Tab;
extern Tab obj_tab;

void tab_gen (void);

#endif
