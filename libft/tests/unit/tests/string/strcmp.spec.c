#include <project.h>
#include "stringft.h"

#define strcmp_test(num, s1, s2, debug)	\
static void		test_## num(t_test *test)		\
{												\
	int expected, actual;						\
	expected = strcmp(s1, s2);					\
	actual = ft_strcmp(s1, s2);					\
	if (debug) {								\
		printf("=====> strcmp(%s, %s)\n", s1, s2);	\
		printf("Expected: %i\n", expected);		\
		printf("Actual:   %i\n", actual);		\
	}											\
	mt_assert(actual == expected);				\
}

strcmp_test(num01, "Bonjour", "Bonjour", false);
strcmp_test(num02, "Bonjour", "Bondour", false);
strcmp_test(num03, "Bondour", "Bonjour", false);
strcmp_test(num04, "Bonjour", "Bonsoir", false);
strcmp_test(num05, "Bon\200our", "Bonsoir", false);

void suite_strcmp(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
}
