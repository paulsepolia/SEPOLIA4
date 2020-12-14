#include "List.h"
#include <iostream>
#include <cassert>

constexpr size_t DIM = 10000;
constexpr size_t DO_MAX = 10;

namespace TESTS_SEPOLIA4_LIST
{
	void TEST1()
	{
		auto list = List();

		for (size_t i = 0; i < DIM; i++)
		{
			list.Insert(static_cast<double>(i));
		}

		assert(list.Size() == DIM);
		assert(list.Empty() == false);
	}

	void TEST2()
	{
		auto list = List({ 1, 2, 3, 4, 5, 6 });

		for (size_t i = 0; i < DIM; i++)
		{
			list.Insert(static_cast<double>(i));
		}

		list.Append({ 5, 6, 7, 8, 9, 10 });

		assert(list.Size() == 6 + DIM + 6);
		assert(list.Empty() == false);
	}

	void TEST3()
	{
		auto list = List({ 1, 2 });

		list.Append({ 3, 4 });
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	void TEST4()
	{
		std::vector<double> values{ 1, 2 };

		auto list = List(values);

		list.Append({ 3, 4 });
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	void TEST5()
	{
		std::vector<double> values{ 1, 2 };

		auto list = List(values);

		std::vector<double> values2{ 3, 4 };

		list.Append(values2);
		list.Insert(5);
		list.Insert(6);

		assert(list.Size() == 6);
		assert(list.Empty() == false);
	}

	void TEST6()
	{
		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		const auto list1 = List(values);
		const auto list2 = List(list1);

		assert(list1.Size() == 6);
		assert(list2.Size() == 6);
		assert(list1.Empty() == false);
		assert(list2.Empty() == false);
	}

	void TEST7()
	{
		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		const auto list1 = List(values);
		const auto& list2 = list1;

		assert(list1.Size() == 6);
		assert(list2.Size() == 6);
		assert(list1.Empty() == false);
		assert(list2.Empty() == false);
	}

	void TEST8()
	{
		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		auto list1 = List(values);
		const auto list2 = List(std::move(list1));

		assert(list2.Size() == 6);
		assert(list2.Empty() == false);
	}

	void TEST9()
	{
		std::vector<double> values{ 1, 2, 3, 4, 5, 6, 7 };

		auto list1 = List(values);
		const auto list2 = std::move(list1);

		assert(list2.Size() == 7);
		assert(list2.Empty() == false);
	}

	void TEST10()
	{
		std::vector<double> values{ 1, 2, 3, 4, 5, 6 };

		auto list = List(values);

		assert(list.Size() == 6);
		assert(list.Empty() == false);

		int v = 1;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 5);
		assert(list.Empty() == false);

		v = 3;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 4);
		assert(list.Empty() == false);

		v = 6;
		list.EraseOne(v);
		list.Print();
		assert(list.Size() == 3);
		assert(list.Empty() == false);
	}

	void TEST11()
	{
		for (size_t kk = 0; kk < DO_MAX; kk++)
		{
			std::vector<double> values{ 1, 2, 5, 1, 2, 4, 5 };

			auto list = List(values);
			assert(list.Size() == 7);
			assert(list.Empty() == false);

			int v = 1;
			list.EraseAll(v);
			list.Print();
			assert(list.Size() == 5);
			assert(list.Empty() == false);

			v = 2;
			list.EraseAll(v);
			list.Print();
			assert(list.Size() == 3);
			assert(list.Empty() == false);

			v = 5;
			list.EraseAll(v);
			list.Print();
			assert(list.Size() == 1);
			assert(list.Empty() == false);

			v = 6;
			list.EraseAll(v);
			list.Print();
			assert(list.Size() == 1);
			assert(list.Empty() == false);

			v = 4;
			list.EraseAll(v);
			list.Print();
			assert(list.Size() == 0);
			assert(list.Empty() == true);
		}
	}

	void TEST12()
	{
		for (size_t kk = 0; kk < DO_MAX; kk++)
		{
			std::vector<double> values(10, kk);

			auto list = List(values);

			assert(list.Size() == 10);
			assert(list.Empty() == false);

			list.Clear();
			list.Print();

			assert(list.Size() == 0);
			assert(list.Empty() == true);
		}
	}

	void TEST13()
	{
		{
			for (size_t kk = 0; kk < DO_MAX; kk++)
			{
				std::vector<double> values({ 1, 2, 3, 4, 5 });

				auto list = List(values);

				list.Print();
				list.Reverse();

				assert(list.Size() == 5);

				list.Print();
			}
		}
	}

	void TEST14()
	{
		for (size_t kk = 0; kk < DO_MAX; kk++)
		{
			auto list = List();

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(i));
			}

			assert(list.Size() == DIM);
			assert(list.Empty() == false);
			assert(list.FindOne(double(0)) == 0);
			assert(list.FindOne(double(1)) == 1);
			assert(list.FindOne(double(2)) == 2);
			assert(list.FindOne(double(3)) == 3);
		}
	}

	void TEST15()
	{
		for (size_t kk = 0; kk < DO_MAX; kk++)
		{
			auto list = List();

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(i));
			}

			assert(list.Size() == DIM);
			assert(list.Empty() == false);
			assert(list.FindAll(double(0)) == std::vector<int64_t>{ 0 });
			assert(list.FindAll(double(1)) == std::vector<int64_t>{ 1 });
			assert(list.FindAll(double(2)) == std::vector<int64_t>{ 2 });
			assert(list.FindAll(double(DIM - 1)) == std::vector<int64_t>{ DIM - 1 });
			assert(list.FindAll(double(DIM)).empty());
		}
	}

	void TEST16()
	{
		for (size_t kk = 0; kk < DO_MAX; kk++)
		{
			auto list = List();

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(0));
			}

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(1));
			}

			assert(list.Size() == 2 * DIM);
			assert(list.Empty() == false);

			std::vector<int64_t> res0;
			for (size_t i = 0; i < DIM; i++)
			{
				res0.push_back(i);
			}
			assert(list.FindAll(double(0)) == res0);

			std::vector<int64_t> res1;
			for (size_t i = 0; i < DIM; i++)
			{
				res1.push_back(DIM + i);
			}
			assert(list.FindAll(double(1)) == res1);
			assert(list.FindAll(double(2)).empty());
			assert(list.FindAll(double(DIM - 1)).empty());
			assert(list.FindAll(double(DIM)).empty());

			list.Reverse();
			assert(list.FindAll(double(0)) == res1);
			assert(list.FindAll(double(1)) == res0);

			list.Clear();
			assert(list.FindAll(double(0)).empty());
			assert(list.FindAll(double(1)).empty());

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(0));
			}

			for (size_t i = 0; i < DIM; i++)
			{
				list.Insert(static_cast<double>(1));
			}

			assert(list.Size() == 2 * DIM);
			assert(list.Empty() == false);
			assert(list.FindAll(double(0)) == res0);
			assert(list.FindAll(double(1)) == res1);
		}
	}
}
