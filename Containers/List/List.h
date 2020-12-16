#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include "../../Common/CommonHeaders.h"

namespace SEPOLIA4::CONTAINERS
{
	template<typename T>
	class Node
	{
	public:

		explicit Node(T val)
		{
			value = val;
		}

		T value = -1;
		Node* next = nullptr;

		virtual ~Node()
		{
			if (SEPOLIA4::DEBUG_PRINT)
			{
				std::cout << "-->> ~Node() -->> " << value << std::endl;
			}
		}
	};

	template<typename T>
	class List
	{
	public:

		List() = default;

		List(const List& other)
		{
			List list;
			auto tmp = other.head;
			while (tmp)
			{
				list.Insert(tmp->value);
				tmp = tmp->next;
			}

			head = list.head;
			size = other.size;
			list.head = nullptr;
		}

		List& operator=(const List& other)
		{
			if (&other != this)
			{
				List list;
				Node<T>* tmp = other.head;
				while (tmp)
				{
					list.Insert(tmp->value);
					tmp = tmp->next;
				}

				head = list.head;
				size = other.size;
				list.head = nullptr;
			}
			return *this;
		}

		List(List&& other) noexcept
		{
			if (&other != this)
			{
				head = other.head;
				size = other.size;
				other.head = nullptr;
				other.size = 0;
			}
		}

		List& operator=(List&& other) noexcept
		{
			if (&other != this)
			{
				head = other.head;
				size = other.size;
				other.head = nullptr;
				other.size = 0;
			}
			return *this;
		}

		List(const std::initializer_list<T>& l)
		{
			for (const auto& el: l)
			{
				Insert(el);
			}
		}

		explicit List(const std::vector<T>& v)
		{
			for (const auto& el: v)
			{
				Insert(el);
			}
		}

		void Append(const std::initializer_list<T>& l)
		{
			for (const auto& el: l)
			{
				Insert(el);
			}
		}

		void Append(const std::vector<T>& l)
		{
			for (const auto& el: l)
			{
				Insert(el);
			}
		}

		void Insert(T v)
		{
			auto newNode = new Node(v);

			if (head == nullptr)
			{
				lastNode = newNode;
				head = newNode;
				size++;
			}
			else
			{
				lastNode->next = newNode;
				lastNode = newNode;
				size++;
			}
		}

		void Print() const
		{
			if (SEPOLIA4::DEBUG_PRINT)
			{
				auto tmp = head;

				while (tmp)
				{
					std::cout << "-->> Print() -->> " << tmp->value << std::endl;
					tmp = tmp->next;
				}
			}
		}

		int EraseOne(T value)
		{
			auto tmp = head;

			// check the first element
			if (tmp && tmp->value == value)
			{
				head = head->next;
				delete tmp;
				size--;
				return 0;
			}

			// check the rest elements
			while (tmp)
			{
				if (tmp->next && tmp->next->value == value)
				{
					auto tmp2 = tmp->next->next;
					delete tmp->next;
					size--;
					tmp->next = tmp2;
					return 0;
				}
				tmp = tmp->next;
			}

			return -1;
		}

		int EraseAll(T value)
		{
			int errorCode = 0;

			while (errorCode == 0)
			{
				errorCode = EraseOne(value);
			}

			return errorCode;
		}

		void Clear()
		{
			while (head)
			{
				auto tmp = head;
				head = head->next;
				delete tmp;
				size--;
			}

			head = nullptr;
		}

		[[nodiscard]] size_t Size() const
		{
			return size;
		}

		[[nodiscard]] bool Empty() const
		{
			return size == 0;
		}

		void Reverse()
		{
			auto current = head;
			Node<T>* prev = nullptr;
			Node<T>* next;

			while (current)
			{
				// Store next
				next = current->next;

				// Reverse current node's pointer
				current->next = prev;

				// Move pointers one position ahead.
				prev = current;
				current = next;
			}
			head = prev;
		}

		[[nodiscard]] int64_t FindOne(T v) const
		{
			auto tmp = head;
			int64_t pos = -1;

			while (tmp)
			{
				pos++;
				if (tmp->value == v)
				{
					return pos;
				}
				tmp = tmp->next;
			}
			return -1;
		}

		[[nodiscard]] std::vector<int64_t> FindAll(T v) const
		{
			auto tmp = head;
			int64_t pos = -1;
			std::vector<int64_t> positions;

			while (tmp)
			{
				pos++;
				if (tmp->value == v)
				{
					positions.push_back(pos);
				}
				tmp = tmp->next;
			}
			return positions;
		}

		virtual ~List()
		{
			Clear();
		}

	private:

		Node<T>* lastNode = nullptr;
		Node<T>* head = nullptr;
		size_t size = 0;
	};
}