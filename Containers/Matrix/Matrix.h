#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace SEPOLIA4::CONTAINERS
{
	template<typename T>
	class Matrix final
	{
	public:

		//==============//
		// Constructors //
		//==============//

		Matrix() = default;

		explicit Matrix(uint32_t nrows, uint32_t ncols)
		{
			Allocate(nrows, ncols);
		}

		explicit Matrix(const std::vector<std::vector<T>>& mat)
		{
			const auto NROWS = static_cast<uint32_t>(mat.size());
			const auto NCOLS = static_cast<uint32_t>(mat[0].size());
			Allocate(NROWS, NCOLS);
			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					operator[](static_cast<size_t>(i) * NCOLS + j) = mat[i][j];
				}
			}
		}

		Matrix(const std::initializer_list<std::initializer_list<T>>& initMatrix)
		{
			std::vector<std::vector<T>> mTmp;

			for(const auto& el1: initMatrix)
			{
				std::vector<T> vTmp;
				for(const auto& el2: el1)
				{
					vTmp.push_back(el2);
				}
				mTmp.push_back(vTmp);
			}

			Allocate(mTmp.size(), mTmp[0].size());
			size_t idx = 0;
			for (const auto& el1 : initMatrix)
			{
				for (const auto& el2 : el1)
				{
					operator[](idx) = el2;
					idx++;
				}
			}
		}

		Matrix(const Matrix& other)
		{
			if (this != &other)
			{
				Allocate(other.m_nrows, other.m_ncols);
				for (size_t i = 0; i < TotalElements(); i++)
				{
					m_data[i] = other.m_data[i];
				}
			}
		}

		Matrix& operator=(const Matrix& other)
		{
			if (this != &other)
			{
				Allocate(other.m_nrows, other.m_ncols);
				for (size_t i = 0; i < TotalElements(); i++)
				{
					m_data[i] = other.m_data[i];
				}
			}
			return *this;
		}

		Matrix(Matrix&& other) noexcept
		{
			if (this != &other)
			{
				if (m_data) Deallocate();
				m_data = std::move(other.m_data);
				m_nrows = other.m_nrows;
				m_ncols = other.m_ncols;
				other.m_data = nullptr;
				other.m_nrows = 0;
				other.m_ncols = 0;
			}
		}

		Matrix& operator=(Matrix&& other) noexcept
		{
			if (this != &other)
			{
				if (m_data) Deallocate();
				m_data = std::move(other.m_data);
				m_nrows = other.m_nrows;
				m_ncols = other.m_ncols;
				other.m_data = nullptr;
				other.m_nrows = 0;
				other.m_ncols = 0;
			}
			return *this;
		}

		~Matrix() = default;

		//===================//
		// Memory management //
		//===================//

		bool Allocate(uint32_t nrows, uint32_t ncols)
		{
			try
			{
				if (m_data) Deallocate();
				m_data = std::make_unique<T[]>(nrows*ncols);
				m_nrows = nrows;
				m_ncols = ncols;
				return true;
			}
			catch (std::exception& e)
			{
				m_data.reset(nullptr);
				std::cout << e.what() << std::endl;
			}
			return false;
		}

		bool Deallocate()
		{
			m_data.reset(nullptr);
			m_nrows = 0;
			m_ncols = 0;
			return true;
		}

		[[nodiscard]] bool IsAllocated() const
		{
			if (m_data) return true;
			return false;
		}

		[[nodiscard]] bool IsDeallocated() const
		{
			return !IsAllocated();
		}

		//======================================//
		// Operators to access and set elements //
		//======================================//

		[[nodiscard]] const T& At(uint32_t rowIdx, uint32_t colIdx) const
		{
			return m_data[rowIdx * static_cast<size_t>(m_ncols) + colIdx];
		}

		T& operator()(uint32_t rowIdx, uint32_t colIdx)
		{
			return m_data[rowIdx * static_cast<size_t>(m_ncols) + colIdx];
		}

	private:

		[[nodiscard]] const T& At(size_t idx) const
		{
			return m_data[idx];
		}

		T& operator[](size_t idx)
		{
			return m_data[idx];
		}

	public:

		//================//
		// Check equality //
		//================//

		bool operator==(const Matrix& rhs) const
		{
			if (m_ncols != rhs.m_ncols) return false;
			if (m_nrows != rhs.m_nrows) return false;

			for (size_t i = 0; i < TotalElements(); i++)
			{
				if (m_data[i] != rhs.m_data[i]) return false;
			}
			return true;
		}

		bool operator==(T val) const
		{
			for (size_t i = 0; i < TotalElements(); i++)
			{
				if (m_data[i] != val) return false;
			}
			return true;
		}

		template<typename U>
		friend bool operator==(U val, const Matrix<U>& rhs)
		{
			return rhs == val;
		}

		bool operator!=(const Matrix& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator!=(T val) const
		{
			return !(*this == val);
		}

		template<typename U>
		friend bool operator!=(U val, const Matrix<U>& rhs)
		{
			return rhs != val;
		}

		//======================//
		// arithmetic operators //
		//======================//

		//=============//
		// operator: + //
		//=============//

		Matrix operator+(const Matrix& rhs) const
		{
			Matrix<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] + rhs.m_data[i];
			}
			return std::move(res);
		}

		Matrix operator+(T val) const
		{
			Matrix<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] + val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Matrix<U> operator+(U val, const Matrix<U>& rhs)
		{
			Matrix<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);

			for (size_t i = 0; i < res.TotalElements(); i++)
			{
				res[i] = val + rhs.At(i);
			}
			return std::move(res);
		}

		void operator++()
		{
			for (size_t i = 0; i < TotalElements(); i++)
			{
				operator[](i)++;
			}
		}

		void operator++(int)
		{
			++(*this);
		}

		Matrix& operator+=(const Matrix& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		Matrix& operator+=(T val)
		{
			*this = *this + val;
			return *this;
		}

		//=============//
		// operator: - //
		//=============//

		Matrix operator-(const Matrix& rhs) const
		{
			Matrix res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] - rhs.m_data[i];
			}
			return std::move(res);
		}

		Matrix operator-(T val) const
		{
			Matrix res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] - val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Matrix<U> operator-(U val, const Matrix<U>& rhs)
		{
			Matrix<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val - rhs.At(i);
			}
			return std::move(res);
		}

		template<typename U>
		friend Matrix<U> operator-(const Matrix<U>& rhs)
		{
			Matrix<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = -rhs.At(i);
			}
			return std::move(res);
		}

		void operator--()
		{
			for (size_t i = 0; i < TotalElements(); i++)
			{
				operator[](i)--;
			}
		}

		void operator--(int)
		{
			--(*this);
		}

		Matrix& operator-=(const Matrix& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		Matrix& operator-=(T val)
		{
			*this = *this - val;
			return *this;
		}

		//=============//
		// operator: * //
		//=============//

		Matrix operator*(const Matrix& rhs) const
		{
			Matrix res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] * rhs.m_data[i];
			}
			return std::move(res);
		}

		Matrix operator*(T val) const
		{
			Matrix<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] * val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Matrix<U> operator*(U val, const Matrix<U>& rhs)
		{
			Matrix<U> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val * rhs.At(i);
			}
			return std::move(res);
		}

		Matrix& operator*=(const Matrix& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		Matrix& operator*=(T val)
		{
			*this = *this * val;
			return *this;
		}

		//=============//
		// operator: / //
		//=============//

		Matrix operator/(const Matrix& rhs) const
		{
			Matrix<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = m_data[i] / rhs.m_data[i];
			}
			return std::move(res);
		}

		Matrix operator/(T val) const
		{
			Matrix<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] / val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Matrix<U> operator/(U val, const Matrix<U>& rhs)
		{
			Matrix<U> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val / rhs.At(i);
			}
			return std::move(res);
		}

		Matrix& operator/=(const Matrix& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		Matrix& operator/=(T val)
		{
			*this = *this / val;
			return *this;
		}

		//============================//
		// Assignment value operators //
		//============================//

		Matrix& operator=(T val)
		{
			for (size_t i = 0; i < TotalElements(); i++)
			{
				m_data[i] = val;
			}
			return *this;
		}

		[[nodiscard]] size_t TotalElements() const
		{
			return static_cast<size_t>(m_nrows) * m_ncols;
		}

		[[nodiscard]] uint32_t NRows() const
		{
			return m_nrows;
		}

		[[nodiscard]] uint32_t NCols() const
		{
			return m_ncols;
		}

	private:

		std::unique_ptr<T[]> m_data;
		uint32_t m_nrows = 0;
		uint32_t m_ncols = 0;
	};
}