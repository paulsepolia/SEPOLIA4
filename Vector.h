#pragma once

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

	[[nodiscard]] const double& At(size_t idx) const;

	double& operator[](size_t idx);

	//================//
	// Check equality //
	//================//

	bool operator==(const Vector& rhs) const;

	bool operator!=(const Vector& rhs) const;

	//========================//
	// vector OPERATOR vector //
	//========================//

	Vector operator+(const Vector& rhs) const;

	Vector operator-(const Vector& rhs) const;

	Vector operator*(const Vector& rhs) const;

	Vector operator/(const Vector& rhs) const;

	//=======================//
	// vector OPERATOR value //
	//=======================//

	Vector operator+(double val) const;

	Vector operator-(double val) const;

	Vector operator*(double val) const;

	Vector operator/(double val) const;

	//=======================//
	// value OPERATOR Vector //
	//=======================//

	friend Vector operator*(double val, const Vector& vec);

	friend Vector operator/(double val, const Vector& vec);

	friend Vector operator+(double val, const Vector& vec);

	friend Vector operator-(double val, const Vector& vec);

	//============================//
	// Assignment value operators //
	//============================//

	Vector& operator=(double val);

private:

	std::unique_ptr<double[]> m_data;
	size_t m_size = 0;
};
