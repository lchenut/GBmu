#include <project.h>
#include "lst.h"

static void		test_simple(t_test *test)
{
	t_lst		*lst;

	lst = lst_new();
	mt_assert(lst_pop(lst, 0) == NULL);
	lst_push_front(lst, "3");
	lst_push_front(lst, "2");
	lst_push_front(lst, "1");
	mt_assert(strcmp(lst_pop(lst, 1), "2") == 0);
	mt_assert(strcmp(lst_pop(lst, 1), "3") == 0);
	mt_assert(strcmp(lst_pop(lst, 0), "1") == 0);
	mt_assert(lst_pop(lst, 3) == NULL);
	mt_assert(lst_len(lst) == 0);
	lst_del(lst, NULL);
}

static void		test_overflow(t_test *test)
{
	t_lst		*lst;

	lst = lst_new();
	mt_assert(lst_pop(lst, 0) == NULL);
	lst_push_front(lst, "3");
	lst_push_front(lst, "2");
	lst_push_front(lst, "1");
	mt_assert(lst_pop(lst, 5) == NULL);
	mt_assert(strcmp(lst_pop(lst, -2), "2") == 0);
	mt_assert(strcmp(lst_pop(lst, -1), "3") == 0);
	mt_assert(strcmp(lst_pop(lst, -1), "1") == 0);
	mt_assert(lst_pop(lst, -3) == NULL);
	mt_assert(lst_len(lst) == 0);
	lst_del(lst, NULL);
}

void			suite_lst_popi(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_simple);
	SUITE_ADD_TEST(suite, test_overflow);
}
