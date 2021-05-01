#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <list>

template <class T>
class TableInterface {
public:
	virtual bool insert(std::size_t _key, const T& elem) = 0;
	virtual bool erase(std::size_t _key) = 0;
	virtual std::pair<std::size_t, T> find(std::size_t _key) = 0;

	virtual std::size_t getSize() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
};

template<class T, class CellType = std::pair<std::size_t, T>>
class TableByArray : public TableInterface<T> {
protected:
	std::vector<CellType> storage;
	std::size_t size;
public:

	TableByArray() {
		storage = std::vector<CellType>();
		size = 0;
	}

	TableByArray(const TableByArray& tab) {
		storage = tab.storage;
		size = tab.size;
	}

	std::size_t getSize() override {
		return size;
	}

	void clear() override {
		storage.clear();
		size = 0;
	}

	bool isEmpty() override {
		return (size == 0);
	}
};

template<class T>
class OrderedTable : public TableByArray<T> {
public:
	OrderedTable() : TableByArray() {};
	OrderedTable(const TableByArray& tab) : TableByArray(tab) {};
	bool insert(size_t key, const T& elem) override {
		bool successful_insert = false;
		std::pair<size_t, T> pr = std::make_pair(key, elem);
		if (!isEmpty())
		{
			auto low = std::lower_bound(storage.begin(), storage.end(), pr);
			if (low != storage.end())
			{
				if (low->first != key) {
					storage.insert(low, pr);
					++size;
					successful_insert = true;
				}
			}
		}
		else {
			storage.push_back(pr);
			++size;
			successful_insert = true;
		}
		return successful_insert;
	}
	bool erase(size_t key) {
		bool successful_deletion = false;
		std::pair<size_t, T> pr = std::make_pair(key, T());
		auto low = std::lower_bound(storage.begin(), storage.end(), pr);
		if (low != storage.end())
		{
			if (low->first == key)
			{
				storage.erase(low);
				--size;
				successful_deletion = true;
			}
		}
		return successful_deletion;
	}
	std::pair<std::size_t, T> find(std::size_t key) override {
		std::pair<std::size_t, T> pr = std::make_pair(key, T());
		std::pair<std::size_t, T> res;
		auto low = std::lower_bound(storage.begin(), storage.end(), pr);
		if (low != storage.end())
		{
			if (low->first == key) {
				res = std::make_pair(key, low->second);
			}
			else
				throw std::logic_error("Field with this key was not found");
		}
		else
			throw std::logic_error("Field with this key was not found");
		return res;
	}
};

template<class T>
class UnorderedTable : public TableByArray<T> {
private:
	std::size_t get_index(std::size_t key) {
		std::size_t index = -1;
		for (std::size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				index = i;
				break;
			}
		}
		return index;
	}
public:
	UnorderedTable() : TableByArray() {};
	UnorderedTable(const TableByArray& tab) : TableByArray(tab) {};
	bool insert(std::size_t key, const T& elem) override {
		bool successful_insert;
		if (get_index(key) != -1)
			successful_insert = false;
		else {
			storage.push_back(std::make_pair(key, elem));
			++size;
			successful_insert = true;
		}
		return successful_insert;
	}
	bool erase(std::size_t key) override {
		bool successful_deletion = false;
		for (std::size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				storage[i] = storage[size - 1];
				storage.pop_back();
				--size;
				successful_deletion = true;
				break;
			}
		}
		return successful_deletion;
	}
	std::pair<std::size_t, T> find(std::size_t key) override {
		bool successful_search = false;
		std::pair<std::size_t, T> res;
		for (std::size_t i = 0; i < size; ++i) {
			if (storage[i].first == key) {
				successful_search = true;
				res = std::make_pair(key, storage[i].second);
				break;
			}
		}
		if (!successful_search)
			throw std::logic_error("Field with this key was not found");
		return res;
	}
};

template<class T>
class HashTable : public TableByArray<T, std::list<std::pair<std::size_t, T>>> {
private:
	void resize(std::size_t new_size) {
		std::vector <std::list<std::pair<std::size_t, T>>> vec(new_size);
		for (std::size_t i = 0; i < size; ++i)
			for (std::list <std::pair<std::size_t, T>>::iterator it = storage[i].begin(); it != storage[i].end(); ++it)
			{
				std::size_t new_index = hash_function(it->first);
				vec[new_index].push_back(std::make_pair(it->first, it->second));
			}
		storage = vec;
	}
public:
	HashTable() : TableByArray() {}
	HashTable(const TableByArray& tab) : TableByArray(tab) {}
	std::size_t hash_function(std::size_t key) {
		std::size_t p = 32749; // prime number
		size_t a = rand() % (p - 2) + 1;
		size_t b = rand() % (p - 1);

		return ((a * key + b) % p) % storage.size();
	}
bool insert(std::size_t key, const T& elem) override {
	bool successful_insertion = true;
	if (storage.size() == 0) {
		storage.resize(1);
		storage[0].push_back(std::make_pair(key, elem));
		++size;
	}
	else {
		if ((double(size) / double(storage.size())) > 0.7)
			resize(2 * storage.size());
		std::size_t index = hash_function(key);
		for (std::list <std::pair<std::size_t, T>>::iterator it = storage[index].begin(); it != storage[index].end(); ++it) {
			if (it->first == key)
				successful_insertion = false;
			break;
		}
		if (successful_insertion) {
			storage[index].push_back(std::make_pair(key, elem));
			++size;
		}
	}
	return successful_insertion;
}
bool erase(std::size_t key) override {
	bool successful_deletion = false;
	if (storage.size()) {
		std::size_t index = hash_function(key);
		for (std::list < std::pair<std::size_t, T>>::iterator it = storage[index].begin(); it != storage[index].end(); ++it) {
			if (it->first == key)
			{
				storage[index].erase(it);
				--size;
				successful_deletion = true;
				break;
			}
		}
	}
	return successful_deletion;
}
std::pair<std::size_t, T> find(std::size_t key) override {
	bool successful_search = false;
	std::pair<std::size_t, T> res;
	if (storage.size()) {
		std::size_t index = hash_function(key);
		for (std::list < std::pair<std::size_t, T>>::iterator it = storage[index].begin(); it != storage[index].end(); ++it) {
			if (it->first == key) {
				successful_search = true;
				res = std::make_pair(key, it->second);
				break;
			}
		}
	}
	if (!successful_search)
		throw std::logic_error("Field with this key was not found");
	return res;
}
};