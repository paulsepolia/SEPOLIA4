#define BOOST_TEST_DYN_LINK

#include "../Containers/Vector/Vector.h"
#include <boost/test/unit_test.hpp>
#include <cblas.h>

using namespace SEPOLIA4::CONTAINERS;

namespace SEPOLIA4::BOOST_UNIT_TEST_BLAS
{
	BOOST_AUTO_TEST_SUITE(BLAS_TESTS)

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_1)
		{
			const int32_t NROWS = 4;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			double A[TOT_ELEMS];
			double x[NCOLS];

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			double y[NROWS];
			const double alpha = 1.234;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NCOLS, x, 1, beta, y, 1);

			const std::vector<double> resExpected{ alpha * 55, alpha * 130, alpha * 205, alpha * 280 };

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected[i] == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_AX_2)
		{
			const int32_t NROWS = 1;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			double A[TOT_ELEMS];
			double x[NCOLS];

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			double y[NROWS];
			const double alpha = 1.234;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NCOLS, x, 1, beta, y, 1);

			const std::vector<double> resExpected{ alpha * 55 };

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected[i] == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_AX_3)
		{
			const int32_t NROWS = 5;
			const int32_t NCOLS = 1;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			double A[TOT_ELEMS];
			double x[NCOLS];

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			double y[NROWS];
			const double alpha = 1.2345;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NCOLS, x, 1, beta, y, 1);

			const std::vector<double> resExpected{ 1 * alpha, 2 * alpha, 3 * alpha, 4 * alpha, 5 * alpha };

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected[i] == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_plus_bY)
		{
			const int32_t NROWS = 4;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			double A[TOT_ELEMS];
			double x[NCOLS];
			double y[NROWS];

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NROWS; i++)
			{
				y[i] = static_cast<double>(i);
			}

			const double alpha = 1.234;
			const double beta = 2.345;
			const std::vector<double> resExpected{ alpha * 55 + beta * y[0], alpha * 130 + beta * y[1],
												   alpha * 205 + beta * y[2], alpha * 280 + beta * y[3] };

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, A, NCOLS, x, 1, beta, y, 1);

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected[i] == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_1_USING_VECTOR)
		{
			const int32_t NROWS = 4;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			Vector<double> A(TOT_ELEMS);
			Vector<double> x(NCOLS);

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			Vector<double> y(NROWS);
			const double alpha = 1.234;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, &A[0], NCOLS, &x[0], 1, beta, &y[0], 1);

			const Vector resExpected({ alpha * 55, alpha * 130, alpha * 205, alpha * 280 });

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected.At(i) == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_2_USING_VECTOR)
		{
			const int32_t NROWS = 1;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			Vector<double> A(TOT_ELEMS);
			Vector<double> x(NCOLS);

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			Vector<double> y(NROWS);
			const double alpha = 1.234;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, &A[0], NCOLS, &x[0], 1, beta, &y[0], 1);

			const Vector<double> resExpected({ alpha * 55 });

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected.At(i) == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_3_USING_VECTOR)
		{
			const int32_t NROWS = 5;
			const int32_t NCOLS = 1;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			Vector<double> A(TOT_ELEMS);
			Vector<double> x(NCOLS);

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			Vector<double> y(NROWS);
			const double alpha = 1.2345;
			const double beta = 0.0;

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, &A[0], NCOLS, &x[0], 1, beta, &y[0], 1);

			const Vector resExpected({ 1 * alpha, 2 * alpha, 3 * alpha, 4 * alpha, 5 * alpha });

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected.At(i) == y[i]);
			}
		}

		BOOST_AUTO_TEST_CASE(TEST_CBLAS_DGEMV_aAX_plus_bY_USING_VECTOR)
		{
			const int32_t NROWS = 4;
			const int32_t NCOLS = 5;
			const size_t TOT_ELEMS = NROWS * NCOLS;

			Vector<double> A(TOT_ELEMS);
			Vector<double> x(NCOLS);
			Vector<double> y(NROWS);

			for (size_t i = 0; i < TOT_ELEMS; i++)
			{
				A[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NCOLS; i++)
			{
				x[i] = static_cast<double>(i + 1);
			}

			for (size_t i = 0; i < NROWS; i++)
			{
				y[i] = static_cast<double>(i);
			}

			const double alpha = 1.234;
			const double beta = 2.345;
			const Vector<double> resExpected({ alpha * 55 + beta * y[0], alpha * 130 + beta * y[1],
									   alpha * 205 + beta * y[2], alpha * 280 + beta * y[3] });

			//========//
			// y = Ax //
			//========//
			cblas_dgemv(CblasRowMajor, CblasNoTrans, NROWS, NCOLS, alpha, &A[0], NCOLS, &x[0], 1, beta, &y[0], 1);

			for (int i = 0; i < NROWS; i++)
			{
				BOOST_TEST(resExpected.At(i) == y[i]);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()
}
