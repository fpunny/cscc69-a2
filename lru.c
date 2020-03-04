#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

extern struct frame *coremap;
extern int memsize;
extern int debug;

unsigned int *timestamps = NULL;
unsigned int time = 0;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	// Find the smallest time (oldest) and boot it
	unsigned int frame = 0;
	for (int i = 1; i < memsize; i++) {
		if (timestamps[i] < timestamps[frame]) {
			frame = i;
		}
	}
	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	// Update time to update memory
	timestamps[p->frame >> PAGE_SHIFT] = ++time;
	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	// Make timestamps size of memory
	timestamps = malloc(memsize * sizeof(unsigned int));
}
