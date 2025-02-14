#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
	if (argc != 2) {
		std::cerr << "The number of arguments is incorrect. One argument is required: the size of the matrix (n)." << std::endl;
		return 1;
	}

	int n = std::stoi(argv[1]);
	double* first= new double[n];
	double* second= new double[n];
	for (int k = 0; k < n; k++) {
		first[k] = 0;
		second[k] = 0;
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
