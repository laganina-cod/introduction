#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>



extern "C" {
 double** mxm(int n, double** m1, double** m2, double** result) {
	if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) return nullptr;

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
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "The number of arguments is incorrect. One argument is required: the size of the matrix (n)." << std::endl;
		return 1;
	}

	int n = std::stoi(argv[1]);
	double** m1=new double* [n];
	double** m2=new double* [n];
	double** result=new double* [n];
	for (int i = 0; i < n; i++) {
		m1[i] = new double[n];
		m2[i] = new double[n];
		result[i] = new double[n];
		for (int j = 0; j < n; j++) {
			m1[i][j] = 0;
			m2[i][j] = 0;
			result[i][j] = 0;
		}
	}
	

	double t1 = omp_get_wtime();

	result = mxm(n, m1,m2,result);

	double t2 = omp_get_wtime();
	t2 -= t1;
	std::cout << t2 << std::endl;
    for(int i=0;i<n;i++){
		delete[] m1[i];
		delete[] m2[i];
		delete[] result[i];
	}
	delete[] m1;
	delete[] m2;
	delete[] result;
	return 0;
}