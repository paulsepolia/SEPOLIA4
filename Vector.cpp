#include "Vector.h"
#include "CommonHeaders.h"
#include <exception>
#include <iostream>
#include <cassert>

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

size_t Vector::Size() const
{
	return m_size;
}

double Vector::operator()(size_t idx) const
{
	return m_data[idx];
}

double& Vector::operator()(size_t idx)
{
	return m_data[idx];
}

bool Vector::operator==(const Vector& other) const
{
	assert(m_data);
	assert(other.m_data);

	if (m_size != other.Size()) return false;

	for (size_t i = 0; i < other.Size(); i++)
	{
		if (m_data[i] != other.m_data[i]) return false;
	}

	return true;
}

bool Vector::operator!=(const Vector& other) const
{
	return !(*this == other);
}

//========================//
// vector OPERATOR vector //
//========================//

Vector Vector::operator+(const Vector& other) const
{
	if constexpr (DEBUG_CHECK) assert(m_size == other.Size());
	if constexpr (DEBUG_CHECK) assert(m_data);
	if constexpr (DEBUG_CHECK) assert(other.m_data);

	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < other.Size(); i++)
	{
		res(i) = m_data[i] + other.m_data[i];
	}

	return std::move(res);
}

Vector Vector::operator-(const Vector& other) const
{
	if constexpr (DEBUG_CHECK) assert(m_size == other.Size());
	if constexpr (DEBUG_CHECK) assert(m_data);
	if constexpr (DEBUG_CHECK) assert(other.m_data);

	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < other.Size(); i++)
	{
		res(i) = m_data[i] - other.m_data[i];
	}

	return std::move(res);
}

Vector Vector::operator*(const Vector& other) const
{
	if constexpr (DEBUG_CHECK) assert(m_size == other.Size());
	if constexpr (DEBUG_CHECK) assert(m_data);
	if constexpr (DEBUG_CHECK) assert(other.m_data);

	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < other.Size(); i++)
	{
		res(i) = m_data[i] * other.m_data[i];
	}

	return std::move(res);
}

Vector Vector::operator/(const Vector& other) const
{
	if constexpr (DEBUG_CHECK) assert(m_size == other.Size());
	if constexpr (DEBUG_CHECK) assert(m_data);
	if constexpr (DEBUG_CHECK) assert(other.m_data);

	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < other.Size(); i++)
	{
		if constexpr (DEBUG_CHECK) assert(other.m_data[i]);
		res(i) = m_data[i] / other.m_data[i];
	}

	return std::move(res);
}

//========================//
// vector OPERATOR double //
//========================//

Vector Vector::operator+(double value) const
{
	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < m_size; i++)
	{
		res(i) = m_data[i] + value;
	}
	return *this;
}

Vector Vector::operator-(double value) const
{
	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < m_size; i++)
	{
		res(i) = m_data[i] - value;
	}
	return *this;
}

Vector Vector::operator*(double value) const
{
	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < m_size; i++)
	{
		res(i) = m_data[i] * value;
	}
	return *this;
}

Vector Vector::operator/(double value) const
{
	if constexpr (DEBUG_CHECK) assert(value);
	Vector res;
	if constexpr (DEBUG_CHECK) assert(res.Allocate(m_size));
	else res.Allocate(m_size);

	for (size_t i = 0; i < m_size; i++)
	{
		res(i) = m_data[i] / value;
	}
	return *this;
}

//======================//
// double OPERATOR type //
//======================//

Vector operator*(const Vector&, double)
{

}

Vector operator/(const Vector&, double)
{

}

Vector operator+(const Vector&, double)
{

}

Vector operator-(const Vector&, double)
{

}
