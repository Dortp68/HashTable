#pragma once
//#include "Log.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
template<typename T>
class HashTable
{
public:
	explicit HashTable(size_t size = 10);
	HashTable(const HashTable& other);
	HashTable(HashTable&& other) noexcept;
	~HashTable();
	HashTable& operator=(const HashTable& other);
	HashTable& operator=(HashTable&& other) noexcept;
	static size_t Getsize();
	void Info() const;
	void Add(const std::string& key, const T& data);
	void Clear();
private:
	size_t HashFunc(const std::string& key) const;
	template<typename T>
	class Node
	{
	public:
		T data;
		std::string key;
		Node* pNext;
		explicit Node(const std::string& key = std::string(), const T& data = T(), Node* pNext = nullptr) : key(key), data(data), pNext(pNext)
		{
		}
		~Node()
		{
		}
		Node& operator=(const T& data)
		{
			this->data = data;
			return *this;
		}
		void Get() const
		{
			std::cout << "[key: " << key << " | data: " << data << "]";
		}
		friend std::ostream& operator<< (std::ostream& out, const Node& node)
		{
			out << node.data;
			return out;
		}
	};
	size_t size;
	Node<T>** List_;
public:
	Node<T>& operator[](const std::string key);
	const Node<T>& operator[](const std::string key) const;
};

