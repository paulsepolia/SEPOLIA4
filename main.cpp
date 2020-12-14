#include "BoostUblas/BoostUblasTests.h"
#include <iostream>

//#include <cblas.h>
//int main()
//{
//	// Create arrays that represent the matrices A,B,C
//	const int n = 20;
//	auto* A = new double[n * n];
//	auto* B = new double[n * n];
//	auto* C = new double[n * n];
//
//	// Fill A and B with random numbers
//	for (uint32_t i = 0; i < n; i++)
//	{
//		for (uint32_t j = 0; j < n; j++)
//		{
//			A[i * n + j] = 1;
//			B[i * n + j] = 1;
//		}
//	}
//
//	// Calculate A*B=C
//	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A, n, B, n, 0.0, C, n);
//
//	std::cout << C[0] << std::endl;
//	std::cout << C[1] << std::endl;
//	std::cout << C[2] << std::endl;
//
//	// Clean up
//	delete[] A;
//	delete[] B;
//	delete[] C;
//
//	return 0;
//}

int main()
{
	{
		using namespace TESTS_BOOST_UBLAS;
		std::cout << "-->> Tests -->> Boost -->> Ublas" << std::endl;
		TEST1();
	}
}
