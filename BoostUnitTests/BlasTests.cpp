#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <cblas.h>

namespace SEPOLIA4::BOOST_UNIT_TEST_BLAS
{
	BOOST_AUTO_TEST_SUITE(BLAS_TESTS)

		BOOST_AUTO_TEST_CASE(TEST1)
		{
			const int32_t NROWS = 4;
			const int32_t NCOLS = 5;

			double A[] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4 };
			double x[] = { 1, 1, 1, 1, 1 };
			double y[NROWS];
			const double alpha = 1.0;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NCOLS, x, 1, beta, y, 1);

			std::vector<double> resExpected1{ 5.0, 10.0, 15.0, 20.0 };
			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected1[i] == y[i]);
			}

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasColMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NROWS, x, 1, beta, y, 1);

			std::vector<double> resExpected2{ 11.0, 12.0, 13.0, 14.0 };
			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected2[i] == y[i]);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()
}
