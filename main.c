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

char* load_file(const char *filename, size_t *out_filesize) {
	FILE *file;
	size_t result;
	file = fopen(filename, "r");
	if (file == NULL) err("File error. \n", EXIT_FAILURE);
	size_t filesize = get_filesize(file);
	*out_filesize = filesize;

	char* buf = (char*)malloc(sizeof(char)*filesize);
	if (!buf) err("Memory error. \n", EXIT_FAILURE);
	result = fread(buf, sizeof(char), filesize, file);
	if (result != filesize) err("Reading error. \n", EXIT_FAILURE);
	fclose(file);
	return buf;
}

int main(int argc, char **argv) {
	if (argc != 2)
		usage();	

	size_t filesize;
	char* instr = load_file(argv[1], &filesize);
	Brain *data = make_brain(16);
	load_instr(data, instr, filesize);
	run_instr(data);

	free_brain(data);
	free(instr);
	return EXIT_SUCCESS;
}

