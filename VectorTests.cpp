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
		assert(&v1.At(0) == nullptr);

		v1.Allocate(DIM);

		assert(v1.Size() == DIM);
		assert(&v1.At(0) != nullptr);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
		}

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v1.At(i) == static_cast<double>(i));
		}

		v1.Deallocate();
		assert(v1.Size() == 0);
		assert(&v1.At(0) == nullptr);
	}

	void TEST2()
	{
		Vector v1;
		Vector v2;

		assert(v1.Size() == 0);
		assert(v2.Size() == 0);
		assert(&v1.At(0) == nullptr);
		assert(&v2.At(0) == nullptr);

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		assert(v1.Size() == DIM);
		assert(v2.Size() == DIM);
		assert(&v1.At(0) != nullptr);
		assert(&v2.At(0) != nullptr);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
			v2[i] = v1.At(i);
		}

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v1.At(i) == static_cast<double>(i));
			assert(v1.At(i) == v2.At(i));
		}

		assert(v1 == v2);

		v1[0] = 2;
		v2[0] = 3;

		assert(v1 != v2);

		v1.Deallocate();
		v2.Deallocate();
		assert(v1.Size() == 0);
		assert(v2.Size() == 0);
		assert(&v1.At(0) == nullptr);
		assert(&v2.At(0) == nullptr);
	}

	void TEST3()
	{
		Vector v1;
		Vector v2;
		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
			v2[i] = static_cast<double>(i + 1);
		}

		const auto v3 = v1 + v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3.At(i) == static_cast<double>(i) + static_cast<double>(i + 1));
		}
	}

	void TEST4()
	{
		Vector v1;
		Vector v2;
		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
			v2[i] = static_cast<double>(i + 1);
		}

		const auto v3 = v1 - v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3.At(i) == static_cast<double>(i) - static_cast<double>(i + 1));
		}
	}

	void TEST5()
	{
		Vector v1;
		Vector v2;

		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
			v2[i] = static_cast<double>(i + 1);
		}

		const auto v3 = v1 * v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3.At(i) == static_cast<double>(i) * static_cast<double>(i + 1));
		}
	}

	void TEST6()
	{
		Vector v1;
		Vector v2;
		v1.Allocate(DIM);
		v2.Allocate(DIM);

		for (size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
			v2[i] = static_cast<double>(i + 1);
		}

		const auto v3 = v1 / v2;

		for (size_t i = 0; i < DIM; i++)
		{
			assert(v3.At(i) == static_cast<double>(i) / static_cast<double>(i + 1));
		}
	}

	void TEST7()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 11;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = v + val;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == v.At(i) + val);
		}
	}

	void TEST8()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 12;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = v - val;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == v.At(i) - val);
		}
	}

	void TEST9()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 12;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = v * val;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == v.At(i) * val);
		}
	}

	void TEST10()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 12;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = v / val;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == v.At(i) / val);
		}
	}

	void TEST11()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 11;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = val + v;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == val + v.At(i));
		}
	}

	void TEST12()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 12;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = val - v;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == val - v.At(i));
		}
	}

	void TEST13()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 13;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i);
		}

		const auto res = val * v;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == val * v.At(i));
		}
	}

	void TEST14()
	{
		Vector v;
		v.Allocate(DIM);
		const double val = 14;

		for (size_t i = 0; i < DIM; i++)
		{
			v[i] = static_cast<double>(i+1);
		}

		const auto res = val / v;
		for (size_t i = 0; i < DIM; i++)
		{
			assert(res.At(i) == val / v.At(i));
		}
	}

	void TEST15()
	{
		Vector v1;
		v1.Allocate(DIM);
		const double val = 10;
		v1 = val;

		for(size_t i = 0; i < v1.Size(); i++)
		{
			assert(v1.At(i) == val);
		}
	}

	void TEST16()
	{
		Vector v1;
		v1.Allocate(DIM);
		const double val = 10;
		v1 = val;

		Vector v2(std::move(v1));

		assert(v2.Size() == DIM);

		for(size_t i = 0; i < v2.Size(); i++)
		{
			assert(v2.At(i) == val);
		}
	}

	void TEST17()
	{
		Vector v1;
		v1.Allocate(DIM);
		const double val = 10;
		v1 = val;

		Vector v2;
		v2 = std::move(v1);

		assert(v2.Size() == DIM);

		for(size_t i = 0; i < v2.Size(); i++)
		{
			assert(v2.At(i) == val);
		}
	}
}
