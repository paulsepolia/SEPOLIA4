#include "VectorTests.h"
#include "Vector.h"
#include <cassert>

namespace TESTS_SEPOLIA4_VECTOR
{
	constexpr size_t DIM = 10;

	void TEST1()
	{
		Vector v1;

		assert(v1.Size() == 0);
		assert(&v1(0) == nullptr);

		v1.Allocate(DIM);

		assert(v1.Size() == DIM);
		assert(&v1(0) != nullptr);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
		}

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v1(i) == static_cast<double>(i));
		}

		v1.Deallocate();
		assert(v1.Size() == 0);
		assert(&v1(0) == nullptr);
	}

	void TEST2()
	{
		Vector v1;
		Vector v2;

		assert(v1.Size() == 0);
		assert(v2.Size() == 0);
		assert(&v1(0) == nullptr);
		assert(&v2(0) == nullptr);

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		assert(v1.Size() == DIM);
		assert(v2.Size() == DIM);
		assert(&v1(0) != nullptr);
		assert(&v2(0) != nullptr);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
			v2(i) = v1(i);
		}

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v1(i) == static_cast<double>(i));
			assert(v1(i) == v2(i));
		}

		assert(v1 == v2);

		v1(0) = 2;
		v2(0) = 3;

		assert(v1 != v2);

		v1.Deallocate();
		v2.Deallocate();
		assert(v1.Size() == 0);
		assert(v2.Size() == 0);
		assert(&v1(0) == nullptr);
		assert(&v2(0) == nullptr);
	}

	void TEST3()
	{
		Vector v1;
		Vector v2;
		Vector v3;

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
			v2(i) = static_cast<double>(i + 1);
		}

		v3 = v1 + v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3(i) == static_cast<double>(i) + static_cast<double>(i + 1));
		}
	}

	void TEST4()
	{
		Vector v1;
		Vector v2;
		Vector v3;

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
			v2(i) = static_cast<double>(i + 1);
		}

		v3 = v1 - v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3(i) == static_cast<double>(i) - static_cast<double>(i + 1));
		}
	}

	void TEST5()
	{
		Vector v1;
		Vector v2;
		Vector v3;

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
			v2(i) = static_cast<double>(i + 1);
		}

		v3 = v1 * v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3(i) == static_cast<double>(i) * static_cast<double>(i + 1));
		}
	}

	void TEST6()
	{
		Vector v1;
		Vector v2;
		Vector v3;

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1(i) = static_cast<double>(i);
			v2(i) = static_cast<double>(i + 1);
		}

		v3 = v1 / v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3(i) == static_cast<double>(i) / static_cast<double>(i + 1));
		}
	}

	void TEST7()
	{
		assert(true);
	}

	void TEST8()
	{
		assert(true);
	}

	void TEST9()
	{
		assert(true);
	}

	void TEST10()
	{
		assert(true);
	}
}

