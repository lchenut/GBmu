#include <project.h>
#include "stringft.h"

#define strchr_test(num, dst, limit, debug)	\
static void		test_## num(t_test *test)			\
{													\
	char		s[] = dst;							\
	char		*actual, *expected;					\
	expected = strchr(s, limit);					\
	actual = ft_strchr(s, limit);					\
	if (debug) {									\
		printf("=====> strchr(%s, %c)\n", dst, limit);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(actual == expected);					\
}

strchr_test(num01, "Bonjour", 'o', false);
strchr_test(num02, "Bonjour", 'k', false);
strchr_test(num03, "Bonjour", '\0', false);
strchr_test(num04, "ab\200\0cd", 'a', false);
strchr_test(num05, "ab\200\0cd", '\200', false);
strchr_test(num06, "ab\200\0cd", '\0', false);
strchr_test(num07, "ab\200\0cd", 'c', false);
strchr_test(num08, "ab\200\0cd", 'c', false);

void suite_strchr(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
	SUITE_ADD_TEST(suite, test_num06);
	SUITE_ADD_TEST(suite, test_num07);
	SUITE_ADD_TEST(suite, test_num08);
}
