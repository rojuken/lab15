#include <../gtest/gtest.h>
#include "TMapTree.h"
#include <vector>

using namespace std;

TEST(TMapTree, can_create_tree_map)
{
	TMapTree<int, int> a;
	ASSERT_NO_THROW(a);
}

TEST(TMapTree, can_add_elem)
{
	TMapTree<string, int> a;
	a.Add("Hello", 10);
	EXPECT_EQ(10, a["Hello"]);
}

TEST(TMapTree, can_find_elem)
{
	TMapTree<string, int> a;
	a.Add("Hello", 10);
	a.Add("World", 20);
	a.Add("nice", 30);
	EXPECT_EQ(20, a.Find("World"));
}

TEST(TMapTree, can_delete_elem)
{
	TMapTree<string, int> a;
	a.Add("Hello", 10);
	a.Add("World", 20);
	a.Add("nice", 30);
	a.Delete("nice");
	ASSERT_ANY_THROW(a.Find("nice"));
}

TEST(TTreeMap, can_iterate_object)
{
	TMapTree<string, int> a;
	a.Add("Hello", 20);
	a.Add("World", 30);
	a.Add("nice", 10);
	int sorted[3] = { 20, 30, 10 };
	int i = 0;
	TMapTree<string, int>::iterator it = a.Begin();
	while (it.IsEnd()) {
		EXPECT_EQ(sorted[i], it.Get()->GetVal());
		it.GoNext();
		i++;
	}
}

