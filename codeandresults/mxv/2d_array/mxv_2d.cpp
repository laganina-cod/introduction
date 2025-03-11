#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>


extern "C" {
	double* mxv(int n, double** matrix, double* vector, double* result) {
		if (n < 1 || matrix == nullptr || vector == nullptr || result == nullptr) return nullptr;
		for (int i = 0; i < n; ++i) {
			result[i] = 0;
			for (int j = 0; j < n; ++j) {
				result[i] = result[i] + matrix[i][j] * vector[j];
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
	int data_method = std::stoi(argv[2]);
	double** matrix=new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n];
	}
	double* vector = new double[n];
	double* result = new double[n];
	if (data_method == 1) {
		for (int k = 0; k < n; k++) {
			vector[k] = 0.0;
			for (int j = 0; j < n; j++) {
				matrix[k][j] = 0;
			}

		}
	}
	else if (data_method == 2) {

		std::random_device rd;  // �������� ��������� �����
		std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)
		std::uniform_real_distribution<> dis(0.0, 1.0); // ����������� ������������� �� 0 �� 1
		for (int k = 0; k < n; k++) {
			vector[k] = dis(gen);
			for (int j = 0; j < n; j++) {
				matrix[k][j] = dis(gen);
			}

		}
	}
	else {
		for (int k = 0; k < n; k++) {
			vector[k] = 2.0;
			for (int j = 0; j < n; j++) {
				matrix[k][j] = 2.0;
			}
		}
	}
	double t1 = omp_get_wtime();

	result = mxv(n, matrix, vector, result);

	double t2 = omp_get_wtime();
	t2 -= t1;
	std::cout << t2 << std::endl;
    for(int i=0;i<n;i++){
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] vector;
	delete[] result;
	return 0;
}
