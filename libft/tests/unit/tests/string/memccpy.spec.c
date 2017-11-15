#include <project.h>
#include "stringft.h"

#define memccpy_test(num, size_dst, dst_, src_, limit, len, debug)	\
static void		test_## num(t_test *test)					\
{															\
	char		dst[size_dst], ft_dst[size_dst], src[] = src_;	\
	char		*ret, *ft_ret;								\
	bzero(dst, size_dst); strcat(dst, dst_);				\
	bzero(ft_dst, size_dst); strcat(ft_dst, dst_);			\
	ret = memccpy(dst, src, limit, len);					\
	ft_ret = ft_memccpy(ft_dst, src, limit, len);			\
	if (debug) {											\
		printf("=====> memccpy(%s, %s, %c, %i)\n", dst_, src_, limit, len);	\
		printf("Expected: %s\n", dst);						\
		printf("Actual:   %s\n", ft_dst);					\
	}														\
	if (!ret) { mt_assert(ret == ft_ret); }					\
	else { mt_assert(strcmp(dst, ft_dst) == 0); }			\
	mt_assert(memcmp(dst, ft_dst, size_dst) == 0);			\
}

memccpy_test(num01, 8, "Bonjour", "Salut", 'z', 5, false);
memccpy_test(num02, 8, "Bonjour", "Salut", 'l', 5, false);
memccpy_test(num03, 8, "Bonjour", "Salut", 'z', 3, false);
memccpy_test(num04, 8, "Bonjour", "Salut", 'u', 3, false);
memccpy_test(num05, 8, "Bonjour", "Salut", 'u', 0, false);
memccpy_test(num06, 8, "Bonjour", "Sa\200ut", '\200', 5, false);
memccpy_test(num07, 8, "Bonjour", "Salut\0\0\0\0\0\0", '\0', 8, false);

void suite_memccpy(t_suite *suite)
{
	SUITE_ADD_TEST(suite, test_num01);
	SUITE_ADD_TEST(suite, test_num02);
	SUITE_ADD_TEST(suite, test_num03);
	SUITE_ADD_TEST(suite, test_num04);
	SUITE_ADD_TEST(suite, test_num05);
	SUITE_ADD_TEST(suite, test_num06);
	SUITE_ADD_TEST(suite, test_num07);
}
