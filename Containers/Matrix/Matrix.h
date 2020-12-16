#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "../DenseContainer/DenseContainer.h"

namespace SEPOLIA4::CONTAINERS
{
	template<typename T>
	class Matrix final: public DenseContainer<T>
	{
	public:

		Matrix() = default;

		explicit Matrix(uint32_t nrows, uint32_t ncols) : DenseContainer<T>(nrows, ncols)
		{}

		explicit Matrix(const std::vector<std::vector<T>>& mat) : DenseContainer<T>(mat)
		{}

		Matrix(const std::initializer_list<std::initializer_list<T>>& initMatrix): DenseContainer<T>(initMatrix)
		{}

		Matrix(const Matrix& other) : DenseContainer<T>(other)
		{}

		Matrix(Matrix&& other) noexcept: DenseContainer<T>(other)
		{}

		~Matrix() = default;

		using DenseContainer<T>::operator=;

		Matrix<T>& operator=(const Matrix<T>& other)
		{
			DenseContainer<T>::operator=(other);
			return *this;
		}

		Matrix<T>& operator=(Matrix<T>&& other)
		{
			DenseContainer<T>::operator=(other);
			return *this;
		}

		[[nodiscard]] uint32_t NRows() const
		{
			return DenseContainer<T>::m_nrows;
		}

		[[nodiscard]] uint32_t NCols() const
		{
			return DenseContainer<T>::m_ncols;
		}

		bool Allocate(uint32_t nrows, uint32_t ncols)
		{
			return DenseContainer<T>::Allocate(nrows, ncols);
		}
	};
}