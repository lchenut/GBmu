#include <project.h>
#include "stringft.h"

#define strdup_test(num, s, debug)					\
static void		test_## num(t_test *test)			\
{													\
	char		*actual, *expected;					\
	actual = ft_strdup(s);							\
	expected = strdup(s);							\
	if (debug) {									\
		printf("=====> strdup(%s)\n", s);			\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(strcmp(actual, expected) == 0);		\
	free(actual); free(expected);					\
}

strdup_test(num00, "", false);
strdup_test(num01, "Bonjour", false);
strdup_test(num02, "Bonjour\200lolilol", false);
strdup_test(num03, "Bonjour\0lolilol", false);

void		suite_strdup(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num00);
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
}
