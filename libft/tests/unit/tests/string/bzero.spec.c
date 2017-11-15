#include <project.h>
#include "stringft.h"

static void	simple_test(t_test *test)
{
	char	tmp[64];

	memset(tmp, 'A', 63);
	tmp[63] = 0;
	bzero(tmp, 0);
	mt_assert(tmp[0] == 'A');
	bzero(tmp, 10);
	mt_assert(tmp[1] == 0);
	mt_assert(tmp[5] == 0);
	mt_assert(tmp[9] == 0);
	mt_assert(tmp[10] == 'A');
}

void		suite_bzero(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
