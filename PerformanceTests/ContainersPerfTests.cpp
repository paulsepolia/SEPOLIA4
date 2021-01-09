#define BOOST_TEST_DYN_LINK

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/test/unit_test.hpp>
#include "../Containers/Matrix/Matrix.h"
#include "../Utilities/Clock.h"

namespace SEPOLIA4::PERFORMANCE_TESTS
{
	using namespace boost::numeric;
	using namespace SEPOLIA4::CONTAINERS;
	using namespace SEPOLIA4::UTILITIES;

	BOOST_AUTO_TEST_SUITE(CONTAINERS_PERF)

		BOOST_AUTO_TEST_CASE(TEST1_BuildMatrix)
		{
			constexpr uint32_t NROWS = 987;
			constexpr uint32_t NCOLS = 567;
			constexpr int DO_MAX = 1000;

			auto clock = Clock();
			clock.Start();
			// UBLAS matrix
			ublas::matrix<double> mUBLAS(NROWS, NCOLS);

			for (int kk = 0; kk < DO_MAX; kk++)
			{
				for (uint32_t i = 0; i < NROWS; i++)
				{
					for (uint32_t j = 0; j < NCOLS; j++)
					{
						mUBLAS(i, j) += static_cast<double>(i) + j + kk;
					}
				}
			}
			const auto tUBLAS = clock.GetSecondsPassedSinceLastCall();

			// SEPOLIA matrix
			Matrix<double> mSEP(NROWS, NCOLS);
			for (int kk = 0; kk < DO_MAX; kk++)
			{
				for (uint32_t i = 0; i < NROWS; ++i)
				{
					for (uint32_t j = 0; j < NCOLS; ++j)
					{
						mSEP(i, j) += static_cast<double>(i) + j + kk;
					}
				}
			}
			const auto tSEP = clock.GetSecondsPassedSinceLastCall();

			// test here
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mUBLAS(i, j) != mSEP(i, j)) BOOST_CHECK(false);
				}
			}

			// report here
			std::cout << "Time used UBLAS = " << tUBLAS << std::endl;
			std::cout << "Time used SEP = " << tSEP << std::endl;
			std::cerr << "tSEP/tUBLAS = " << tSEP / tUBLAS << std::endl;
		}

		BOOST_AUTO_TEST_CASE(TEST2_MatrixOperationsPlus)
		{
			Clock clock;
			clock.Start();

			constexpr uint32_t NROWS = 1001;
			constexpr uint32_t NCOLS = 999;
			constexpr int DO_MAX = 500;

			// UBLAS matrices
			ublas::matrix<double> mUBLAS1(NROWS, NCOLS);
			ublas::matrix<double> mUBLAS2(NROWS, NCOLS);
			ublas::matrix<double> mUBLAS3(NROWS, NCOLS);

			for (uint32_t i = 0; i < NROWS; ++i)
			{
				for (uint32_t j = 0; j < NCOLS; ++j)
				{
					mUBLAS1(i, j) = static_cast<double>(i) + j;
					mUBLAS2(i, j) = static_cast<double>(i) * j;
				}
			}

			clock.Reset();
			// measure the operator+
			for (int kk = 0; kk < DO_MAX; kk++)
			{
				mUBLAS3 += mUBLAS1 + mUBLAS2;
			}
			const auto tUBLAS = clock.GetSecondsPassedSinceLastCall();

			// SEPOLIA matrices
			Matrix<double> mSEP1(NROWS, NCOLS);
			Matrix<double> mSEP2(NROWS, NCOLS);
			Matrix<double> mSEP3(NROWS, NCOLS);

			for (int i = 0; i < NROWS; ++i)
			{
				for (int j = 0; j < NCOLS; ++j)
				{
					mSEP1(i, j) = static_cast<double>(i) + j;
					mSEP2(i, j) = static_cast<double>(i) * j;
				}
			}

			// measure the operator+
			clock.Reset();
			for (int kk = 0; kk < DO_MAX; kk++)
			{
				mSEP3 += mSEP1 + mSEP2;
			}
			const auto tSEP = clock.GetSecondsPassedSinceLastCall();

			// test here
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mSEP3(i, j) != (mSEP1(i, j) + mSEP2(i, j)) * DO_MAX) BOOST_CHECK(false);
				}
			}
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mUBLAS3(i, j) != (mUBLAS1(i, j) + mUBLAS2(i, j)) * DO_MAX) BOOST_CHECK(false);
				}
			}
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mUBLAS3(i, j) != mSEP3(i, j)) BOOST_CHECK(false);
				}
			}

			// report here
			std::cout << "Time used UBLAS = " << tUBLAS << std::endl;
			std::cout << "Time used SEP = " << tSEP << std::endl;
			std::cerr << "tSEP/tUBLAS = " << tSEP / tUBLAS << std::endl;
		}

		BOOST_AUTO_TEST_CASE(TEST3_MatrixOperationSubtract)
		{
			Clock clock;
			const uint32_t NROWS = 345;
			const uint32_t NCOLS = 987;
			const int DO_MAX = 500;

			// SEPOLIA matrices
			Matrix<double> mSEP1(NROWS, NCOLS);
			Matrix<double> mSEP2(NROWS, NCOLS);
			Matrix<double> mSEP3(NROWS, NCOLS);

			for (int i = 0; i < NROWS; ++i)
			{
				for (int j = 0; j < NCOLS; ++j)
				{
					mSEP1(i, j) = static_cast<double>(i) + j;
					mSEP2(i, j) = static_cast<double>(i) * j;
				}
			}

			// measure the operator+
			clock.Reset();
			for (int kk = 0; kk < DO_MAX; kk++)
			{
				mSEP3 -= mSEP1 - mSEP2;
			}
			auto tSEP = clock.GetSecondsPassedSinceLastCall();

			// UBLAS matrices
			ublas::matrix<double> mUBLAS1(NROWS, NCOLS);
			ublas::matrix<double> mUBLAS2(NROWS, NCOLS);
			ublas::matrix<double> mUBLAS3(NROWS, NCOLS);

			for (uint32_t i = 0; i < NROWS; ++i)
			{
				for (uint32_t j = 0; j < NCOLS; ++j)
				{
					mUBLAS1(i, j) = static_cast<double>(i) + j;
					mUBLAS2(i, j) = static_cast<double>(i) * j;
				}
			}

			// measure the operator+
			clock.Reset();
			for (int kk = 0; kk < DO_MAX; kk++)
			{
				mUBLAS3 -= mUBLAS1 - mUBLAS2;
			}
			auto tUBLAS = clock.GetSecondsPassedSinceLastCall();

			// test here
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mUBLAS3(i, j) != -(mUBLAS1(i, j) - mUBLAS2(i, j)) * DO_MAX) BOOST_CHECK(false);
				}
			}
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mSEP3(i, j) != -(mSEP1(i, j) - mSEP2(i, j)) * DO_MAX) BOOST_CHECK(false);
				}
			}
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					if (mSEP3(i, j) != mUBLAS3(i, j)) BOOST_CHECK(false);
				}
			}

			// report here
			std::cout << "Time used UBLAS = " << tUBLAS << std::endl;
			std::cout << "Time used SEP = " << tSEP << std::endl;
			std::cerr << "tSEP/tUBLAS = " << tSEP / tUBLAS << std::endl;
		}

	BOOST_AUTO_TEST_SUITE_END()
}

