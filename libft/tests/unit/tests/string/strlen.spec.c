#include <project.h>
#include "stringft.h"

#define strlen_test(num, str, debug)		\
static void		test_## num(t_test *test)	\
{											\
	size_t		actual, expected;			\
	actual = ft_strlen(str);				\
	expected = strlen(str);					\
	if (debug) {							\
		printf("=====> strlen(%s)\n", str);	\
		printf("Expected: %zu\n", expected);\
		printf("Actual:   %zu\n", actual);	\
	}										\
	mt_assert(actual == expected);			\
}

strlen_test(num00, "", false);
strlen_test(num01, "Bonjour", false);
strlen_test(num02, "Bonjour\0Salut", false);
strlen_test(num03, "Bonjour\200Salut", false);

static void		test_bigstring(t_test *test)
{
	char		*bigstring;
	size_t		actual, expected;
	bigstring = malloc(10000000);
	memset(bigstring, 'a', 9999999);
	actual = ft_strlen(bigstring);
	expected = strlen(bigstring);
	mt_assert(actual == expected);
	free(bigstring);
}

void suite_strlen(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num00);
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_bigstring);
}
