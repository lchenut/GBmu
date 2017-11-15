#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	mt_assert(lst_len(lst) == 0);
	lst_push_front(lst, "1");
	lst_push_front(lst, "2");
	lst_push_front(lst, "3");
	lst_push_front(lst, "4");
	lst_push_front(lst, "5");
	lst_push_front(lst, "6");
	mt_assert(lst_len(lst) == 6);
	lst_del(lst, NULL);
}

static void	test_multiple_add_and_pop(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	lst_pop_front(lst);
	mt_assert(lst_len(lst) == 0);
	lst_push_front(lst, "1");
	lst_push_back(lst, "2");
	lst_insert(lst, "3", 1);
	lst_push_front(lst, "4");
	lst_push_back(lst, "5");
	lst_insert(lst, "6", 0);
	mt_assert(lst_len(lst) == 6);
	lst_pop_front(lst);
	mt_assert(lst_len(lst) == 5);
	lst_pop_back(lst);
	mt_assert(lst_len(lst) == 4);
	lst_pop(lst, 2);
	mt_assert(lst_len(lst) == 3);
	lst_del(lst, NULL);
}

void		suite_lst_len(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
	SUITE_ADD_TEST(suite, test_multiple_add_and_pop);
}
