#include <project.h>
#include "lst.h"

static void		test_simple(t_test *test)
{
	t_lst		*lst;

	lst = lst_new();
	mt_assert(lst_pop_back(lst) == NULL);
	lst_push_front(lst, "3");
	lst_push_front(lst, "2");
	lst_push_front(lst, "1");
	mt_assert(strcmp(lst_pop_back(lst), "3") == 0);
	mt_assert(strcmp(lst_pop_back(lst), "2") == 0);
	mt_assert(strcmp(lst_pop_back(lst), "1") == 0);
	mt_assert(lst_pop_back(lst) == NULL);
	mt_assert(lst_len(lst) == 0);
	lst_del(lst, NULL);
}

void			suite_lst_popb(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_simple);
}
