#pragma once

#include <cstdint>
#include <cstdio>
#include <memory>

class Vector final
{
public:

	//==============//
	// Constructors //
	//==============//

	Vector() = default;

	Vector(const Vector& other);

	Vector& operator=(const Vector& other);

	Vector(Vector&& other) noexcept;

	Vector& operator=(Vector&& other) noexcept;

	~Vector() = default;

	//===================//
	// Memory management //
	//===================//

	bool Allocate(size_t size);

	bool Deallocate();

	[[nodiscard]] size_t Size() const;

	//======================================//
	// Operators to access and set elements //
	//======================================//

	double operator()(size_t idx) const;

	double& operator()(size_t idx);

	//================//
	// Operators rest //
	//================//

	bool operator==(const Vector& rhs) const;

	bool operator!=(const Vector& rhs) const;

	//  vector OPERATOR vector

	Vector operator+(const Vector& rhs) const;

	Vector operator-(const Vector& rhs) const;

	Vector operator*(const Vector& rhs) const;

	Vector operator/(const Vector& rhs) const;

	//  vector OPERATOR double

	Vector operator+(double val) const;

	Vector operator-(double val) const;

	Vector operator*(double val) const;

	Vector operator/(double val) const;

	//  double OPERATOR type

	friend Vector operator*(const Vector& vec, double val);

	friend Vector operator/(const Vector& vec, double val);

	friend Vector operator+(const Vector& vec, double val);

	friend Vector operator-(const Vector& vec, double val);

private:

	std::unique_ptr<double[]> m_data;
	size_t m_size = 0;
};
