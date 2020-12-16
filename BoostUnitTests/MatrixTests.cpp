#define BOOST_TEST_DYN_LINK

#include "../Containers/Matrix/Matrix.h"
#include <boost/test/unit_test.hpp>
#include <cmath>

using namespace SEPOLIA4::CONTAINERS;

namespace std
{
	template<typename T>
	ostream& operator<<(ostream& stream, const Matrix<T>& mat)
	{
		return stream;
	}
}

namespace SEPOLIA4::BOOST_UNIT_TEST_MATRIX
{
	constexpr int32_t NROWS = 5;
	constexpr int32_t NCOLS = 6;

	BOOST_AUTO_TEST_SUITE(CONTAINER_MATRIX)

		BOOST_AUTO_TEST_CASE(TEST1)
		{
			Matrix<double> m1;
			BOOST_TEST(m1.NRows() == 0);
			BOOST_TEST(m1.NCols() == 0);
			BOOST_TEST(m1.IsDeallocated());

			m1.Allocate(NROWS, NCOLS);
			BOOST_TEST(m1.TotalElements() == static_cast<size_t>(NROWS) * NCOLS);
			BOOST_TEST(m1.NRows() == NROWS);
			BOOST_TEST(m1.NCols() == NCOLS);
			BOOST_TEST(m1.IsAllocated());

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
				}
			}

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m1.At(i, j) == static_cast<double>(i + j));
				}
			}

			m1.Deallocate();
			BOOST_TEST(m1.NRows() == 0);
			BOOST_TEST(m1.NCols() == 0);
			BOOST_TEST(m1.IsDeallocated());
		}

		BOOST_AUTO_TEST_CASE(TEST2)
		{
			Matrix<double> m1;
			Matrix<double> m2;

			BOOST_TEST(m1.TotalElements() == 0);
			BOOST_TEST(m2.TotalElements() == 0);
			BOOST_TEST(m1.IsDeallocated());
			BOOST_TEST(m2.IsDeallocated());

			m1.Allocate(NROWS, NCOLS);
			m2.Allocate(NROWS, NCOLS);

			BOOST_TEST(m1.TotalElements() == static_cast<size_t>(NROWS) * NCOLS);
			BOOST_TEST(m2.TotalElements() == static_cast<size_t>(NROWS) * NCOLS);
			BOOST_TEST(m1.NRows() == NROWS);
			BOOST_TEST(m1.NCols() == NCOLS);
			BOOST_TEST(m1.IsAllocated());
			BOOST_TEST(m2.IsAllocated());

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
					m2(i, j) = m1.At(i, j);
				}
			}

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m1(i, j) == static_cast<double>(i + j));
					BOOST_TEST(m1(i, j) == m2(i, j));
				}
			}

			BOOST_CHECK(m1 == m2);

			m1(0, 0) = 2;
			m2(0, 0) = 3;
			BOOST_CHECK(m1 != m2);

			m1.Deallocate();
			m2.Deallocate();
			BOOST_TEST(m1.NRows() == 0);
			BOOST_TEST(m1.NCols() == 0);
			BOOST_TEST(m2.NRows() == 0);
			BOOST_TEST(m2.NCols() == 0);
			BOOST_TEST(m1.IsDeallocated());
			BOOST_TEST(m2.IsDeallocated());
		}

		BOOST_AUTO_TEST_CASE(TEST3)
		{
			Matrix<double> m1;
			Matrix<double> m2;
			m1.Allocate(NROWS, NCOLS);
			m2.Allocate(NROWS, NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
					m2(i, j) = static_cast<double>(i + j + 1);
				}
			}

			const auto m3 = m1 + m2;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m3.At(i, j) == static_cast<double>(i + j) + static_cast<double>(i + j + 1));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST4)
		{
			Matrix<double> m1;
			Matrix<double> m2;
			m1.Allocate(NROWS, NCOLS);
			m2.Allocate(NROWS, NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
					m2(i, j) = static_cast<double>(i + j + 1);
				}
			}

			const auto m3 = m1 - m2;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m3.At(i, j) == static_cast<double>(i + j) - static_cast<double>(i + j + 1));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST5)
		{
			Matrix<double> m1;
			Matrix<double> m2;

			m1.Allocate(NROWS, NCOLS);
			m2.Allocate(NROWS, NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
					m2(i, j) = static_cast<double>(i + j + 1);
				}
			}

			const auto m3 = m1 * m2;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m3.At(i, j) == static_cast<double>(i + j) * static_cast<double>(i + j + 1));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST6)
		{
			Matrix<double> m1;
			Matrix<double> m2;

			m1.Allocate(NROWS, NCOLS);
			m2.Allocate(NROWS, NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = static_cast<double>(i + j);
					m2(i, j) = static_cast<double>(i + j + 1);
				}
			}

			const auto m3 = m1 / m2;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m3.At(i, j) == static_cast<double>(i + j) / static_cast<double>(i + j + 1));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST7)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 11;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = m + val;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == static_cast<double>(i + j) + val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST8)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 11;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = m - val;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == static_cast<double>(i + j) - val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST9)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 11;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = m * val;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == static_cast<double>(i + j) * val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST10)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 15;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = m / val;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == static_cast<double>(i + j) / val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST11)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 15;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = val + m;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == val + static_cast<double>(i + j));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST12)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 15;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = val - m;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == val - static_cast<double>(i + j));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST13)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 15;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j);
				}
			}

			const auto res = val * m;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == val * static_cast<double>(i + j));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST14)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 15;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m(i, j) = static_cast<double>(i + j + 1);
				}
			}

			const auto res = val / m;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(res.At(i, j) == val / static_cast<double>(i + j + 1));
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST15)
		{
			Matrix<double> m;
			m.Allocate(NROWS, NCOLS);
			const double val = 10;
			m = val;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m.At(i, j) == val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST16)
		{
			Matrix<double> m1;
			m1.Allocate(NROWS, NCOLS);
			const double val = 10;
			m1 = val;

			Matrix<double> m2(std::move(m1));

			BOOST_TEST(m2.TotalElements() == static_cast<size_t>(NROWS) * NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m2.At(i, j) == val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST17)
		{
			Matrix<double> m1;
			m1.Allocate(NROWS, NCOLS);
			const double val = 10;
			m1 = val;

			Matrix<double> m2;
			m2 = std::move(m1);

			BOOST_TEST(m2.NRows() == NROWS);
			BOOST_TEST(m2.NCols() == NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					BOOST_TEST(m2.At(i, j) == val);
				}
			}
		}

		BOOST_AUTO_TEST_CASE(TEST18)
		{
			Matrix<double> m1;
			m1.Allocate(NROWS, NCOLS);
			m1 = 10.0;
			auto m2 = -m1;
			BOOST_TEST(m1 == 10.0);
			BOOST_TEST(10.0 == m1);
			BOOST_TEST(m2 == -m1);
			BOOST_TEST(-m1 == m2);
			BOOST_TEST(m1 != 11.0);
			BOOST_TEST(m2 != m1);
			BOOST_TEST(11.0 != m1);
		}

		BOOST_AUTO_TEST_CASE(TEST19)
		{
			Matrix<double> m1;
			m1.Allocate(NROWS, NCOLS);
			const double val = 10;
			m1 = val;
			Matrix<double> m2(m1);

			BOOST_TEST(m1 == val);
			BOOST_TEST(val == m1);
			BOOST_TEST(m2 == m1);
			BOOST_TEST(m2 == val);
		}

		BOOST_AUTO_TEST_CASE(TEST20)
		{
			Matrix<double> m1;
			m1.Allocate(NROWS, NCOLS);
			Matrix<double> m2;
			m2.Allocate(NROWS, NCOLS);
			Matrix<double> m3;
			m3.Allocate(NROWS, NCOLS);

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					m1(i, j) = std::sin(i + j);
					m2(i, j) = std::sin(i + j);
					m3(i, j) = std::sin(i + j);
				}
			}

			BOOST_TEST(m1 == m2);
			BOOST_TEST(m2 == m3);
			BOOST_TEST(m1 == m3);
		}

		BOOST_AUTO_TEST_CASE(TEST21)
		{
			const Matrix<double> mat{{ 1, 2, 3, 4 },
									 { 2, 3, 4, 5 }};

			BOOST_TEST(mat.NRows() == 2);
			BOOST_TEST(mat.NCols() == 4);

			BOOST_TEST(mat.At(0, 0) == 1);
			BOOST_TEST(mat.At(0, 1) == 2);
			BOOST_TEST(mat.At(0, 2) == 3);
			BOOST_TEST(mat.At(0, 3) == 4);

			BOOST_TEST(mat.At(1, 0) == 2);
			BOOST_TEST(mat.At(1, 1) == 3);
			BOOST_TEST(mat.At(1, 2) == 4);
			BOOST_TEST(mat.At(1, 3) == 5);
		}

		BOOST_AUTO_TEST_CASE(TEST22)
		{
			const std::vector<std::vector<double>> matSTL{{ 1, 2, 3, 4 },
														  { 2, 3, 4, 5 },
														  { 3, 4, 5, 6 }};
			const Matrix<double> mat(matSTL);
			BOOST_TEST(mat.NRows() == 3);
			BOOST_TEST(mat.NCols() == 4);

			BOOST_TEST(mat.At(0, 0) == 1);
			BOOST_TEST(mat.At(0, 1) == 2);
			BOOST_TEST(mat.At(0, 2) == 3);
			BOOST_TEST(mat.At(0, 3) == 4);

			BOOST_TEST(mat.At(1, 0) == 2);
			BOOST_TEST(mat.At(1, 1) == 3);
			BOOST_TEST(mat.At(1, 2) == 4);
			BOOST_TEST(mat.At(1, 3) == 5);

			BOOST_TEST(mat.At(2, 0) == 3);
			BOOST_TEST(mat.At(2, 1) == 4);
			BOOST_TEST(mat.At(2, 2) == 5);
			BOOST_TEST(mat.At(2, 3) == 6);
		}

		BOOST_AUTO_TEST_CASE(TEST23)
		{
			Matrix<double> mat(NROWS, NCOLS);
			BOOST_TEST(mat.NRows() == NROWS);
			BOOST_TEST(mat.NCols() == NCOLS);
			const double val = 12.34;

			for (int32_t i = 0; i < NROWS; i++)
			{
				for (int32_t j = 0; j < NCOLS; j++)
				{
					mat(i, j) = val;
				}
			}

			BOOST_TEST(mat == val);
			BOOST_TEST(val == mat);
		}

		BOOST_AUTO_TEST_CASE(TEST24)
		{
			Matrix<double> m1(NROWS, NCOLS);
			Matrix<double> m2(NROWS, NCOLS);
			Matrix<double> m3(NROWS, NCOLS);
			Matrix<double> m4(NROWS, NCOLS);
			const double val1 = 1;
			m1 = val1;
			const double val2 = 2;
			m2 = val2;
			const double val3 = 3;
			m3 = val3;
			const double val4 = 4;
			m4 = val4;

			m4 = m1 + m2 + m3 + m4;
			BOOST_TEST(m4 == val1 + val2 + val3 + val4);

			m4 = val1;
			BOOST_TEST(val1 == m4);

			m4 = val1 + val2 + val3 - val1 - val2 - val3;
			BOOST_TEST(m4 == 0);

			m4 = val1;
			BOOST_TEST(val1 == m4);

			m4 = -m1 + val1 + m2 - val2;
			BOOST_TEST(m4 == 0);
		}

		BOOST_AUTO_TEST_CASE(TEST25)
		{
			Matrix<double> m1(NROWS, NCOLS);
			Matrix<double> m2(NROWS, NCOLS);
			Matrix<double> m3(NROWS, NCOLS);
			const double val1 = 1;
			m1 = val1;
			const double val2 = 2;
			m2 = val2;

			m3 = (m1 / m2) * (m2 / m1);
			BOOST_TEST(m3 == 1.0);
		}

		BOOST_AUTO_TEST_CASE(TEST26)
		{
			Matrix<double> mat(NROWS, NCOLS);
			double val = 1;
			mat = val;
			++mat;
			++val;
			BOOST_TEST(mat == val);
		}

		BOOST_AUTO_TEST_CASE(TEST27)
		{
			Matrix<double> mat(NROWS, NCOLS);
			double val = 1;
			mat = val;
			--mat;
			--val;
			BOOST_TEST(mat == val);
		}

		BOOST_AUTO_TEST_CASE(TEST28)
		{
			Matrix<double> mat(NROWS, NCOLS);
			double val = 1;
			mat += val;
			BOOST_TEST(mat == val);
			mat += val;
			BOOST_TEST(mat == 2 * val);
			mat += mat;
			BOOST_TEST(mat == 4 * val);
		}

		BOOST_AUTO_TEST_CASE(TEST29)
		{
			Matrix<double> mat(NROWS, NCOLS);
			double val = 1;
			mat -= val;
			BOOST_TEST(mat == -1 * val);
			mat -= val;
			BOOST_TEST(mat == -2 * val);
			mat -= mat;
			BOOST_TEST(mat == 0);
		}

		BOOST_AUTO_TEST_CASE(TEST30)
		{
			Matrix<double> mat(NROWS, NCOLS);
			double val1 = 3;
			double val2 = 4;
			mat = val1;
			mat *= val2;
			BOOST_TEST(mat == val1 * val2);
			mat *= mat;
			BOOST_TEST(mat == val1 * val2 * val1 * val2);
		}

		BOOST_AUTO_TEST_CASE(TEST31)
		{
			Matrix<double> mat(NROWS, NCOLS);
			const double val1 = 3;
			const double val2 = 4;
			mat = val1;
			mat /= val2;
			BOOST_TEST(mat == val1 / val2);
			mat /= mat;
			BOOST_TEST(1.0 == mat);
		}

	BOOST_AUTO_TEST_SUITE_END()
}

