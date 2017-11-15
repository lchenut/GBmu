#include <project.h>
#include "stringft.h"

#define strcat_test(num, s1, s2, debug)				\
static void		test_## num(t_test *test)			\
{													\
	char		actual[1000] = s1;					\
	char		expected[1000] = s1;				\
	ft_strcat(actual, s2);							\
	strcat(expected, s2);							\
	if (debug) {									\
		printf("=====> strcat(%s, %s)\n", s1, s2);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(strcmp(actual, expected) == 0);		\
}

strcat_test(num01, "Bonjour", "", false);
strcat_test(num02, "", "Bonjour", false);
strcat_test(num03, "Bon", "jour", false);
strcat_test(num04, "\200Bon", "jour\200", false);
strcat_test(num05, "Bonjour\0Bonjour", "Bonsoir\0Bonsoir", false);

void		suite_strcat(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
}
