/*
* The MIT License (MIT)
*
* Copyright (c) 2014 Profan
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
	Brain *brn = (Brain*)malloc(sizeof(Brain));
	memset(&brn->mem, 0, sizeof(brn->mem));
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
		if (brn->instr[cur] == '[') {
			stack[st_ptr++] = cur;
		}
		if (brn->instr[cur] == ']') {
			brn->brackets[cur] = stack[--st_ptr];
			brn->brackets[stack[st_ptr]] = cur;
		}
	} 
	/* if stack is not empty, exit since a bracket or more was not matched. */
	if (st_ptr != 0) exit(EXIT_FAILURE); 
}

int brain_load_instr(Brain *brn, char *instructions, size_t instr_len) {
	brn->instr = instructions;
	brn->instr_len = instr_len;
	brain_init_brackets(brn);
	brn->ptr = 0;
	return 0;
}

void brain_run_instr(Brain *brn) {
	int in;
	size_t cur;
	for (cur = 0; cur < brn->instr_len; ++cur) {
		switch (brn->instr[cur]) {
			case '>': brn->ptr++; break;
			case '<': brn->ptr--; break;
			case '+': brn->mem[brn->ptr]++; break;
			case '-': brn->mem[brn->ptr]--; break;
#if '\n' == 10 || defined NO_EOL_FILTER
			case '.': putchar(brn->mem[brn->ptr]); break;
			case ',': 
				if ((in = getchar()) != EOF) 
					brn->mem[brn->ptr] = (char)in;
				break;
#else
			case '.': 
				putchar((brn->mem[brn->ptr]==10)?'\n':brn->mem[brn->ptr]); 
				break;
			case ',': 
				if ((in = getchar()) != EOF) 
					(brn->mem[brn->ptr]=(char)in)=='\n'?10:(char)in;
				break;
#endif
			case '[':
				if (!brn->mem[brn->ptr]) 
					cur = brn->brackets[cur];
				break;
			case ']':
				if (brn->mem[brn->ptr])
					cur = brn->brackets[cur];
				break;
			case '#': brain_dump_memory(brn); break;
			default: break;
		}
		
		if (brn->ptr > BRAIN_MEM_SIZE) {
			printf("Memory pointer out of bounds, exiting. \n");
			exit(EXIT_FAILURE);
		}

		if (cur > brn->instr_len) {
			printf("Early exit, attempted access outside instruction range. \n");
			exit(EXIT_FAILURE);
		}

	}
}

/*****************************************
* Simply prints the content of the first *******
* 16 memory cells, a space separating each cell. */
void brain_dump_memory(Brain* brn) {
	size_t i;
	for (i = 0; i < BRAIN_DUMP_SIZE; ++i) {
		printf("%d ", brn->mem[i]);
	}
	putchar('\n');
}
