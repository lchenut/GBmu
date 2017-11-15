#include <project.h>
#include "lst.h"

static bool	find_fn(void *data, void *ctx)
{
	return (*((char *)data) == *((char *)ctx));
}

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	lst_push_front(lst, "AAA");
	lst_push_front(lst, "BBB");
	lst_push_front(lst, "CCC");
	mt_assert(strcmp(lst_find_pop(lst, find_fn, "A"), "AAA") == 0);
	mt_assert(strcmp(lst_find_pop(lst, find_fn, "B"), "BBB") == 0);
	mt_assert(lst_find_pop(lst, find_fn, "D") == NULL);
	mt_assert(lst_find_pop(lst, find_fn, "B") == NULL);
	mt_assert(strcmp(lst_find_pop(lst, find_fn, "C"), "CCC") == 0);
	mt_assert(lst_len(lst) == 0);
	lst_del(lst, NULL);
}

void		suite_lst_find_pop(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
