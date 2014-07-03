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
