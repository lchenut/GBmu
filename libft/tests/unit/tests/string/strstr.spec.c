#include <project.h>
#include "stringft.h"

#define strstr_test(num, big, little, debug)		\
static void		test_## num(t_test *test)			\
{													\
	char		*s1 = big, *s2 = little;			\
	char		*actual, *expected;					\
	actual = ft_strstr(s1, s2);						\
	expected = strstr(s1, s2);						\
	if (debug) {									\
		printf("=====> strstr(%s, %s)\n", s1, s2);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	if (expected) {									\
		mt_assert(strcmp(actual, expected) == 0);	\
	} else {										\
		mt_assert(actual == NULL);					\
	}												\
}

strstr_test(num01, "Bonjour", "o", false);
strstr_test(num02, "Bonjour", "k", false);
strstr_test(num03, "Bonjour", "ou", false);
strstr_test(num04, "azarabozarabozepouet", "zaraboze", false);

void		suite_strstr(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
}
