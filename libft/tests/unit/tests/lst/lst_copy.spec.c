#include <project.h>
#include "lst.h"

static void	simple_test(t_test *test)
{
	t_lst	*lst;
	t_lst	*copy;

	lst = lst_new();
	lst_push_back(lst, "AAA");
	lst_push_back(lst, "BBB");
	lst_push_back(lst, "CCC");
	copy = lst_copy(lst, NULL);
	mt_assert(lst_len(lst) == lst_len(copy));
	mt_assert(lst_get(lst, 0) == lst_get(copy, 0));
	mt_assert(lst_get(lst, 1) == lst_get(copy, 1));
	mt_assert(lst_get(lst, 2) == lst_get(copy, 2));
	lst_del(lst, NULL);
	lst_del(copy, NULL);
}

static void	*copy_fn(void *data)
{
	char	*ret;

	ret = strdup(data);
	for (int i = 0, len = strlen(ret); i < len; i += 1)
	{
		ret[i] += 1;
	}
	return (ret);
}

static void	middle_test(t_test *test)
{
	t_lst	*lst;
	t_lst	*copy;

	lst = lst_new();
	lst_push_back(lst, "AAA");
	lst_push_back(lst, "CCC");
	lst_push_back(lst, "EEE");
	copy = lst_copy(lst, copy_fn);
	mt_assert(lst_len(lst) == lst_len(copy));
	mt_assert(strcmp(lst_get(copy, 0), "BBB") == 0);
	mt_assert(strcmp(lst_get(copy, 1), "DDD") == 0);
	mt_assert(strcmp(lst_get(copy, 2), "FFF") == 0);
	lst_del(lst, NULL);
	lst_del(copy, free);
}

void		suite_lst_copy(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
	SUITE_ADD_TEST(suite, middle_test);
}
