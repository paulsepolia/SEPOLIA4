#include "Vector.h"
#include <exception>
#include <iostream>

namespace SEPOLIA4::CONTAINERS
{
	Vector::Vector(size_t size)
	{
		Allocate(size);
	}

	Vector::Vector(const std::vector<double>& vec)
	{
		Allocate(vec.size());

		for (size_t i = 0; i < vec.size(); i++)
		{
			operator[](i) = vec[i];
		}
	}

	Vector::Vector(const std::initializer_list<double>& initList)
	{
		Allocate(initList.size());

		size_t idx = 0;
		for (const auto& el : initList)
		{
			operator[](idx) = el;
			idx++;
		}
	}

	//==================//
	// Copy constructor //
	//==================//

	Vector::Vector(const Vector& other)
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

	//=============================//
	// Copy assignment constructor //
	//=============================//

	Vector& Vector::operator=(const Vector& other)
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

	//==================//
	// Move constructor //
	//==================//

	Vector::Vector(Vector&& other) noexcept
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

	//=============================//
	// Move assignment constructor //
	//=============================//

	Vector& Vector::operator=(Vector&& other) noexcept
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

	bool Vector::Allocate(size_t size)
	{
		try
		{
			if (m_data) Deallocate();
			m_data = std::make_unique<double[]>(size);
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

	bool Vector::Deallocate()
	{
		m_data.reset(nullptr);
		m_size = 0;
		return true;
	}

	bool Vector::IsAllocated() const
	{
		if (m_data) return true;
		return false;
	}

	bool Vector::IsDeallocated() const
	{
		return !IsAllocated();
	}

	size_t Vector::Size() const
	{
		return m_size;
	}

	const double& Vector::At(size_t idx) const
	{
		return m_data[idx];
	}

	double& Vector::operator[](size_t idx)
	{
		return m_data[idx];
	}

	//================//
	// Check equality //
	//================//

	bool Vector::operator==(const Vector& other) const
	{
		if (m_size != other.Size()) return false;

		for (size_t i = 0; i < other.Size(); i++)
		{
			if (m_data[i] != other.m_data[i]) return false;
		}
		return true;
	}

	bool Vector::operator==(double val) const
	{
		for (size_t i = 0; i < Size(); i++)
		{
			if (m_data[i] != val) return false;
		}
		return true;
	}

	bool operator==(double val, const Vector& rhs)
	{
		return rhs == val;
	}

	bool Vector::operator!=(const Vector& other) const
	{
		return !(*this == other);
	}

	bool Vector::operator!=(double val) const
	{
		return !(*this == val);
	}

	bool operator!=(double val, const Vector& rhs)
	{
		return rhs != val;
	}

	//======================//
	// arithmetic operators //
	//======================//

	//=============//
	// operator: + //
	//=============//

	Vector Vector::operator+(const Vector& other) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < other.Size(); i++)
		{
			res[i] = m_data[i] + other.m_data[i];
		}

		return std::move(res);
	}

	Vector Vector::operator+(double value) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			res[i] = m_data[i] + value;
		}
		return std::move(res);
	}

	Vector operator+(double val, const Vector& rhs)
	{
		Vector res;
		res.Allocate(rhs.m_size);

		for (size_t i = 0; i < rhs.m_size; i++)
		{
			res[i] = val + rhs.At(i);
		}
		return std::move(res);
	}

	void Vector::operator++()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			operator[](i)++;
		}
	}

	void Vector::operator++(int)
	{
		++(*this);
	}

	Vector& Vector::operator+=(const Vector& rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	Vector& Vector::operator+=(double val)
	{
		*this = *this + val;
		return *this;
	}

	//=============//
	// operator: - //
	//=============//

	Vector Vector::operator-(const Vector& other) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < other.Size(); i++)
		{
			res[i] = m_data[i] - other.m_data[i];
		}

		return std::move(res);
	}

	Vector Vector::operator-(double value) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			res[i] = m_data[i] - value;
		}
		return std::move(res);
	}

	Vector operator-(double val, const Vector& rhs)
	{
		Vector res;
		res.Allocate(rhs.m_size);

		for (size_t i = 0; i < rhs.m_size; i++)
		{
			res[i] = val - rhs.At(i);
		}
		return std::move(res);
	}

	Vector operator-(const Vector& rhs)
	{
		Vector res;
		res.Allocate(rhs.m_size);

		for (size_t i = 0; i < rhs.m_size; i++)
		{
			res[i] = -rhs.At(i);
		}
		return std::move(res);
	}

	void Vector::operator--()
	{
		for (size_t i = 0; i < m_size; i++)
		{
			operator[](i)--;
		}
	}

	void Vector::operator--(int)
	{
		--(*this);
	}

	Vector& Vector::operator-=(const Vector& rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	Vector& Vector::operator-=(double val)
	{
		*this = *this - val;
		return *this;
	}

	//=============//
	// operator: * //
	//=============//

	Vector Vector::operator*(const Vector& other) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < other.Size(); i++)
		{
			res[i] = m_data[i] * other.m_data[i];
		}

		return std::move(res);
	}

	Vector Vector::operator*(double value) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			res[i] = m_data[i] * value;
		}
		return std::move(res);
	}

	Vector operator*(double val, const Vector& rhs)
	{
		Vector res;
		res.Allocate(rhs.m_size);

		for (size_t i = 0; i < rhs.m_size; i++)
		{
			res[i] = val * rhs.At(i);
		}
		return std::move(res);
	}

	Vector& Vector::operator*=(const Vector& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector& Vector::operator*=(double val)
	{
		*this = *this * val;
		return *this;
	}

	//=============//
	// operator: / //
	//=============//

	Vector Vector::operator/(const Vector& other) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < other.Size(); i++)
		{
			res[i] = m_data[i] / other.m_data[i];
		}

		return std::move(res);
	}

	Vector Vector::operator/(double value) const
	{
		Vector res;
		res.Allocate(m_size);

		for (size_t i = 0; i < m_size; i++)
		{
			res[i] = m_data[i] / value;
		}
		return std::move(res);
	}

	Vector operator/(double val, const Vector& rhs)
	{
		Vector res;
		res.Allocate(rhs.m_size);

		for (size_t i = 0; i < rhs.m_size; i++)
		{
			res[i] = val / rhs.At(i);
		}
		return std::move(res);
	}

	Vector& Vector::operator/=(const Vector& rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	Vector& Vector::operator/=(double val)
	{
		*this = *this / val;
		return *this;
	}

	//============================//
	// Assignment value operators //
	//============================//

	Vector& Vector::operator=(double val)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_data[i] = val;
		}
		return *this;
	}
}