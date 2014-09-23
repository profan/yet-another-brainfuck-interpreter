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
int tests_run = 0;

static void test_run(const char *testfile) {
	char *instr = load_file(testfile);
	brain_load_instr(brain, instr);
	brain_run_instr(brain);
	free(instr);
}

static char *test_inc() {
	test_run("tests/inc.b");
	printf("[inc]: brain->mem[0]: %d\n", brain->mem[0]);
	mu_assert("[inc]: brain->mem[0] does not equal 65(A)!", brain->mem[0] == 65);
	mu_assert("[inc]: brain->ptr does not equal 0!", brain->ptr == 0);
	return 0;
}

static char *test_dec() {
	test_run("tests/dec.b");
	mu_assert("[dec]: brain->mem[0] does not equal -65!", brain->mem[0] == -65);
	mu_assert("[dec]: brain->ptr does not equal 0!", brain->ptr == 0);
	return 0;
}

static char *test_inc_jump() {
	test_run("tests/inc_jump.b");
	mu_assert("[inc_jump]: brain->mem[1] does not equal 65(A)!", brain->mem[1] == 65);
	mu_assert("[inc_jump]: brain->ptr does not equal 1!", brain->ptr == 1);
	return 0;
}

static char *test_dec_jump() {
	test_run("tests/dec_jump.b");
	mu_assert("[dec_jump]: brain->mem[1] does not equal -65!", brain->mem[1] == -65);
	mu_assert("[dec_jump]: brain->ptr does not equal 1!", brain->ptr == 1);
	return 0;
}

static char *test_jump() {
	return 0;
}

static char *test_output() {
	FILE *fp = fopen("output.txt", "ab+"); 
	brain_set_out_fd(brain, fp);
	test_run("tests/output.b");
	fclose(fp);
	return 0;
}

static char *test_ptr_mov() {
	test_run("tests/ptr_mov.b");
	mu_assert("[ptr_rmov] brain->ptr position not 0!", brain->ptr == 0);
	return 0;
}

static char *test_tape() {
	return 0;
}

static void setup() {
	brain = brain_create();
}

static void destroy() {
	brain_destroy(brain);
}

static char *all_tests() {
	setup();
	mu_run_test(test_ptr_mov);
	mu_run_test(test_inc);
	mu_run_test(test_dec);
	mu_run_test(test_inc_jump);
	mu_run_test(test_dec_jump);
	mu_run_test(test_output);
	destroy();
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
