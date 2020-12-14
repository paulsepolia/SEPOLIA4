#pragma once

#include <memory>
#include <vector>

class Vector final
{
public:

	//==============//
	// Constructors //
	//==============//

	Vector() = default;

	explicit Vector(size_t size);

	explicit Vector(const std::vector<double>& vec);

	Vector(const std::initializer_list<double>& initList);

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

	[[nodiscard]] bool IsAllocated() const;

	[[nodiscard]] bool IsDeallocated() const;

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

	bool operator==(double val) const;

	friend bool operator==(double val, const Vector& rhs);

	bool operator!=(const Vector& rhs) const;

	bool operator!=(double val) const;

	friend bool operator!=(double val, const Vector& rhs);

	//======================//
	// arithmetic operators //
	//======================//

	//=============//
	// operator: + //
	//=============//

	Vector operator+(const Vector& rhs) const;

	Vector operator+(double val) const;

	friend Vector operator+(double val, const Vector& vec);

	void operator++();

	void operator++(int);

	Vector& operator+=(const Vector& rhs);

	Vector& operator+=(double);

	//=============//
	// operator: - //
	//=============//

	Vector operator-(const Vector& rhs) const;

	Vector operator-(double val) const;

	friend Vector operator-(double val, const Vector& vec);

	friend Vector operator-(const Vector& vec);

	void operator--();

	void operator--(int);

	Vector& operator-=(const Vector& rhs);

	Vector& operator-=(double);

	//=============//
	// operator: * //
	//=============//

	Vector operator*(const Vector& rhs) const;

	Vector operator*(double val) const;

	friend Vector operator*(double val, const Vector& vec);

	Vector& operator*=(const Vector& rhs);

	Vector& operator*=(double);

	//=============//
	// operator: / //
	//=============//

	Vector operator/(const Vector& rhs) const;

	Vector operator/(double val) const;

	friend Vector operator/(double val, const Vector& vec);

	Vector& operator/=(const Vector& rhs);

	Vector& operator/=(double);

	//============================//
	// Assignment value operators //
	//============================//

	Vector& operator=(double val);

private:

	std::unique_ptr<double[]> m_data;
	size_t m_size = 0;
};
