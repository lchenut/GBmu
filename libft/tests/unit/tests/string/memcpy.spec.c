#include <project.h>
#include "stringft.h"

static void		test_simple(t_test *test)
{
	const char	*src = "Bonjour";
	char		dst[10];
	ft_memcpy(dst, src, 8);
	mt_assert(memcmp(dst, src, 8) == 0);
}

static void		test_overlap01(t_test *test)
{
	char		dst[10] = "Bonjour";
	ft_memcpy(dst, dst + 3, 4);
	mt_assert(memcmp(dst, "jourour", 8) == 0);
}

static void		test_overlap02(t_test *test)
{
	char		dst[10] = "Bonjour";
	ft_memcpy(dst + 3, dst, 4);
	mt_assert(memcmp(dst, "BonBonj", 8) == 0);
}

void suite_memcpy(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_simple);
	SUITE_ADD_TEST(suite, test_overlap01);
	SUITE_ADD_TEST(suite, test_overlap02);
}
