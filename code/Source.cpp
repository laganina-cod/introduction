#include <iostream>
#include <omp.h>
#include <random>
#include <fstream>
template <typename T>

T scalar_product(int n, T* first, T* second) {
	if (n < 1) {
		return -1;
	}
	T result = 0;
	for (int i = 0; i < n; i++) {
		result = result + first[i] * second[i];
	}
	return result;
}
template <typename U>
double sp_get_time(int n, int count) {
	U* first = new U[n];
	U* second = new U[n];
	for (int i = 0; i < n; i++) {
		first[i] = (U)rand();
		second[i] = (U)rand();
	}
	std::ofstream file1;
	file1.open("result.csv", std::ios::app);
	double t1 = omp_get_wtime();
	for (int i = 0; i < count; i++) {
		scalar_product(n, first, second);
	}
	double t2 = omp_get_wtime();
	t2 -= t1;
	file1 << n << ";" << t2 << ";" << std::endl;
	delete[] first;
	delete[] second;
	return t2;

}
template <typename T>
T* mxv(int n, T** matrix, T* vector, T* result) {
	if (n < 1) {
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		result[i] = 0;
	}
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			result[j] = result[j] + matrix[j][k] * vector[k];
		}
	}
	return result;
}

template <typename U>
double mxv_get_time(int n, int count) {
	U** matrix = new U * [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new U[n];
	}
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			matrix[j][k] = (U)rand();
		}
	}
	U* vector = new U[n];
	for (int z = 0; z < n; z++) {
		vector[z] = (U)rand();
	}
	U* result = new U[n];
	std::ofstream file1;
	file1.open("result.csv", std::ios::app);
	double t1 = omp_get_wtime();
	for (int i = 0; i < count; i++) {
		mxv<U>(n, matrix, vector, result);
	}
	double t2 = omp_get_wtime();
	t2 -= t1;
	file1 << n << ";" << t2 << ";" << std::endl;
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] vector;
	delete[] result;
	return t2;


}

template <typename T>
T** mxm(int n, T** m1, T** m2, T** result) {
	if (n < 1) {
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			result[i][k] = 0;
			for (int j = 0; j < n; j++) {
				result[i][k] = result[i][k] + m1[i][j] * m2[j][k];
			}
		}
	}
	return result;
}

template <typename U>
double mxm_get_time(int n, int count) {
	U** m1 = new U * [n];
	U** m2 = new U * [n];
	U** result = new U * [n];
	for (int i = 0; i < n; i++) {
		m1[i] = new U[n];
		m2[i] = new U[n];
		result[i] = new U[n];
	}
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			m1[j][k] = (U)rand();
			m2[j][k] = (U)rand();
		}
	}
	std::ofstream file1;
	file1.open("result.csv", std::ios::app);
	double t1 = omp_get_wtime();
	for (int i = 0; i < count; i++) {
		mxm<U>(n, m1, m2, result);
	}
	double t2 = omp_get_wtime();
	t2 -= t1;
	file1 << n << ";" << t2 << ";" << std::endl;
	for (int i = 0; i < n; i++) {
		delete[] m1[i];
		delete[] m2[i];
		delete[] result[i];
	}
	delete[] m1;
	delete[] m2;
	delete[] result;
	return t2;

}

int main() {
	int method, dim, number;
	std::cout << "Enter method(sp-1,mxv-2,mxm-3),dim,number" << std::endl;
	std::cin >> method;
	std::cin >> dim;
	std::cin >> number;
	if (dim <= 0) {
		std::cout << "incorrect dim" << std::endl;
		return 0;
	}
	if (number <= 0) {
		std::cout << "incorrect number" << std::endl;
		return 0;
	}
	if (method == 1) {
	sp_get_time<double>(dim, number);
	}
	else if (method == 2) {
		mxv_get_time<double>(dim, number);
	}
	else if (method == 3) {
		mxm_get_time<double>(dim, number);
	}
	else {
		std::cout << "incorrect method" << std::endl;
	}
}