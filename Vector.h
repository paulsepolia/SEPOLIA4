#pragma once

#include <cstdint>
#include <cstdio>

class Vector final
{
public:

	Vector() = default;

	Vector(const Vector& other);

	Vector& operator=(const Vector& other);

	Vector(Vector&& other) noexcept;

	Vector& operator=(Vector&& other) noexcept;

	bool Allocate(size_t size);

	bool Deallocate();

	[[nodiscard]] size_t Size() const;

	double operator()(size_t idx) const;

	double& operator()(size_t idx);

	~Vector();

private:

	double* p = nullptr;
	size_t m_size = 0;
};

