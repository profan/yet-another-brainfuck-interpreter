/*
* The MIT License (MIT)
*
* Copyright (c) 2014 Robin Hübner <robinhubner@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef BRAIN_H
#define BRAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BRAIN_MAX_INPUT 65536
#define BRAIN_MEM_SIZE 	65536
#define BRAIN_DUMP_SIZE 16

#define BRAIN_OP_ADD 			'+'
#define BRAIN_OP_SUB 			'-'
#define BRAIN_OP_PTR_LEFT 		'<'
#define BRAIN_OP_PTR_RIGHT		'>'
#define BRAIN_OP_INPUT			','
#define BRAIN_OP_OUTPUT			'.'
#define BRAIN_OP_LEFT_BRACKET	'['
#define BRAIN_OP_RIGHT_BRACKET	']'
#define BRAIN_OP_DUMP			'#'

#define BRAIN_EOL 10 /* eol character value! */

/* error return codes! */
#define BRAIN_PC_OUT_OF_BOUNDS 2
#define BRAIN_MEM_OUT_OF_BOUNDS 3
#define BRAIN_INIT_BRACKET_MISMATCH 4

/* flags! */
#define BRAIN_MODE_REPL (1 << 0)

typedef struct {
	size_t value; /* Can represent both jump point for a bracket, or increment/decrement value for ADD/SUB/MOVLEFT/MOVRIGHT */
	char type;
} Instruction;

typedef struct {
	Instruction instr[BRAIN_MAX_INPUT];
	char mem[BRAIN_MEM_SIZE];
	size_t instr_len, ptr;
	FILE *in, *out, *err;
	unsigned int flags;
} Brain;

Brain* 	brain_create();
void 	brain_destroy(Brain *brn);
int 	brain_load_instr(Brain *brn, char *instr);
void	brain_set_in_fd(Brain *brn, FILE *file);
void	brain_set_out_fd(Brain *brn, FILE *file);
void	brain_set_err_fd(Brain *brn, FILE *file);
int 	brain_run_instr(Brain *brn);
void 	brain_dump_memory(Brain* brn);

/* End of prototypes and header, implementation follows. */

Brain* brain_create() {
	Brain *brn = malloc(sizeof(*brn));
	brn->in = stdin;
	brn->out = stdout;
	brn->err = stderr;
	return brn;
}

void brain_destroy(Brain *brn) {
	free(brn);
}

/**************************************************
* Traverses the instruction stream, removing redundant
* instructions for faster execution.
* Removes all non-instructions from stream and turns
* several sequential instructions into single ops.
* >>>>> would become {>, 5}, +++++ would become {+, 5}
*******************************************************/

static void brain_parse_instr(Brain *brn, char *instr) {
	
	char token;
	size_t cur, newsize = 0, instr_len = strlen(instr);
	for (cur = 0; cur < instr_len; ++cur) {
		token = instr[cur];
		
		if (token != BRAIN_OP_ADD && 
			token != BRAIN_OP_SUB && 
			token != BRAIN_OP_PTR_LEFT &&
			token != BRAIN_OP_PTR_RIGHT && 
			token != BRAIN_OP_INPUT && 
			token != BRAIN_OP_OUTPUT && 
			token != BRAIN_OP_LEFT_BRACKET &&
			token != BRAIN_OP_RIGHT_BRACKET && 
			token != BRAIN_OP_DUMP) 
		{
				continue;
		}

		if (token != brn->instr[newsize].type) {
			brn->instr[newsize].type = token;
			brn->instr[newsize].value = 1;
			++newsize;
		} else {
			if (token == BRAIN_OP_ADD || token == BRAIN_OP_SUB || token == BRAIN_OP_PTR_LEFT || token == BRAIN_OP_PTR_RIGHT) {
				++brn->instr[newsize].value;
			}
		}
	}

	/* set actual instruction length size. */
	brn->instr_len = newsize;

}

