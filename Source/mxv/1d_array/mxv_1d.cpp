#include <iostream>
#include <random>
#include <omp.h>
#include <cfloat>
#include <cmath>
#include <string>  

extern "C" {
	double* mxv(int n, double* matrix, double* vector, double* result) {
		if (n < 1 || matrix == nullptr || vector == nullptr || result == nullptr) {
			return nullptr;
		}

		for (int i = 0; i < n; ++i) {
			result[i] = 0;
			for (int j = 0; j < n; ++j) {
				result[i] += matrix[i * n + j] * vector[j];
			}
		}
		return result;
	}
}

bool almostEqual(int n, const double* a, const double* b, double epsilon = 1e-6) {
	for (int i = 0; i < n; ++i) {
		if (std::fabs(a[i] - b[i]) >= epsilon) {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "The number of arguments is incorrect. Two arguments are required: the size of the matrix (n) and data filling type." << std::endl;
		return 1;
	}

	int n = std::stoi(argv[1]);
	int data_method = std::stoi(argv[2]);
	double* matrix = new double[n * n];
	double* vector = new double[n];
	double* result = new double[n];
	double* expected = new double[n];


	if (data_method == 1) {
		for (int i = 0; i < n * n; ++i) matrix[i] = 0.0;
		for (int i = 0; i < n; ++i) {
			vector[i] = 0.0;
			expected[i] = 0.0;
		}
	}
	else if (data_method == 2) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);
		for (int i = 0; i < n * n; ++i) matrix[i] = dis(gen);
		for (int i = 0; i < n; ++i) vector[i] = dis(gen);
	}
	else if (data_method == 3) {
		for (int i = 0; i < n * n; ++i) matrix[i] = 2.0;
		for (int i = 0; i < n; ++i) {
			vector[i] = 2.0;
			expected[i] = 4.0 * n;
		}
	}
	else if (data_method == 4) {
		for (int i = 0; i < n * n; ++i) matrix[i] = 1.0e300;
		for (int i = 0; i < n; ++i) vector[i] = 1.0e300;
	}
	else {
		std::cerr << "Invalid data method" << std::endl;
		delete[] matrix;
		delete[] vector;
		delete[] result;
		delete[] expected;
		return 1;
	}

	double t1 = omp_get_wtime();
	double* res = mxv(n, matrix, vector, result);
	double t2 = omp_get_wtime();
	t2 -= t1;

	if (res == nullptr) {
		std::cerr << "Error: Calculation failed due to invalid input." << std::endl;
		delete[] matrix;
		delete[] vector;
		delete[] result;
		delete[] expected;
		return 1;
	}


	if (data_method != 4) {
		for (int i = 0; i < n; ++i) {
			if (result[i] > DBL_MAX || result[i] < -DBL_MAX) {
				std::cerr << "Error: Result overflow detected at position " << i
					<< " (result = " << result[i] << ")" << std::endl;
				delete[] matrix;
				delete[] vector;
				delete[] result;
				delete[] expected;
				return 1;
			}
		}
	}

	if (data_method != 2 && data_method != 4) {
		if (!almostEqual(n, result, expected)) {
			std::cout << "Test case failed!" << std::endl;
			std::cout << "Expected: ";
			for (int i = 0; i < n; ++i) std::cout << expected[i] << " ";
			std::cout << "\nActual: ";
			for (int i = 0; i < n; ++i) std::cout << result[i] << " ";
			std::cout << std::endl;
			delete[] matrix;
			delete[] vector;
			delete[] result;
			delete[] expected;
			return 1;
		}
	}

	std::cout << t2 << std::endl;
	delete[] matrix;
	delete[] vector;
	delete[] result;
	delete[] expected;
	return 0;
}