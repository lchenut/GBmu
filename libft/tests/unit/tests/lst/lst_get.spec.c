#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	mt_assert(lst_get(lst, 0) == NULL);
	mt_assert(lst_get(lst, 50) == NULL);
	lst_push_front(lst, "Coucou");
	mt_assert(strcmp(lst_get(lst, 0), "Coucou") == 0);
	mt_assert(strcmp(lst_get(lst, -1), "Coucou") == 0);
	mt_assert(lst_get(lst, 50) == NULL);
	lst_del(lst, NULL);
}

static void	test_multiple_add(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	lst_push_back(lst, "Coucou0");
	lst_push_back(lst, "Coucou1");
	lst_push_back(lst, "Coucou2");
	lst_push_back(lst, "Coucou3");
	lst_push_back(lst, "Coucou4");
	lst_push_back(lst, "Coucou5");
	lst_push_back(lst, "Coucou6");
	mt_assert(strcmp(lst_get(lst, 0), "Coucou0") == 0);
	mt_assert(strcmp(lst_get(lst, 1), "Coucou1") == 0);
	mt_assert(strcmp(lst_get(lst, 2), "Coucou2") == 0);
	mt_assert(strcmp(lst_get(lst, 3), "Coucou3") == 0);
	mt_assert(strcmp(lst_get(lst, 4), "Coucou4") == 0);
	mt_assert(strcmp(lst_get(lst, 5), "Coucou5") == 0);
	mt_assert(strcmp(lst_get(lst, 6), "Coucou6") == 0);
	mt_assert(strcmp(lst_get(lst, -1), "Coucou6") == 0);
	mt_assert(strcmp(lst_get(lst, -2), "Coucou5") == 0);
	mt_assert(strcmp(lst_get(lst, -3), "Coucou4") == 0);
	mt_assert(strcmp(lst_get(lst, -4), "Coucou3") == 0);
	mt_assert(strcmp(lst_get(lst, -5), "Coucou2") == 0);
	mt_assert(strcmp(lst_get(lst, -6), "Coucou1") == 0);
	mt_assert(strcmp(lst_get(lst, -7), "Coucou0") == 0);
	mt_assert(lst_get(lst, 7) == NULL);
	lst_del(lst, NULL);
}

void		suite_lst_get(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
	SUITE_ADD_TEST(suite, test_multiple_add);
}