/******************************************************
* Goes through all the instructions and matches brackets
* with eachother so that you can index with a instruction
* array index and get the other matching bracket position.
**********************************************************/
static int brain_init_brackets(Brain* brn) {

	size_t *stack = malloc(sizeof(*stack)*brn->instr_len);
	size_t cur, st_ptr = 0;
	char token;
	
	for (cur = 0; cur < brn->instr_len; ++cur) {
		token = brn->instr[cur].type;
		if (token == BRAIN_OP_LEFT_BRACKET) {
			stack[st_ptr++] = cur;
		}
		else if (token == BRAIN_OP_RIGHT_BRACKET) {
			brn->instr[cur].value = stack[--st_ptr];
			brn->instr[stack[st_ptr]].value = cur;
		}
	} 
	/* if stack is not empty, return since a bracket or more was not matched. */
	if (st_ptr != 0) {
		fprintf(brn->err, "ERROR: Unmatched bracket during initiation process, returning with failure.\n");
		return BRAIN_INIT_BRACKET_MISMATCH;
	}

	free(stack);
	return 0;
}

int brain_load_instr(Brain *brn, char *instructions) {
	memset(&brn->instr, 0, sizeof(brn->instr));
	brain_parse_instr(brn, instructions);

	int init_status;
	if ((init_status = brain_init_brackets(brn)) != 0)
		return init_status;

	memset(&brn->mem, 0, sizeof(brn->mem));
	brn->ptr = 0;

	return 0;
}

void brain_set_in_fd(Brain *brn, FILE *file) {
	brn->in = file;
}

void brain_set_out_fd(Brain *brn, FILE *file) {
	brn->out = file;
}

void brain_set_err_fd(Brain *brn, FILE *file) {
	brn->err = file;
}

int brain_run_instr(Brain *brn) {
	int in;
	size_t pc;
	for (pc = 0; pc < brn->instr_len; ++pc) {
		switch (brn->instr[pc].type) {
			case BRAIN_OP_PTR_RIGHT: brn->ptr += brn->instr[pc].value; break;
			case BRAIN_OP_PTR_LEFT: brn->ptr -= brn->instr[pc].value; break;
			case BRAIN_OP_ADD: brn->mem[brn->ptr] += brn->instr[pc].value; break;
			case BRAIN_OP_SUB: brn->mem[brn->ptr] -= brn->instr[pc].value; break;
			case BRAIN_OP_LEFT_BRACKET:
				if (brn->mem[brn->ptr] == 0) 
					pc = brn->instr[pc].value;
				break;
			case BRAIN_OP_RIGHT_BRACKET:
				if (brn->mem[brn->ptr])
					pc = brn->instr[pc].value;
				break;
#if '\n' == 10 || defined BRAIN_NO_EOL_FILTER
			case BRAIN_OP_OUTPUT: putc(brn->mem[brn->ptr], brn->out); break;
			case BRAIN_OP_INPUT: 
				if ((in = getc(brn->in)) != EOF) 
					brn->mem[brn->ptr] = (char)in;
				break;
#else
			case BRAIN_OP_OUTPUT: 
				putc((brn->mem[brn->ptr] == BRAIN_EOL, brn->out) ? '\n':brn->mem[brn->ptr]); 
				break;
			case BRAIN_OP_INPUT: 
				if ((in = getc(brn->in)) != EOF) 
					((brn->mem[brn->ptr]=(char)in) == '\n') ? BRAIN_EOL:(char)in;
				break;
#endif
			case BRAIN_OP_DUMP: brain_dump_memory(brn); break;
			default: break;
		}
	
		
		if (brn->ptr > BRAIN_MEM_SIZE) {
			fprintf(brn->err, "ERROR: Memory pointer out of bounds, returning with failure.\n");
			fprintf(brn->err, " - pointer was at: %zu\n", brn->ptr);
			fprintf(brn->err, " - cells allocated: %d\n", BRAIN_MEM_SIZE);
			return BRAIN_MEM_OUT_OF_BOUNDS;
		}

		if (pc > brn->instr_len) {
			fprintf(brn->err, "ERROR: Attempting access outside instruction range, returning with failure.\n");
			fprintf(brn->err, " - access was at: %zu\n", pc);
			fprintf(brn->err, " - instruction size was: %zu\n", brn->instr_len);
			return BRAIN_PC_OUT_OF_BOUNDS;
		}
		

	}
	return 0;
}

/*****************************************
* Simply prints the content of the first *******
* 16 memory cells, a space separating each cell. */
void brain_dump_memory(Brain* brn) {
	size_t i;
	fprintf(brn->err, "\n[DEBUG] Memory (0 - 15): ");
	for (i = 0; i < BRAIN_DUMP_SIZE; ++i) {
		fprintf(brn->err, "%d ", (char)brn->mem[i]);
	}
	putc('\n', brn->err);
}

#endif
