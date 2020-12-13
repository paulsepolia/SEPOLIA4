#include "Vector.h"
#include <exception>
#include <iostream>

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
			p[i] = other.p[i];
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
			p[i] = other.p[i];
		}
	}
	return *this;
}

//==================//
// Move constructor //
//==================//

Vector::Vector(Vector&& other) noexcept
{
	if(this != &other)
	{
		if (p) Deallocate();
		p = other.p;
		m_size = other.m_size;
		other.p = nullptr;
		other.m_size = 0;
	}
}

//=============================//
// Move assignment constructor //
//=============================//

Vector& Vector::operator=(Vector&& other) noexcept
{
	if(this != &other)
	{
		if (p) Deallocate();
		p = other.p;
		m_size = other.m_size;
		other.p = nullptr;
		other.m_size = 0;
	}
	return *this;
}

bool Vector::Allocate(size_t size)
{
	try
	{
		if (p) Deallocate();
		p = new double[size];
		m_size = size;
		return true;
	}
	catch (std::exception& e)
	{
		p = nullptr;
		std::cout << e.what() << std::endl;
	}
	return false;
}

bool Vector::Deallocate()
{
	delete[] p;
	p = nullptr;
	m_size = 0;
	return true;
}

size_t Vector::Size() const
{
	return m_size;
}

double Vector::operator[](size_t idx) const
{
	return p[idx];
}

double& Vector::operator[](size_t idx)
{
	return p[idx];
}

Vector::~Vector()
{
	delete[] p;
	p = nullptr;
	m_size = 0;
}
