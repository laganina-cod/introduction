#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>



extern "C" {
 double* mxm(int n, double* m1, double* m2, double* result) {
	if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) return nullptr;

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			result[i*n+k] = 0;
			for (int j = 0; j < n; j++) {
				result[i*n+k] = result[i*n+k] + m1[i*n+j] * m2[j*n+k];
			}
		}
	}
	return result;
 }
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "The number of arguments is incorrect. Two arguments is required: the size of the matrix (n) and data filing type." << std::endl;
		return 1;
	}

	int n = std::stoi(argv[1]);
	int flag = std::stoi(argv[2]);

	double* m1 = new double [n * n];
	double* m2 = new double [n * n];
	double* result = new double [n * n];
	if (flag == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m1[i * n + j] = 0.0;
				m2[i * n + j] = 0.0;
			}
		}
	}
	else if (flag == 2) {
		std::random_device rd;  // Источник случайных чисел
		std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)
		std::uniform_real_distribution<> dis(0.0, 1.0); // Равномерное распределение от 0 до 1

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m1[i * n + j] = dis(gen);
				m2[i * n + j] = dis(gen);
			}
		}
	}
	else if (flag == 3) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				m1[i * n + j] = 2.0;
				m2[i * n + j] = 2.0;
			}
		}
	}
	double t1 = omp_get_wtime();

	result = mxm(n, m1, m2, result);

	double t2 = omp_get_wtime();
	t2 -= t1;
	std::cout << t2 << std::endl;
	delete[] m1;
	delete[] m2;
	delete[] result;
	return 0;
}