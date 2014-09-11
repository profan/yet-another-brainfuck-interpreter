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


#include "brain.h"

Brain* brain_create() {
	Brain *brn = malloc(sizeof(*brn));
	return brn;
}

void brain_destroy(Brain *brn) {
	free(brn);
}


/******************************************************
* Goes through all the instructions and matches brackets
* with eachother so that you can index with a instruction
* array index and get the other matching bracket position.
**********************************************************/
void brain_init_brackets(Brain* brn) {
	size_t stack[BRAIN_MAX_INPUT];
	size_t st_ptr = 0;

	size_t cur;
	for (cur = 0; cur < brn->instr_len; ++cur) {
		if (brn->instr[cur] == BRAIN_OP_LEFT_BRACKET) {
			stack[st_ptr++] = cur;
		}
		if (brn->instr[cur] == BRAIN_OP_RIGHT_BRACKET) {
			brn->brackets[cur] = stack[--st_ptr];
			brn->brackets[stack[st_ptr]] = cur;
		}
	} 
	/* if stack is not empty, exit since a bracket or more was not matched. */
	if (st_ptr != 0) {
		printf("ERROR: Unmatched bracket during initiation process, exiting with failure.\n");
		exit(EXIT_FAILURE); 
	}
}

int brain_load_instr(Brain *brn, char *instructions) {
	brn->instr = instructions;
	brn->instr_len = strlen(instructions);
	brain_init_brackets(brn);
	memset(&brn->mem, 0, sizeof(brn->mem));
	brn->ptr = 0;
	return 0;
}

void brain_run_instr(Brain *brn) {
	int in;
	size_t cur;
	for (cur = 0; cur < brn->instr_len; ++cur) {
		switch (brn->instr[cur]) {
			case BRAIN_OP_PTR_RIGHT: brn->ptr++; break;
			case BRAIN_OP_PTR_LEFT: brn->ptr--; break;
			case BRAIN_OP_ADD: brn->mem[brn->ptr]++; break;
			case BRAIN_OP_SUB: brn->mem[brn->ptr]--; break;
#if '\n' == 10 || defined BRAIN_NO_EOL_FILTER
			case BRAIN_OP_OUTPUT: putchar(brn->mem[brn->ptr]); break;
			case BRAIN_OP_INPUT: 
				if ((in = getchar()) != EOF) 
					brn->mem[brn->ptr] = (char)in;
				break;
#else
			case BRAIN_OP_OUTPUT: 
				putchar((brn->mem[brn->ptr] == BRAIN_EOL) ? '\n':brn->mem[brn->ptr]); 
				break;
			case BRAIN_OP_INPUT: 
				if ((in = getchar()) != EOF) 
					((brn->mem[brn->ptr]=(char)in) == '\n') ? BRAIN_EOL:(char)in;
				break;
#endif
			case BRAIN_OP_LEFT_BRACKET:
				if (!brn->mem[brn->ptr]) 
					cur = brn->brackets[cur];
				break;
			case BRAIN_OP_RIGHT_BRACKET:
				if (brn->mem[brn->ptr])
					cur = brn->brackets[cur];
				break;
			case BRAIN_OP_DUMP: brain_dump_memory(brn); break;
			default: break;
		}
	
		
		if (brn->ptr > BRAIN_MEM_SIZE) {
			printf("ERROR: Memory pointer out of bounds, exiting with failure.\n");
			exit(EXIT_FAILURE);
		}

		if (cur > brn->instr_len) {
			printf("ERROR: Attempting access outside instruction range, exiting with failure.\n");
			exit(EXIT_FAILURE);
		}
		

	}
}

/*****************************************
* Simply prints the content of the first *******
* 16 memory cells, a space separating each cell. */
void brain_dump_memory(Brain* brn) {
	size_t i;
	printf("\nMemory (0 - 15): ");
	for (i = 0; i < BRAIN_DUMP_SIZE; ++i) {
		printf("%d ", (char)brn->mem[i]);
	}
	putchar('\n');
}
