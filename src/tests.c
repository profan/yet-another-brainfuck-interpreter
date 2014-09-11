#include "util.h"
#include "brain.h"
#include "minunit.h"

Brain *brain;

static char *test_inc() {
	
}

static char *test_dec() {
	
}

static char *test_inc_jump() {
	
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
	mu_run_test(test_inc_jump);
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
