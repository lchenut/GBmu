#include <project.h>
#include "stringft.h"

#define strstr_test(num, big, little, len, debug)	\
static void		test_## num(t_test *test)			\
{													\
	char		*s1 = big, *s2 = little;			\
	char		*actual, *expected;					\
	actual = ft_strnstr(s1, s2, len);				\
	expected = strnstr(s1, s2, len);				\
	if (debug) {									\
		printf("=====> strstr(%s, %s, %i)\n", s1, s2, len);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(actual == expected);					\
}

strstr_test(num01, "Bonjour", "o", 7, false);
strstr_test(num02, "Bonjour", "k", 7, false);
strstr_test(num03, "Bonjour", "ou", 7, false);
strstr_test(num04, "azarabozarabozepouet", "zaraboze", 50, false);
strstr_test(num05, "1234567890", "34567", 6, false);

void		suite_strnstr(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
}
