#include <project.h>
#include "stringft.h"

#define memcmp_test(num, s1, s2, len, debug)	\
static void		test_## num(t_test *test)		\
{												\
	int expected, actual;						\
	expected = memcmp(s1, s2, len);				\
	actual = ft_memcmp(s1, s2, len);			\
	if (debug) {								\
		printf("=====> memcmp(%s, %s, %i)\n", s1, s2, len);	\
		printf("Expected: %i\n", expected);		\
		printf("Actual:   %i\n", actual);		\
	}											\
	mt_assert(actual == expected);				\
}

memcmp_test(num01, "Bonjour", "Bonjour", 8, false);
memcmp_test(num02, "Bonjour", "Bondour", 8, false);
memcmp_test(num03, "Bondour", "Bonjour", 8, false);
memcmp_test(num04, "Bonjour", "Bonsoir", 3, false);
memcmp_test(num05, "Bon\200our", "Bonsoir", 4, false);
memcmp_test(num06, "Bon\0our", "Bon\0our", 8, false);

void suite_memcmp(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
	SUITE_ADD_TEST(suite, test_num06);
}
