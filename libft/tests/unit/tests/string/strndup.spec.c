#include <project.h>
#include "stringft.h"

#define strndup_test(num, s, size, debug)			\
static void		test_## num(t_test *test)			\
{													\
	char		*actual, *expected;					\
	actual = ft_strndup(s, size);					\
	expected = strndup(s, size);					\
	if (debug) {									\
		printf("=====> strndup(%s, %i)\n", s, size);	\
		printf("Expected: %s\n", expected);			\
		printf("Actual:   %s\n", actual);			\
	}												\
	mt_assert(strcmp(actual, expected) == 0);		\
	free(actual); free(expected);					\
}

strndup_test(num00, "Bonjour", 0, false);
strndup_test(num01, "Bonjour", 4, false);
strndup_test(num02, "Bonjour", 7, false);
strndup_test(num03, "Bonjour", 17, false);
strndup_test(num04, "Bonjour\0lolilol", 17, false);

void		suite_strndup(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num00);
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
}
