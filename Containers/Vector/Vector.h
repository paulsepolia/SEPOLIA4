#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace SEPOLIA4::CONTAINERS
{
	template<typename T>
	class Vector final
	{
	public:

		//==============//
		// Constructors //
		//==============//

		Vector() = default;

		explicit Vector(size_t size)
		{
			Allocate(size);
		}

		explicit Vector(const std::vector<T>& vec)
		{
			Allocate(vec.size());
			for (size_t i = 0; i < vec.size(); i++)
			{
				m_data[i] = vec[i];
			}
		}

		Vector(const std::initializer_list<T>& initList)
		{
			Allocate(initList.size());
			size_t idx = 0;
			for (const auto& el : initList)
			{
				m_data[idx] = el;
				idx++;
			}
		}

		Vector(const Vector& other)
		{
			if (this != &other)
			{
				Allocate(other.m_size);
				m_size = other.m_size;
				for (size_t i = 0; i < m_size; i++)
				{
					m_data[i] = other.m_data[i];
				}
			}
		}

		Vector& operator=(const Vector& other)
		{
			if (this != &other)
			{
				Allocate(other.m_size);
				for (size_t i = 0; i < m_size; i++)
				{
					m_data[i] = other.m_data[i];
				}
			}
			return *this;
		}

		Vector(Vector&& other) noexcept
		{
			if (this != &other)
			{
				if (m_data) Deallocate();
				m_data = std::move(other.m_data);
				m_size = other.m_size;
				other.m_data = nullptr;
				other.m_size = 0;
			}
		}

		Vector& operator=(Vector&& other) noexcept
		{
			if (this != &other)
			{
				if (m_data) Deallocate();
				m_data = std::move(other.m_data);
				m_size = other.m_size;
				other.m_data = nullptr;
				other.m_size = 0;
			}
			return *this;
		}

		~Vector() = default;

		//===================//
		// Memory management //
		//===================//

		bool Allocate(size_t size)
		{
			try
			{
				if (m_data) Deallocate();
				m_data = std::make_unique<T[]>(size);
				m_size = size;
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

		[[nodiscard]] size_t Size() const
		{
			return m_size;
		}

		//======================================//
		// Operators to access and set elements //
		//======================================//

		[[nodiscard]] const T& At(size_t idx) const
		{
			return m_data[idx];
		}

		T& operator[](size_t idx)
		{
			return m_data[idx];
		}

		//================//
		// Check equality //
		//================//

		bool operator==(const Vector& rhs) const
		{
			if (m_size != rhs.Size()) return false;
			for (size_t i = 0; i < rhs.Size(); i++)
			{
				if (m_data[i] != rhs.m_data[i]) return false;
			}
			return true;
		}

		bool operator==(T val) const
		{
			for (size_t i = 0; i < Size(); i++)
			{
				if (m_data[i] != val) return false;
			}
			return true;
		}

		template<typename U>
		friend bool operator==(U val, const Vector<U>& rhs)
		{
			return rhs == val;
		}

		bool operator!=(const Vector& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator!=(T val) const
		{
			return !(*this == val);
		}

		template<typename U>
		friend bool operator!=(U val, const Vector<U>& rhs)
		{
			return rhs != val;
		}

		//======================//
		// arithmetic operators //
		//======================//

		//=============//
		// operator: + //
		//=============//

		Vector operator+(const Vector& rhs) const
		{
			Vector<T> res;
			res.Allocate(m_size);
			for (size_t i = 0; i < rhs.Size(); i++)
			{
				res.m_data[i] = m_data[i] + rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector operator+(T val) const
		{
			Vector<T> res;
			res.Allocate(m_size);
			for (size_t i = 0; i < m_size; i++)
			{
				res.m_data[i] = m_data[i] + val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Vector<U> operator+(U val, const Vector<U>& rhs)
		{
			Vector<T> res;
			res.Allocate(rhs.m_size);
			for (size_t i = 0; i < rhs.m_size; i++)
			{
				res.m_data[i] = val + rhs.m_data[i];
			}
			return std::move(res);
		}

		void operator++()
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_data[i]++;
			}
		}

		void operator++(int)
		{
			++(*this);
		}

		Vector& operator+=(const Vector& rhs)
		{
			*this = *this + rhs;
			return *this;
		}

		Vector& operator+=(T val)
		{
			*this = *this + val;
			return *this;
		}

		//=============//
		// operator: - //
		//=============//

		Vector operator-(const Vector& rhs) const
		{
			Vector res;
			res.Allocate(m_size);
			for (size_t i = 0; i < rhs.Size(); i++)
			{
				res.m_data[i] = m_data[i] - rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector operator-(T val) const
		{
			Vector res;
			res.Allocate(m_size);
			for (size_t i = 0; i < m_size; i++)
			{
				res.m_data[i] = m_data[i] - val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Vector<U> operator-(U val, const Vector<U>& rhs)
		{
			Vector<T> res;
			res.Allocate(rhs.m_size);
			for (size_t i = 0; i < rhs.m_size; i++)
			{
				res.m_data[i] = val - rhs.m_data[i];
			}
			return std::move(res);
		}

		template<typename U>
		friend Vector<U> operator-(const Vector<U>& rhs)
		{
			Vector<T> res;
			res.Allocate(rhs.m_size);
			for (size_t i = 0; i < rhs.m_size; i++)
			{
				res.m_data[i] = -rhs.m_data[i];
			}
			return std::move(res);
		}

		void operator--()
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_data[i]--;
			}
		}

		void operator--(int)
		{
			--(*this);
		}

		Vector& operator-=(const Vector& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		Vector& operator-=(T val)
		{
			*this = *this - val;
			return *this;
		}

		//=============//
		// operator: * //
		//=============//

		Vector operator*(const Vector& rhs) const
		{
			Vector res;
			res.Allocate(m_size);
			for (size_t i = 0; i < rhs.Size(); i++)
			{
				res.m_data[i] = m_data[i] * rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector operator*(T val) const
		{
			Vector<T> res;
			res.Allocate(m_size);
			for (size_t i = 0; i < m_size; i++)
			{
				res.m_data[i] = m_data[i] * val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Vector<U> operator*(U val, const Vector<U>& rhs)
		{
			Vector<T> res;
			res.Allocate(rhs.m_size);
			for (size_t i = 0; i < rhs.m_size; i++)
			{
				res.m_data[i] = val * rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector& operator*=(const Vector& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		Vector& operator*=(T val)
		{
			*this = *this * val;
			return *this;
		}

		//=============//
		// operator: / //
		//=============//

		Vector operator/(const Vector& rhs) const
		{
			Vector<T> res;
			res.Allocate(m_size);
			for (size_t i = 0; i < rhs.Size(); i++)
			{
				res.m_data[i] = m_data[i] / rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector operator/(T val) const
		{
			Vector<T> res;
			res.Allocate(m_size);
			for (size_t i = 0; i < m_size; i++)
			{
				res.m_data[i] = m_data[i] / val;
			}
			return std::move(res);
		}

		template<typename U>
		friend Vector<U> operator/(U val, const Vector<U>& rhs)
		{
			Vector<T> res;
			res.Allocate(rhs.m_size);
			for (size_t i = 0; i < rhs.m_size; i++)
			{
				res.m_data[i] = val / rhs.m_data[i];
			}
			return std::move(res);
		}

		Vector& operator/=(const Vector& rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		Vector& operator/=(T val)
		{
			*this = *this / val;
			return *this;
		}

		//============================//
		// Assignment value operators //
		//============================//

		Vector& operator=(T val)
		{
			for (size_t i = 0; i < m_size; i++)
			{
				m_data[i] = val;
			}
			return *this;
		}

	private:

		std::unique_ptr<T[]> m_data;
		size_t m_size = 0;
	};
}