#include "BoostUblasTests.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cassert>

namespace TESTS_BOOST_UBLAS
{
	using namespace boost::numeric::ublas;

	void TEST1()
	{
		matrix<double> m1(3, 3);
		matrix<double> m2(3, 3);
		matrix<double> m3(3, 3);

		for (unsigned i = 0; i < m1.size1(); ++i)
		{
			for (unsigned j = 0; j < m1.size2(); ++j)
			{
				m1(i, j) = 1;
				m2(i, j) = 2;
				m3(i, j) = 3;
			}
		}

		for (size_t i = 0; i < m1.size1(); i++)
		{
			for (size_t j = 0; j < m1.size2(); j++)
			{
				assert(m1(i, j) + m2(i, j) == m3(i, j));
			}
		}
	}
}
