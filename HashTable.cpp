#include "HashTable.h"

template<typename T>
HashTable<T>::HashTable(size_t size) : size(size)
{
	List_ = new Node<T>*[size];
	for (size_t i = 0; i < size; i++)
	{
		List_[i] = nullptr;
	}
}

template<typename T>
HashTable<T>::HashTable(const HashTable& other) : size(other.size)
{
	List_ = new Node<T>*[size];
	for (size_t i = 0; i < size; i++)
	{
		if (other.List_[i] == nullptr)
		{
			List_[i] = nullptr;
		}
		else
		{
			List_[i] = new Node<T>(other.List_[i]->key, other.List_[i]->data, other.List_[i]->pNext, other.List_[i]->appeals);
			Node<T>* current = List_[i];
			Node<T>* next = other.List_[i]->pNext;
			while (next != nullptr)
			{
				current->pNext = new Node<T>(next->key, next->data, next->pNext, next->appeals);
				current = current->pNext;
				next = next->pNext;
			}
		}	
	}
}

template<typename T>
HashTable<T>::HashTable(HashTable&& other) noexcept
{
	std::swap(List_, other.List_);
	std::swap(size, other.size);
}

template<typename T>
HashTable<T>::~HashTable()
{
	this->Clear();
	delete[] List_;
}
template<typename T>
size_t HashTable<T>::Getsize()
{
	return size;
}

template<typename T>
void HashTable<T>::Info() const
{
	std::cout << "HashTable" << std::endl;
	size_t flag = 1;
	for (size_t i = 0; i < size; i++)
	{
		if (List_[i]!=nullptr)
		{
			flag = 0;
			std::cout << "index " << i << "=> {";
			Node<T>* current = List_[i];
			while (current != nullptr)
			{
				current->Get();
				current = current->pNext;
			}
			std::cout << "}" << std::endl;
		}
	}
	if (flag)
	{
		std::cout << "{Empty}"<<std::endl;
	}
}

template<typename T>
void HashTable<T>::Add(const std::string& key, const T& data)
{
	size_t id = this->HashFunc(key);
	if (List_[id] == nullptr)
	{
		List_[id] = new Node<T>(key, data);
	}
	else
	{
		Node<T>* current = List_[id];
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(key, data);
	}
}

template<typename T>
void HashTable<T>::Clear()
{
	for (size_t i = 0; i < size; i++)
	{
		while (List_[i] != nullptr)
		{
			Node<T>* tmp = List_[i];
			List_[i] = List_[i]->pNext;
			delete tmp;
		}
	}
}




template<typename T>
size_t HashTable<T>::HashFunc(const std::string& key) const
{
	size_t hashval = 0;
	for (size_t i = 0; i < key.size(); i++)
	{
		hashval += key[i] + 31 * hashval;
	}
	return (hashval % size);
}


template<typename T>
HashTable<T>::Node<T>& HashTable<T>::operator[](const std::string key)
{
	size_t id = this->HashFunc(key);
	Node<T>* tmp = List_[id];
	size_t flag = 0;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
		{
			flag++;
			return (*tmp);
		}
		tmp = tmp->pNext;
	}
	assert(flag, "Key does not found");
}

template<typename T>
const HashTable<T>::Node<T>& HashTable<T>::operator[](const std::string key) const
{
	size_t id = this->HashFunc(key);
	Node<T>* tmp = List_[id];
	size_t flag = 0;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
		{
			flag++;
			return (*tmp);
		}
		tmp = tmp->pNext;
	}
	assert(flag, "Key does not found");
}



template<typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable& other)
{
	if (this != &other)
	{
		this->Clear();
		delete[] List_;
		size = other.size;
		List_ = new Node<T>*[size];
		for (size_t i = 0; i < size; i++)
		{
			if (other.List_[i] == nullptr)
			{
				List_[i] = nullptr;
			}
			else
			{
				List_[i] = new Node<T>(other.List_[i]->key, other.List_[i]->data, other.List_[i]->pNext);
				Node<T>* current = List_[i];
				Node<T>* next = other.List_[i]->pNext;
				while (next != nullptr)
				{
					current->pNext = new Node<T>(next->key, next->data, next->pNext);
					current = current->pNext;
					next = next->pNext;
				}
			}
		}
	}
	return *this;
}

template<typename T>
HashTable<T>& HashTable<T>::operator=(HashTable&& other) noexcept
{
	std::swap(List_, other.List_);
	std::swap(size, other.size);
	std::cout << "move =" << std::endl;
	return(*this);
}