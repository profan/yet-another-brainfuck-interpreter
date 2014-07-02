#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BRAIN_MAX_INPUT 65536
#define BRAIN_MEM_SIZE 65536

typedef struct {
	char *instr;
	size_t instr_len;
	size_t brackets[BRAIN_MAX_INPUT];
	char mem[BRAIN_MEM_SIZE];
	size_t ptr;
	unsigned int dumpsize;
} Brain;

Brain* make_brain(unsigned int dumpsize);
void free_brain(Brain *brn);
void init_brackets(Brain* data);
int load_instr(Brain *brn, char *instr, size_t instr_len);
void run_instr(Brain *brn);
void dump_memory(Brain* brn);

#endif
