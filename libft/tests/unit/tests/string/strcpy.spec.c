#include <project.h>
#include "stringft.h"

#define strcpy_test(num, src, debug)			\
static void		test_ ##num(t_test *test)		\
{												\
	char		actual[1024], expected[1024];	\
	ft_strcpy(actual, src);						\
	strcpy(expected, src);						\
	if (debug) {								\
		printf("=====> strcpy([], %s)\n", src);	\
		printf("Expected: %s\n", expected);		\
		printf("Actual:   %s\n", actual);		\
	}											\
	mt_assert(strcmp(actual, expected) == 0);	\
}

strcpy_test(num01, "Coucou", false);
strcpy_test(num02, "Cou\0cou", false);
strcpy_test(num03, "Cou\200cou", false);

void suite_strcpy(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
}
