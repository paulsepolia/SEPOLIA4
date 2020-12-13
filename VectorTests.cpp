#include <cassert>
#include "VectorTests.h"
#include "Vector.h"
#include <iostream>

namespace TESTS_SEPOLIA4_VECTOR
{
	constexpr size_t DIM = 10;

	void TEST1()
	{
		Vector v1;

		assert(v1.Size() == 0);
		assert(&v1[0] == nullptr);

		v1.Allocate(DIM);

		assert(v1.Size() == DIM);
		assert(&v1[0] != nullptr);

		for(size_t i = 0; i < DIM; i++)
		{
			v1[i] = static_cast<double>(i);
		}

		for(size_t i = 0; i < DIM; i++)
		{
			assert(v1[i] == static_cast<double>(i));
		}

		v1.Deallocate();
		assert(v1.Size() == 0);
		assert(&v1[0] == nullptr);
	}

	void TEST2()
	{
		assert(true);
	}

	void TEST3()
	{
		assert(true);
	}

	void TEST4()
	{
		assert(true);
	}
}

