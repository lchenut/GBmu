#include <project.h>
#include "xstring.h"

static void		free_arr(char **arr)
{
	size_t		index;
	index = 0;
	while (arr[index])
	{
		free(arr[index]);
		index += 1;
	}
	free(arr);
}

static size_t	len_arr(char **arr)
{
	size_t		index;
	index = 0;
	while (arr[index])
	{
		index += 1;
	}
	return (index);
}

static void		dump_arr(char **arr)
{
	size_t		index;
	index = 0;
	while (arr[index])
	{
		printf("%zu: >%s<\n", index, arr[index]);
		index += 1;
	}
}

static void		test_simple01(t_test *test)
{
	const char	*src = "B o n j o u r";
	char		**dst;
	dst = ft_strsplit(src, ' ');
	mt_assert(len_arr(dst) == 7);
	mt_assert(strcmp(dst[0], "B") == 0);
	mt_assert(strcmp(dst[1], "o") == 0);
	mt_assert(strcmp(dst[2], "n") == 0);
	mt_assert(strcmp(dst[3], "j") == 0);
	mt_assert(strcmp(dst[4], "o") == 0);
	mt_assert(strcmp(dst[5], "u") == 0);
	mt_assert(strcmp(dst[6], "r") == 0);
	free_arr(dst);
}

static void		test_simple02(t_test *test)
{
	const char	*src = "Bonjour";
	char		**dst;
	dst = ft_strsplit(src, ' ');
	mt_assert(len_arr(dst) == 1);
	mt_assert(strcmp(dst[0], "Bonjour") == 0);
	free_arr(dst);
}

static void		test_simple03(t_test *test)
{
	const char	*src1 = "";
	const char	*src2 = "                   ";
	char		**dst;
	dst = ft_strsplit(src1, ' ');
	mt_assert(len_arr(dst) == 0);
	free_arr(dst);
	dst = ft_strsplit(src2, ' ');
	mt_assert(len_arr(dst) == 0);
	free_arr(dst);
}

static void		big_string(t_test *test)
{
	char		*src;
	char		**dst;
	src = malloc(100000);
	bzero(src, 100000);
	memset(src, 'A', 50000);
	src[50000] = ' ';
	memset(src + 50001, 'B', 40000);
	dst = ft_strsplit(src, ' ');
	src[50000] = '\0';
	mt_assert(len_arr(dst) == 2);
	mt_assert(strcmp(dst[0], src) == 0);
	mt_assert(strcmp(dst[1], src + 50001) == 0);
	free(src);
	free_arr(dst);
}

void suite_strsplit(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_simple01);
	SUITE_ADD_TEST(suite, test_simple02);
	SUITE_ADD_TEST(suite, test_simple03);
	SUITE_ADD_TEST(suite, big_string);
}
