#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"

extern struct frame *coremap;
extern char *tracefile;
extern char *physmem;
extern int memsize;
extern int debug;

typedef struct node {
	addr_t vaddr;
	struct node *next;
} oracle;

oracle *ptr = NULL;
FILE *tfp = stdin;

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {

	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	char buf[MAXLINE];
	ddr_t vaddr = 0;
	char type;

	for (int i = 0; i < PTRS_PER_PGDIR; i++) {
		pgdir_clone[i].pde = 0;
	}

	if(tracefile != NULL) {
		if((tfp = fopen(tracefile, "r")) == NULL) {
			perror("Error opening tracefile:");
			exit(1);
		}
	}

	unsigned idx;
	while(fgets(buf, MAXLINE, infp) != NULL) {
		sscanf(buf, "%c %lx", &type, &vaddr);
		idx = PGDIR_INDEX(vaddr);
		// TODO
	}
}

