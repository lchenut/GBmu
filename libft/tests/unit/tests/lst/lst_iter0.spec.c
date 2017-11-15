#include <project.h>
#include "lst.h"

static void	get_size(void *data, void *ctx)
{
	*((size_t *)ctx) += strlen(data);
}

static void	concat(void *data, void *ctx)
{
	strcat(ctx, data);
}

static void	simple_test(t_test *test)
{
	t_lst	*lst;
	size_t	len;
	char	*tmp;

	lst = lst_new();
	lst_push_front(lst, "AAA");
	lst_push_front(lst, "BBB");
	lst_push_front(lst, "CCC");
	len = 0;
	lst_iter(lst, get_size, &len);
	mt_assert(len == 9);
	tmp = malloc(len + 1);
	bzero(test, len + 1);
	lst_iter(lst, concat, tmp);
	mt_assert(strcmp(tmp, "CCCBBBAAA") == 0);
	free(tmp);
	lst_del(lst, NULL);
}

void		suite_lst_iter0(t_suite *suite)
{
	SUITE_ADD_TEST(suite, simple_test);
}
