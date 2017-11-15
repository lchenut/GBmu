#include <project.h>
#include "stringft.h"

#define strrchr_test(num, s, c, debug)				\
static void		test_## num(t_test *test)			\
{													\
	char		*str = s;							\
	char		*actual, *expected;					\
	actual = ft_strrchr(str, c);					\
	expected = strrchr(str, c);						\
	if (debug) {									\
		printf("=====> strrchr(%s, %c)\n", str, c);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(actual == expected);					\
}

strrchr_test(num01, "Bonjour", 'o', false);
strrchr_test(num02, "Bonjour", 'k', false);
strrchr_test(num03, "Bonjour\0klol", 'k', false);
strrchr_test(num04, "Bonjour\200klol", 'k', false);
strrchr_test(num05, "Bonjour\200klol", '\200', false);
strrchr_test(num06, "qweqweqweqweqweqwe", 'q', false);

void		suite_strrchr(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
	SUITE_ADD_TEST(suite, test_num06);
}
