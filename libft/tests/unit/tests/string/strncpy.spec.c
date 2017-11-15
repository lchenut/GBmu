#include <project.h>
#include "stringft.h"

#define strncpy_test(num, src, len, debug)		\
static void		test_ ##num(t_test *test)		\
{												\
	char		actual[64], expected[64];		\
	memset(actual, 'A', sizeof(actual));		\
	memset(expected, 'A', sizeof(expected));	\
	actual[63] = 0; expected[63] = 0;			\
	ft_strncpy(actual, src, len);				\
	strncpy(expected, src, len);				\
	if (debug) {								\
		printf("=====> strncpy([], %s, %i)\n", src, len);	\
		printf("Expected: %s\n", expected);		\
		printf("Actual:   %s\n", actual);		\
	}											\
	mt_assert(memcmp(actual, expected, 64) == 0);	\
}

strncpy_test(num01, "Coucou", 6, false);
strncpy_test(num02, "Coucou", 3, false);
strncpy_test(num03, "Coucou", 42, false);
strncpy_test(num04, "Cou\0cou", 7, false);
strncpy_test(num05, "Cou\200cou", 7, false);

void suite_strncpy(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
}
