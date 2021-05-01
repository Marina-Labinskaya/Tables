#include "tables.h"
#include "polynom.h"
#include <gtest.h>

TEST(THashTable, can_create_empty_hash_table) {
	HashTable<Polynom> tab;
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(THashTable, can_create_copied_hash_table) {
	HashTable<Polynom> tab1;
	ASSERT_NO_THROW(HashTable<Polynom> tab2(tab1));
}

TEST(THashTable, throws_if_key_is_not_found) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	ASSERT_ANY_THROW(tab.find(3));
}

TEST(THashTable, can_find_by_the_key) {
	HashTable<Polynom> tab;
	Polynom p;
	Polynom p2(p);
	tab.insert(1, p);
	tab.insert(5, p2);
	std::pair<std::size_t, Polynom> pr = std::make_pair(5, p);
	EXPECT_EQ(tab.find(5), pr);
}

TEST(THashTable, can_insert_if_key_is_unique) {
	HashTable<Polynom> tab;
	Polynom p;
	EXPECT_EQ(tab.insert(1, p), true);
}

TEST(THashTable, insert_changes_size) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	EXPECT_EQ(tab.getSize(), 1);
}

TEST(THashTable, can_insert_correctly) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	std::pair<std::size_t, Polynom> pr = std::make_pair(1, p);
	EXPECT_EQ(tab.find(1), pr);
}

TEST(THashTable, cant_insert_if_value_of_key_exists) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	EXPECT_EQ(tab.insert(1, p), false);
}

TEST(THashTable, can_erase_if_key_exists) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	EXPECT_EQ(tab.erase(1), true);
}

TEST(THashTable, can_erase_correctly) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	tab.erase(1);
	EXPECT_EQ(tab.getSize(), 0);
}

TEST(THashTable, cant_erase_if_key_does_not_exist) {
	HashTable<Polynom> tab;
	Polynom p;
	tab.insert(1, p);
	EXPECT_EQ(tab.erase(3), false);
}
