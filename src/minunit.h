/* http://www.jera.com/techinfo/jtns/jtn002.html */

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(testname, test) \
	do { \
		char *message = test(); tests_run++; \
		if (message) return message; \
		else printf("OK: %s\n", testname); \
	} while (0)

extern int tests_run;
