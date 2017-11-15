#include <project.h>
#include "stringft.h"

#define strncmp_test(num, s1, s2, len, debug)	\
static void		test_## num(t_test *test)		\
{												\
	int expected, actual;						\
	expected = strncmp(s1, s2, len);			\
	actual = ft_strncmp(s1, s2, len);			\
	if (debug) {								\
		printf("=====> strncmp(%s, %s, %i)\n", s1, s2, len);	\
		printf("Expected: %i\n", expected);		\
		printf("Actual:   %i\n", actual);		\
	}											\
	mt_assert(actual == expected);				\
}

strncmp_test(num01, "Bonjour", "Bonjour", 8, false);
strncmp_test(num02, "Bonjour", "Bondour", 8, false);
strncmp_test(num03, "Bondour", "Bonjour", 8, false);
strncmp_test(num04, "Bonjour", "Bonsoir", 3, false);
strncmp_test(num05, "Bon\200our", "Bonsoir", 5, false);
strncmp_test(num06, "Bonjour", "Bonjour", 50, false);

void suite_strncmp(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
	SUITE_ADD_TEST(suite, test_num06);
}
