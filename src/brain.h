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

typedef struct {
	char *instr;
	size_t instr_len, ptr;
	size_t brackets[BRAIN_MAX_INPUT];
	char mem[BRAIN_MEM_SIZE];
	/* file descriptors for rerouting input and output, will be stdin/stderr/stdout by default. */
	FILE *in, *out, *err;
} Brain;

Brain* 	brain_create();
void 	brain_destroy(Brain *brn);
void 	brain_init_brackets(Brain* data);
int 	brain_load_instr(Brain *brn, char *instr);
void	brain_set_in_fd(Brain *brn, FILE *file);
void	brain_set_out_fd(Brain *brn, FILE *file);
void	brain_set_err_fd(Brain *brn, FILE *file);
void 	brain_run_instr(Brain *brn);
void 	brain_dump_memory(Brain* brn);

#endif
