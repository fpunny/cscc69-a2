#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

extern struct frame *coremap;
extern int memsize;
extern int debug;

int clock_index = 0;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	pgtbl_entry_t *page = coremap[clock_index].pte;

	while(page->frame & PG_REF) {
		page->frame &= ~PG_REF;
		clock_index = (clock_index + 1) % memsize;
		page = coremap[clock_index].pte;
	}

	int _index = clock_index;
	clock_index = (clock_index + 1) % memsize;
	return _index;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
}
