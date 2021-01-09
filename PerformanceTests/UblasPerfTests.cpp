#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/test/unit_test.hpp>
#include "../Utilities/Clock.h"

namespace SEPOLIA4::PERFORMANCE_TESTS
{
	using namespace boost::numeric;
	using namespace SEPOLIA4::UTILITIES;

	BOOST_AUTO_TEST_SUITE(UBLAS_MATRIX_PERF)

		BOOST_AUTO_TEST_CASE(TEST1)
		{
			const int NROWS = 222;
			const int NCOLS = 333;

			Clock clock;

			ublas::matrix<double> m1(NROWS, NCOLS);
			ublas::matrix<double> m2(NCOLS, NCOLS);
			ublas::matrix<double> m3(NROWS, NCOLS);

			for (int i = 0; i < NROWS; ++i)
			{
				for (int j = 0; j < NCOLS; ++j)
				{
					m1(i, j) = 1.0;
				}
			}

			for (int i = 0; i < NCOLS; ++i)
			{
				for (int j = 0; j < NCOLS; ++j)
				{
					m2(i, j) = 2.0;
				}
			}

			clock.Start();
			m3 = ublas::prod(m1, m2);
			clock.PrintTimeSinceLastCall();

			for (int i = 0; i < NROWS; ++i)
			{
				for (int j = 0; j < NCOLS; ++j)
				{
					if(m3(i, j) != static_cast<double>(2 * NCOLS)) BOOST_CHECK(false);
				}
			}
		}

	BOOST_AUTO_TEST_SUITE_END()
}
