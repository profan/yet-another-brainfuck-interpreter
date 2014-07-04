/*
* The MIT License (MIT)
*
* Copyright (c) 2014 Robin Hübner <robinhubner@gmail.com
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

void usage() {
	printf("usage: yabi <filename> [<args>] \n");
	exit(EXIT_FAILURE);
}

void err(char* msg, int errcode) {
	fputs(msg, stderr);
	exit(errcode);
}

size_t get_filesize(FILE *file) {
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
 	rewind(file);
	if (size <= 0) err("Invalid file size. \n", EXIT_FAILURE);
	return (size_t)size;
}

char* load_file(const char *filename) {
	FILE *file;
	size_t result;
	file = fopen(filename, "r");
	if (file == NULL) err("File error (does it exist?). \n", EXIT_FAILURE);
	size_t filesize = get_filesize(file);
	
	char *buf = malloc(sizeof(*buf)*filesize);
	if (!buf) err("Memory error. \n", EXIT_FAILURE);
	result = fread(buf, sizeof(*buf), filesize, file);
	if (result != filesize) err("Reading error. \n", EXIT_FAILURE);
	fclose(file);
	return buf;
}

int main(int argc, char **argv) {
	if (argc != 2)
		usage();	

	char* instr = load_file(argv[1]);
	Brain *data = brain_create();
	brain_load_instr(data, instr);
	brain_run_instr(data);

	brain_destroy(data);
	free(instr);
	return EXIT_SUCCESS;
}

