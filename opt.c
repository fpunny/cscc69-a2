#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"
#include "sim.h"

extern struct frame *coremap;
extern char *tracefile;
extern char *physmem;
extern int debug;

typedef struct ref_node {
	addr_t vaddr;
	struct ref_node *next;
} node;

addr_t pgdir_vaddr[PTRS_PER_PGDIR];
node *current = NULL;

// For finding the next time vaddr is gonna be accessed
int find_next(addr_t vaddr) {
	int res = 0;
	node *curr = current;

	while(curr) {
		if (curr->vaddr == vaddr) {
			return res;
		}
		curr = curr->next;
		res++;
	}

	return -1;
}

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	int max_distance = 0;
	int frame = 0;

	// Go through all frames to find the one that would be access the latest
	for (int i = 0; i < memsize; i++) {
		int distance = find_next(pgdir_vaddr[i]);

		// If never found (aka never used), then good to boot
		if (distance == -1) {
			return i;
		
		// If further than before, remember that
		} else if (distance > max_distance) {
			max_distance = distance;
			frame = i;
		}
	}

	// Return furthest distance frame
	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {
	// Record vaddr change to frame from tracefile
	pgdir_vaddr[p->frame >> PAGE_SHIFT] = current->vaddr;

	// Move down tracefile to match progress of program
	node *curr = current;
	current = current->next;

	// Free last node
	free(curr);
	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {
	char buf[MAXLINE];
	addr_t vaddr;
	FILE *tfp;
	char type;

	// Init pgdir to vaddr map
	for (int i=0; i < PTRS_PER_PGDIR; i++) {
		pgdir_vaddr[i] = 0;
	}

	// Open ze tracefile (copied from sim.c)
	if(tracefile != NULL) {
		if((tfp = fopen(tracefile, "r")) == NULL) {
			perror("Error opening tracefile:");
			exit(1);
		}
	}

	// Read the tracefile
	node *prev;
	while(fgets(buf, MAXLINE, tfp) != NULL) {
		sscanf(buf, "%c %lx", &type, &vaddr);
	
		// Store vaddr from tracefile
		node *next = malloc(sizeof(struct ref_node));
		next->vaddr = vaddr;
		next->next = NULL;

		// Init head or add to end of list
		if (!current) {
			current = next;
		} else {
			prev->next = next;
		}
		prev = next;
	}
}

