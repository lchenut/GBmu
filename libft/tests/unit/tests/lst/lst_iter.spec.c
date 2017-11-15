#include <project.h>
#include "lst.h"

static void	rot1(void *data)
{
	for (int i = 0, l = strlen(data); i < l; i += 1)
	{
		((char *)data)[i] += 1;
	}
}

static void	simple_test(t_test *test)
{
	t_lst	*lst;
	char	*tmp;

	lst = lst_new();
	lst_push_front(lst, strdup("AAA"));
	lst_push_front(lst, strdup("CCC"));
	lst_push_front(lst, strdup("EEE"));
	lst_iter0(lst, rot1);
	mt_assert(strcmp(lst_get(lst, 0), "FFF") == 0);
	mt_assert(strcmp(lst_get(lst, 1), "DDD") == 0);
	mt_assert(strcmp(lst_get(lst, 2), "BBB") == 0);
	lst_del(lst, free);
}

void		suite_lst_iter(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
