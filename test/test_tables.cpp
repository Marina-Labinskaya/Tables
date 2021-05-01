#include "tables.h"

#include <gtest.h>

TEST(TUnorderedTable, can_create_empty_unordered_table) {
	UnorderedTable<int> tab;
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(TUnorderedTable, can_create_copied_unordered_table) {
	UnorderedTable<int> tab1;
	ASSERT_NO_THROW(UnorderedTable<int> tab2(tab1));
}

TEST(TUnorderedTable, throws_if_key_is_not_found) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	ASSERT_ANY_THROW(tab.find(3));
}

TEST(TUnorderedTable, can_find_by_the_key) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	tab.insert(5, 2);
	std::pair<std::size_t, int> pr = std::make_pair(5, 2);
	EXPECT_EQ(tab.find(5), pr);
}

TEST(TUnorderedTable, can_insert_if_key_is_unique) {
	UnorderedTable<int> tab;
	EXPECT_EQ(tab.insert(1, 7), true);
}

TEST(TUnorderedTable, insert_changes_size) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.getSize(), 1);
}

TEST(TUnorderedTable, can_insert_correctly) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	std::pair<std::size_t, int> pr = std::make_pair(1, 7);
	EXPECT_EQ(tab.find(1), pr);
}

TEST(TUnorderedTable, cant_insert_if_value_of_key_exists) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.insert(1, 5), false);
}

TEST(TUnorderedTable, can_erase_if_key_exists) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.erase(1), true);
}

TEST(TUnorderedTable, can_erase_correctly) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	tab.erase(1);
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(TUnorderedTable, cant_erase_if_key_does_not_exist) {
	UnorderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.erase(3), false);
}

TEST(TOrderedTable, can_create_empty_ordered_table) {
	OrderedTable<int> tab;
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(TOrderedTable, can_create_copied_ordered_table) {
	OrderedTable <int> tab1;
	ASSERT_NO_THROW(OrderedTable<int> tab2(tab1));
}

TEST(TOrderedTable, throws_if_key_is_not_found) {
	OrderedTable <int> tab;
	ASSERT_ANY_THROW(tab.find(1));
}

TEST(TOrderedTable, can_find_by_the_key) {
	OrderedTable <int> tab;
	tab.insert(1, 7);
	std::pair<std::size_t, int> pr = std::make_pair(1, 7);
	EXPECT_EQ(tab.find(1), pr);
}

TEST(TOrderedTable, can_insert_in_empty_ordered_table) {
	OrderedTable<int> tab;
	EXPECT_EQ(tab.insert(1, 7), true);
}

TEST(TOrderedTable, can_insert_in_not_empty_ordered_table) {
	OrderedTable<int> tab;
	tab.insert(2, 4);
	EXPECT_EQ(tab.insert(1, 7), true);
}

TEST(TOrderedTable, can_insert_in_ordered_table_correctly) {
	OrderedTable<int> tab;
	tab.insert(2, 4);
	tab.insert(1, 7);
	std::pair<std::size_t, int> pr = std::make_pair(1, 7);
	EXPECT_EQ(tab.find(1), pr);
}

TEST(TOrderedTable, insert_changes_size) {
	OrderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.getSize(), 1);
}

TEST(TOrderedTable, cant_insert_if_value_of_key_exists) {
	OrderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.insert(1, 5), false);
}

TEST(TOrderedTable, can_erase_if_key_exists) {
	OrderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.erase(1), true);
}

TEST(TOrderedTable, can_erase_correctly) {
	OrderedTable<int> tab;
	tab.insert(1, 7);
	tab.erase(1);
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(TOrderedTable, cant_erase_if_key_does_not_exist) {
	OrderedTable<int> tab;
	tab.insert(1, 7);
	EXPECT_EQ(tab.erase(3), false);
}