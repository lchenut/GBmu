#include <project.h>
#include "stringft.h"

#define memchr_test(num, dst, limit, len, debug)	\
static void		test_## num(t_test *test)			\
{													\
	char		s[] = dst;							\
	char		*actual, *expected;					\
	expected = memchr(s, limit, len);				\
	actual = ft_memchr(s, limit, len);				\
	if (debug) {									\
		printf("=====> memchr(%s, %c, %i)\n", dst, limit, len);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(actual == expected);					\
}

memchr_test(num01, "Bonjour", 'n', 8, false);
memchr_test(num02, "Bonjour", 'k', 8, false);
memchr_test(num03, "Bonjour", '\0', 8, false);
memchr_test(num04, "ab\200\0cd", 'a', 6, false);
memchr_test(num05, "ab\200\0cd", '\200', 6, false);
memchr_test(num06, "ab\200\0cd", '\0', 6, false);
memchr_test(num07, "ab\200\0cd", 'c', 6, false);
memchr_test(num08, "ab\200\0cd", 'c', 0, false);

void suite_memchr(t_suite *suite)
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
