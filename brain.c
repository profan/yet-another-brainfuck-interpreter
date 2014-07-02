#include "brain.h"

Brain* make_brain() {
	Brain *brn = (Brain*)malloc(sizeof(Brain));
	memset(&brn->mem, 0, sizeof(brn->mem));
	return brn;
}

void free_brain(Brain *brn) {
	free(brn);
}


/******************************************************
* Goes through all the instructions and matches brackets
* with eachother so that you can index with a instruction
* array index and get the other matching bracket position.
**********************************************************/
void init_brackets(Brain* brn) {
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

int load_instr(Brain *brn, char *instructions, size_t instr_len) {
	brn->instr = instructions;
	brn->instr_len = instr_len;
	init_brackets(brn);
	brn->ptr = 0;
	return 0;
}

void run_instr(Brain *brn) {
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
			case '#': dump_memory(brn); break;
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
void dump_memory(Brain* brn) {
	size_t i;
	for (i = 0; i < BRAIN_DUMP_SIZE; ++i) {
		printf("%d ", brn->mem[i]);
	}
	putchar('\n');
}
