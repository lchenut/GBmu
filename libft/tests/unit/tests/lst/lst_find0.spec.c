#include <project.h>
#include "lst.h"

static bool	ret_false(void *data) { (void)data; return (0); }
static bool	findA(void *data) { return (*((char *)data) == 'A'); }
static bool	findB(void *data) { return (*((char *)data) == 'B'); }
static bool	findC(void *data) { return (*((char *)data) == 'C'); }

static void	simple_test(t_test *test)
{
	t_lst	*lst;

	lst = lst_new();
	lst_push_front(lst, "AAA");
	lst_push_front(lst, "BBB");
	lst_push_front(lst, "CCC");
	mt_assert(lst_find0(lst, ret_false) == NULL);
	mt_assert(strcmp(lst_find0(lst, findA), "AAA") == 0);
	mt_assert(strcmp(lst_find0(lst, findB), "BBB") == 0);
	mt_assert(strcmp(lst_find0(lst, findC), "CCC") == 0);
	lst_del(lst, NULL);
}

void		suite_lst_find0(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
