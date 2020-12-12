#include "List.h"
#include <iostream>
#include <cassert>

int main()
{

	{
		std::cout << "-->> example ---------------------------------->> 1" << std::endl;
		auto list = List();

		list.Insert(1);
		list.Insert(2);
		list.Insert(3);
		list.Insert(4);

		assert(list.Size() == 4);
		assert(list.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 2" << std::endl;
		auto list = List({ 1, 2 });

		list.Insert(3);
		list.Insert(4);
		list.Append({ 5, 6 });

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 3" << std::endl;

		auto list = List({ 1, 2 });

		list.Append({ 3, 4 });
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 4" << std::endl;

		std::vector<double> values{ 1, 2 };

		auto list = List(values);

		list.Append({ 3, 4 });
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 5" << std::endl;

		std::vector<double> values{ 1, 2 };

		auto list = List(values);

		std::vector<double> values2{ 3, 4 };

		list.Append(values2);
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 6" << std::endl;

		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		const auto list1 = List(values);
		const auto list2 = List(list1);

		assert(list1.Size() == 6);
		assert(list2.Size() == 6);
		assert(list1.Empty() == false);
		assert(list2.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 7" << std::endl;

		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		const auto list1 = List(values);
		const auto list2 = list1;

		std::cout << &list1 << std::endl;
		std::cout << &list2 << std::endl;

		assert(list1.Size() == 6);
		assert(list2.Size() == 6);
		assert(list1.Empty() == false);
		assert(list2.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 8" << std::endl;

		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		auto list1 = List(values);
		const auto list2 = List(std::move(list1));

		assert(list2.Size() == 6);
		assert(list2.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 9" << std::endl;

		std::vector<double> values{ 1, 2, 3, 4, 5, 6, 7 };

		auto list1 = List(values);
		const auto list2 = std::move(list1);

		std::cout << &list2 << std::endl;

		assert(list2.Size() == 7);
		assert(list2.Empty() == false);
	}

	{
		std::cout << "-->> example ---------------------------------->> 10" << std::endl;

		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		auto list = List(values);

		assert(list.Size() == 6);
		assert(list.Empty() == false);

		int v = 1;
		std::cout << "pgg -->> Erasing element: " << v << std::endl;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 5);
		assert(list.Empty() == false);

		v = 3;
		std::cout << "pgg -->> Erasing element: " << v << std::endl;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 4);
		assert(list.Empty() == false);

		v = 6;
		std::cout << "pgg -->> Erasing element: " << v << std::endl;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 3);
		assert(list.Empty() == false);
	}

	for (size_t kk = 0; kk < 100; kk++)
	{
		std::cout << "-->> example ---------------------------------->> 11 -->> " << kk << std::endl;

		std::vector<double> values{ 1, 2, 5, 1, 2, 4, 5 };

		auto list = List(values);
		assert(list.Size() == 7);
		assert(list.Empty() == false);

		int v = 1;
		std::cout << "pgg -->> Erasing all elements: " << v << std::endl;
		list.EraseAll(v);
		list.Print();
		assert(list.Size() == 5);
		assert(list.Empty() == false);

		v = 2;
		std::cout << "pgg -->> Erasing all elements: " << v << std::endl;
		list.EraseAll(v);
		list.Print();
		assert(list.Size() == 3);
		assert(list.Empty() == false);

		v = 5;
		std::cout << "pgg -->> Erasing all elements: " << v << std::endl;
		list.EraseAll(v);
		list.Print();
		assert(list.Size() == 1);
		assert(list.Empty() == false);

		v = 6;
		std::cout << "pgg -->> Erasing all elements: " << v << std::endl;
		list.EraseAll(v);
		list.Print();
		assert(list.Size() == 1);
		assert(list.Empty() == false);

		v = 4;
		std::cout << "pgg -->> Erasing all elements: " << v << std::endl;
		list.EraseAll(v);
		list.Print();
		assert(list.Size() == 0);
		assert(list.Empty() == true);
	}

	for (size_t kk = 0; kk < 10; kk++)
	{
		std::cout << "-->> example ---------------------------------->> 12 -->> " << kk << std::endl;

		std::vector<double> values(10, 1);

		auto list = List(values);

		assert(list.Size() == 10);
		assert(list.Empty() == false);

		list.Clear();
		list.Print();

		assert(list.Size() == 0);
		assert(list.Empty() == true);
	}

	for (size_t kk = 0; kk < 10; kk++)
	{
		std::cout << "-->> example ---------------------------------->> 13 -->> " << kk << std::endl;

		std::vector<double> values({ 1, 2, 3, 4, 5 });

		auto list = List(values);

		list.Print();

		list.Reverse();

		assert(list.Size() == 5);

		list.Print();
	}
}
