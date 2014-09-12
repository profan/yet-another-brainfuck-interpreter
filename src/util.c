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

#include "util.h"

void err(char *msg, int errcode) {
	fputs(msg, stderr);
	exit(errcode);
}

long get_filesize(FILE *file) {
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
 	rewind(file);
	if (size <= 0) err("Invalid file size. \n", EXIT_FAILURE);
	return size;
}

long fread_str(char *buf, size_t buf_size, long filesize, FILE *file) {
	long result = fread(buf, buf_size, filesize, file);
	buf[filesize] = '\0';
	return result;
}

char* load_file(const char *filename) {
	FILE *file;
	long result;
	file = fopen(filename, "r");
	if (file == NULL) err("File error (does it exist?). \n", EXIT_FAILURE);
	long filesize = get_filesize(file);
	
	char *buf = malloc((sizeof(*buf)*filesize)+1);
	if (!buf) err("Memory error. \n", EXIT_FAILURE);
	result = fread_str(buf, sizeof(*buf), filesize, file);
	if (result != filesize) err("Reading error. \n", EXIT_FAILURE);
	fclose(file);
	return buf;
}


