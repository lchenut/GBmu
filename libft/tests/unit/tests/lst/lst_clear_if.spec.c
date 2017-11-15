#include <project.h>
#include <string.h>
#include "lst.h"

static bool		find_nothing(void *data, void *context)
{
	(void)data;
	(void)context;
	return (false);
}

static bool		find_a(void *data, void *context)
{
	return (((char *)data)[0] == 'a');
	(void)context;
}

static void		test_simple(t_test *test)
{
	t_lst		*lst;

	lst = lst_new();
	lst_clear_if(lst, NULL, find_nothing, NULL);
	mt_assert(lst_pop_front(lst) == NULL);
	lst_push_front(lst, strdup("aaabbb"));
	lst_push_front(lst, strdup("cccbbb"));
	lst_push_front(lst, strdup("aaaddd"));
	lst_push_front(lst, strdup("eeebbb"));
	lst_push_front(lst, strdup("aaafff"));
	lst_push_front(lst, strdup("gggbbb"));
	lst_push_front(lst, strdup("aaahhh"));
	mt_assert(lst_len(lst) == 7);
	lst_clear_if(lst, free, find_nothing, NULL);
	mt_assert(lst_len(lst) == 7);
	lst_clear_if(lst, free, find_a, NULL);
	mt_assert(lst_len(lst) == 3);
	mt_assert(strcmp(lst_first(lst), "gggbbb") == 0);
	lst_del(lst, free);
}

void			suite_lst_clear_if(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_simple);
}
