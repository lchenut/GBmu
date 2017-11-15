#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	mt_assert(lst_first(lst) == NULL);
	lst_push_front(lst, "AAA");
	mt_assert(strcmp(lst_first(lst), "AAA") == 0);
	lst_push_front(lst, "BBB");
	mt_assert(strcmp(lst_first(lst), "BBB") == 0);
	lst_pop_front(lst);
	mt_assert(strcmp(lst_first(lst), "AAA") == 0);
	lst_del(lst, NULL);
}

void		suite_lst_first(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
