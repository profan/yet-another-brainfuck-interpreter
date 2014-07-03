#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BRAIN_MAX_INPUT 65536
#define BRAIN_MEM_SIZE 65536
#define BRAIN_DUMP_SIZE 16

typedef struct {
	char *instr;
	size_t instr_len;
	size_t brackets[BRAIN_MAX_INPUT];
	char mem[BRAIN_MEM_SIZE];
	size_t ptr;
} Brain;

Brain* 	brain_create();
void 	brain_destroy(Brain *brn);
void 	brain_init_brackets(Brain* data);
int 	brain_load_instr(Brain *brn, char *instr, size_t instr_len);
void 	brain_run_instr(Brain *brn);
void 	brain_dump_memory(Brain* brn);

#endif
