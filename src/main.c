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

#include <argp.h>
#include "util.h"
#include "brain.h"

const char *argp_program_version = "yet-another-brainfuck-interpreter v1.0";
const char *argp_program_bug_address = "<robinhubner@gmail.com>";
static char doc[] = "Simple brainfuck interpreter with REPL.";
static char args_doc[] = "[filename]...";
static struct argp_option options[] = { 
	{ "input", 'i', "FILE", 0, "Brainfuck file to load."},
	{ "repl", 'r', 0, OPTION_ARG_OPTIONAL, "Start interpreter in REPL mode."},
	{ 0 } 
};

struct arguments {
    const char *input_file;
	enum { STANDARD_MODE, REPL_MODE } mode;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
	struct arguments *args = state->input;
	switch (key) {
		case 'i': args->input_file = arg; break;
		case 'r': args->mode = REPL_MODE; break;
		case ARGP_KEY_ARG: return 0;
		default: return ARGP_ERR_UNKNOWN;
	}   
	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char **argv) {
	struct arguments args;
	args.mode = STANDARD_MODE;
	argp_parse(&argp, argc, argv, 0, 0, &args);	

	if (args.mode == STANDARD_MODE) {
		char* instr = load_file(args.input_file);
		Brain *data = brain_create();
		brain_load_instr(data, instr);
		int statuscode = brain_run_instr(data);
		brain_destroy(data);
		free(instr);
	} else if (args.mode == REPL_MODE) {
		return EXIT_FAILURE;
	} else {
		return EXIT_FAILURE;
	}	

	return 0;
}

