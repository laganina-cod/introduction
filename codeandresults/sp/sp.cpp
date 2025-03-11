#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>

extern "C" {
 double sp(int n, double* first, double* second) {
	if (n < 1 || first == nullptr || second == nullptr) return -1;
	double result = 0;
	for (int i = 0; i < n; i++) {
		result = result + first[i] * second[i];
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
	int data_method = std::stoi(argv[2]);
	double* first= new double[n];
	double* second= new double[n];
	if (data_method == 1) {
		for (int k = 0; k < n; k++) {
			first[k] = 0;
			second[k] = 0;
		}
	}
	else if (data_method == 2) {
		std::random_device rd;  // Источник случайных чисел
		std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)
		std::uniform_real_distribution<> dis(0.0, 1.0); // Равномерное распределение от 0 до 1
		for (int k = 0; k < n; k++) {
			first[k]= dis(gen);
			second[k] = dis(gen);
		}
	}

	else if (data_method == 3) {
		for (int k = 0; k < n; k++) {
			first[k] = 2.0;
			second[k] = 2.0;
		}
	}
	double t1 = omp_get_wtime();

	double result= sp(n,first,second);

	double t2 = omp_get_wtime();
	t2 -= t1;
	std::cout << t2 << std::endl;
    delete[] first;
	delete[] second;
	return 0;
}
