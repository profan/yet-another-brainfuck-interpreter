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
#include "brain.h"
#include "minunit.h"

Brain *brain;

static void test_run(const char *testfile) {
	char *instr = load_file(testfile);
	brain_load_instr(brain, instr);
	brain_run_instr(brain);
	free(instr);
}

static char *test_inc() {
	test_run("tests/inc.b");
	mu_assert("mem[0] does not equal 65(A)!", mem[0] == 65);
}

static char *test_dec() {
	test_run("tests/dec.b");
	mu_assert("mem[0] does not equal -65!", mem[0] == -65);
}

static char *test_inc_jump() {
	test_run("tests/inc_jump.b");
	mu_assert("mem[0] does not equal 65(A)!", mem[0] == 65);
	return 0;
}

static char *test_dec_jump() {
	test_run("tests/dec_jump.b");
	mu_assert("mem[0] does not equal -65!", mem[0] == -65);
	return 0;
}

static char *test_jump() {
	
}

static char *test_output() {
	
}

static char *test_ptrmov() {
	
}

static char *test_tape() {
	
}

static void setup() {
	brain = brain_create();
}

static void destroy() {
	brain_destroy(brain);
}

static char *all_tests() {
	mu_run_test(test_inc);
	mu_run_test(test_dec);
	mu_run_test(test_inc_jump);
	mu_run_test(test_dec_jump);
	return 0;
}

int main(void) {	
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	} else {
		printf("ALL TESTS PASSED.\n");
	}
	
	printf("Tests run: %d\n", tests_run); /* extern comes from minunit.h */
	return result != 0;
}
