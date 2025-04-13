#include <iostream>
#include <random>
#include <omp.h>
#include <cfloat>
#include <cmath>
#include <string>

extern "C" {
	double* mxm(int n, double* m1, double* m2, double* result) {
		if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) {
			return nullptr;
		}

		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < n; ++k) {
				result[i * n + k] = 0;
				for (int j = 0; j < n; ++j) {
					result[i * n + k] += m1[i * n + j] * m2[j * n + k];
				}
			}
		}
		return result;
	}
}

bool almostEqual(int n, double* a, double* b, double epsilon = 1e-6) {
	for (int i = 0; i < n * n; ++i) {
		if (std::abs(a[i] - b[i]) > epsilon) {
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

	double* m1 = new double[n * n];
	double* m2 = new double[n * n];
	double* result = new double[n * n];
	double* expected = new double[n * n];

	if (data_method == 1) {
		for (int i = 0; i < n * n; ++i) {
			m1[i] = 0.0;
			m2[i] = 0.0;
			expected[i] = 0.0;
		}
	}
	else if (data_method == 2) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);
		for (int i = 0; i < n * n; ++i) {
			m1[i] = dis(gen);
			m2[i] = dis(gen);
		}
	}
	else if (data_method == 3) {
		for (int i = 0; i < n * n; ++i) {
			m1[i] = 2.0;
			m2[i] = 2.0;
		}
		for (int i = 0; i < n; ++i) {
			for (int k = 0; k < n; ++k) {
				expected[i * n + k] = 4.0 * n;
			}
		}
	}
	else if (data_method == 4) {
		for (int i = 0; i < n * n; ++i) {
			m1[i] = 1.0e300;
			m2[i] = 1.0e300;
		}
	}
	else {
		std::cerr << "Invalid data method" << std::endl;
		delete[] m1;
		delete[] m2;
		delete[] result;
		delete[] expected;
		return 1;
	}

	double t1 = omp_get_wtime();
	double* res = mxm(n, m1, m2, result);
	double t2 = omp_get_wtime();
	t2 -= t1;

	if (res == nullptr) {
		std::cerr << "Error: Calculation failed due to invalid input." << std::endl;
		delete[] m1;
		delete[] m2;
		delete[] result;
		delete[] expected;
		return 1;
	}


	if (data_method != 4) {
		for (int i = 0; i < n * n; ++i) {
			if (result[i] > DBL_MAX || result[i] < -DBL_MAX) {
				std::cerr << "Error: Result overflow detected at position " << i
					<< " (result = " << result[i] << ")" << std::endl;
				delete[] m1;
				delete[] m2;
				delete[] result;
				delete[] expected;
				return 1;
			}
		}
	}


	if (data_method != 2 && data_method != 4) {
		if (!almostEqual(n, result, expected)) {
			std::cout << "Test case failed!" << std::endl;
			std::cout << "Expected: " << std::endl;
			for (int i = 0; i < n; ++i) {
				for (int k = 0; k < n; ++k) {
					std::cout << expected[i * n + k] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "Actual: " << std::endl;
			for (int i = 0; i < n; ++i) {
				for (int k = 0; k < n; ++k) {
					std::cout << result[i * n + k] << " ";
				}
				std::cout << std::endl;
			}
			delete[] m1;
			delete[] m2;
			delete[] result;
			delete[] expected;
			return 1;
		}
	}

	std::cout << t2 << std::endl;

	delete[] m1;
	delete[] m2;
	delete[] result;
	delete[] expected;

	return 0;
}
