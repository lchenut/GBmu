#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;
	char	*tmp;

	lst = lst_new();
	lst_push_front(lst, strdup("AAA"));
	lst_push_front(lst, strdup("CCC"));
	lst_push_front(lst, strdup("EEE"));
	lst_rev(lst);
	mt_assert(strcmp(lst_get(lst, 0), "AAA") == 0);
	mt_assert(strcmp(lst_get(lst, 1), "CCC") == 0);
	mt_assert(strcmp(lst_get(lst, 2), "EEE") == 0);
	lst_del(lst, free);
}

void		suite_lst_rev(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
