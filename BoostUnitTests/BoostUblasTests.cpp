#define BOOST_TEST_DYN_LINK

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/test/unit_test.hpp>

namespace SEPOLIA4::BOOST_UNIT_TEST_UBLAS
{
	using namespace boost::numeric;

	BOOST_AUTO_TEST_SUITE(UBLAS_MATRIX)

		BOOST_AUTO_TEST_CASE(TEST1)
		{
			ublas::matrix<double> m1(3, 3);
			ublas::matrix<double> m2(3, 3);
			ublas::matrix<double> m3(3, 3);

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
					BOOST_TEST(m1(i, j) + m2(i, j) == m3(i, j));
				}
			}
		}

	BOOST_AUTO_TEST_SUITE_END()
}
