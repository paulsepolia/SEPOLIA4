#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

namespace SEPOLIA4::CONTAINERS
{
	class Node
	{
	public:

		explicit Node(double v);

		double value = -1;
		Node* next = nullptr;

		virtual ~Node();
	};

	class List
	{
	public:

		List();

		List(const List& other);

		List& operator=(const List& other);

		List(List&& other) noexcept;

		List& operator=(List&& other) noexcept;

		List(const std::initializer_list<double>& l);

		explicit List(const std::vector<double>& v);

		void Append(const std::initializer_list<double>& l);

		void Append(const std::vector<double>& l);

		void Insert(double v);

		void Print() const;

		int EraseOne(double value);

		int EraseAll(double value);

		void Clear();

		[[nodiscard]] size_t Size() const;

		[[nodiscard]] bool Empty() const;

		void Reverse();

		[[nodiscard]] int64_t FindOne(double v) const;

		[[nodiscard]] std::vector<int64_t> FindAll(double v) const;

		virtual ~List();

	private:

		Node* lastNode = nullptr;
		Node* head = nullptr;
		size_t size = 0;
	};
}