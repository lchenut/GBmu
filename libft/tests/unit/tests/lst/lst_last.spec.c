#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	mt_assert(lst_first(lst) == NULL);
	lst_push_front(lst, "AAA");
	mt_assert(strcmp(lst_last(lst), "AAA") == 0);
	lst_push_front(lst, "BBB");
	mt_assert(strcmp(lst_last(lst), "AAA") == 0);
	lst_pop_back(lst);
	mt_assert(strcmp(lst_last(lst), "BBB") == 0);
	lst_del(lst, NULL);
}

void		suite_lst_last(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
