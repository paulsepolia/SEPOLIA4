#pragma once
#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace SEPOLIA4::CONTAINERS
{
	template<typename T>
	class DenseContainer
	{
	public:

		//==============//
		// Constructors //
		//==============//

		DenseContainer() = default;

		explicit DenseContainer(size_t size)
		{
			Allocate(1, size);
		}

		explicit DenseContainer(size_t nrows, size_t ncols)
		{
			Allocate(nrows, ncols);
		}

		explicit DenseContainer(const std::vector<std::vector<T>>& mat)
		{
			const auto NROWS = mat.size();
			const auto NCOLS = mat[0].size();

			Allocate(NROWS, NCOLS);

			for (uint32_t i = 0; i < NROWS; i++)
			{
				for (uint32_t j = 0; j < NCOLS; j++)
				{
					operator[](static_cast<size_t>(i) * NCOLS + j) = mat[i][j];
				}
			}
		}

		DenseContainer(const std::initializer_list<std::initializer_list<T>>& initMatrix)
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

		DenseContainer(const DenseContainer& other)
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

		DenseContainer& operator=(const DenseContainer& other)
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

		DenseContainer(DenseContainer&& other) noexcept
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

		virtual DenseContainer& operator=(DenseContainer&& other) noexcept
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

		virtual ~DenseContainer() = default;

		//===================//
		// Memory management //
		//===================//

		bool Allocate(size_t nrows, size_t ncols)
		{
			try
			{
				if (m_data) Deallocate();
				m_size = nrows * ncols;
				m_nrows = nrows;
				m_ncols = ncols;
				m_data = std::make_unique<T[]>(m_size);
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
			m_size = 0;
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

		[[nodiscard]] const T& At(size_t idx) const
		{
			return m_data[idx];
		}

		virtual T& operator()(uint32_t rowIdx, uint32_t colIdx)
		{
			return m_data[rowIdx * static_cast<size_t>(m_ncols) + colIdx];
		}

		T& operator[](size_t idx)
		{
			return m_data[idx];
		}

		//================//
		// Check equality //
		//================//

		bool operator==(const DenseContainer& rhs) const
		{
			if (m_ncols != rhs.m_ncols) return false;
			if (m_nrows != rhs.m_nrows) return false;
			if (m_size != rhs.m_size) return false;

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
		friend bool operator==(U val, const DenseContainer<U>& rhs)
		{
			return rhs == val;
		}

		bool operator!=(const DenseContainer& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator!=(T val) const
		{
			return !(*this == val);
		}

		template<typename U>
		friend bool operator!=(U val, const DenseContainer<U>& rhs)
		{
			return rhs != val;
		}

		//======================//
		// arithmetic operators //
		//======================//

		//=============//
		// operator: + //
		//=============//

		DenseContainer operator+(const DenseContainer& rhs) const
		{
			DenseContainer<T> res;

			res.Allocate(m_nrows, m_ncols);

			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] + rhs.m_data[i];
			}

			return std::move(res);
		}

		DenseContainer operator+(T val) const
		{
			DenseContainer<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] + val;
			}
			return std::move(res);
		}

		template<typename U>
		friend DenseContainer<U> operator+(U val, const DenseContainer<U>& rhs)
		{
			DenseContainer<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);

			for (size_t i = 0; i < res.TotalElements(); i++)
			{
				res[i] = val + rhs.m_data[i];
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

		DenseContainer& operator+=(const DenseContainer& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		DenseContainer& operator+=(T val)
		{
			*this = *this + val;
			return *this;
		}

		//=============//
		// operator: - //
		//=============//

		DenseContainer operator-(const DenseContainer& rhs) const
		{
			DenseContainer res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] - rhs.m_data[i];
			}
			return std::move(res);
		}

		DenseContainer operator-(T val) const
		{
			DenseContainer res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] - val;
			}
			return std::move(res);
		}

		template<typename U>
		friend DenseContainer<U> operator-(U val, const DenseContainer<U>& rhs)
		{
			DenseContainer<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val - rhs.m_data[i];
			}
			return std::move(res);
		}

		template<typename U>
		friend DenseContainer<U> operator-(const DenseContainer<U>& rhs)
		{
			DenseContainer<T> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = -rhs.m_data[i];
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

		DenseContainer& operator-=(const DenseContainer& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		DenseContainer& operator-=(T val)
		{
			*this = *this - val;
			return *this;
		}

		//=============//
		// operator: * //
		//=============//

		DenseContainer operator*(const DenseContainer& rhs) const
		{
			DenseContainer res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] * rhs.m_data[i];
			}
			return std::move(res);
		}

		DenseContainer operator*(T val) const
		{
			DenseContainer<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] * val;
			}
			return std::move(res);
		}

		template<typename U>
		friend DenseContainer<U> operator*(U val, const DenseContainer<U>& rhs)
		{
			DenseContainer<U> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val * rhs.m_data[i];
			}
			return std::move(res);
		}

		DenseContainer& operator*=(const DenseContainer& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		DenseContainer& operator*=(T val)
		{
			*this = *this * val;
			return *this;
		}

		//=============//
		// operator: / //
		//=============//

		DenseContainer operator/(const DenseContainer& rhs) const
		{
			DenseContainer<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = m_data[i] / rhs.m_data[i];
			}
			return std::move(res);
		}

		DenseContainer operator/(T val) const
		{
			DenseContainer<T> res;
			res.Allocate(m_nrows, m_ncols);
			for (size_t i = 0; i < TotalElements(); i++)
			{
				res[i] = m_data[i] / val;
			}
			return std::move(res);
		}

		template<typename U>
		friend DenseContainer<U> operator/(U val, const DenseContainer<U>& rhs)
		{
			DenseContainer<U> res;
			res.Allocate(rhs.m_nrows, rhs.m_ncols);
			for (size_t i = 0; i < rhs.TotalElements(); i++)
			{
				res[i] = val / rhs.m_data[i];
			}
			return std::move(res);
		}

		DenseContainer& operator/=(const DenseContainer& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		DenseContainer& operator/=(T val)
		{
			*this = *this / val;
			return *this;
		}

		//============================//
		// Assignment value operators //
		//============================//

		virtual DenseContainer<T>& operator=(T val)
		{
			for (size_t i = 0; i < TotalElements(); i++)
			{
				m_data[i] = val;
			}
			return *this;
		}

		[[nodiscard]] size_t TotalElements() const
		{
			return m_size;
		}

	protected:

		std::unique_ptr<T[]> m_data;
		size_t m_nrows = 0;
		size_t m_ncols = 0;
		size_t m_size = 0;
	};
}