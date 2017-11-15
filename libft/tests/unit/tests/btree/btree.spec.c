#include <project.h>
#include "btree.h"

static int		lol(void *a, void *b)
{
	return (strcmp(a, b));
}

static void		pouet(t_test *test)
{
	t_btree		*tree;

	tree = btree_new(lol);
	btree_insert(tree, "ccc");
	btree_insert(tree, "bbb");
	btree_insert(tree, "aaa");
	btree_insert(tree, "baa");
	btree_insert(tree, "abb");
	btree_insert(tree, "bab");
	btree_insert(tree, "aba");
	btree_insert(tree, "ddd");
	btree_insert(tree, "eee");
	btree_insert(tree, "dee");
	btree_insert(tree, "edd");
	btree_insert(tree, "ded");
	btree_insert(tree, "ede");
	mt_assert(btree_exists(tree, "aaa"));
	mt_assert(!btree_exists(tree, "aca"));
}

void suite_btree(t_suite *suite)
{
	SUITE_ADD_TEST(suite, pouet);
}
