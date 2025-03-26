#include <iostream>  // Для std::cerr, std::cout
#include <random>    // Для std::random_device, std::mt19937, std::uniform_real_distribution
#include <omp.h>     // Для omp_get_wtime()
#include <cfloat>    // Для DBL_MAX
#include <cmath>  // Для std::fabs
#include <string>

extern "C" {
    double sp(int n, double* first, double* second) {
        if (n < 1 || first == nullptr || second == nullptr) {
            return -1;
        }

        double result = 0;
        for (int i = 0; i < n; i++) {
            result += first[i] * second[i];
        }
        return result;
    }
}

bool almostEqual(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "The number of arguments is incorrect. Two arguments are required: the size of the vectors (n) and data filling type." << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    int data_method = std::stoi(argv[2]);
    double* first = new double[n];
    double* second = new double[n];
    double expected;

    // Инициализация массивов
    if (data_method == 1) {
        for (int k = 0; k < n; k++) {
            first[k] = second[k] = 0.0;
        }
        expected = 0.0;
    }
    else if (data_method == 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        for (int k = 0; k < n; k++) {
            first[k] = dis(gen);
            second[k] = dis(gen);
        }
    }
    else if (data_method == 3) {
        for (int k = 0; k < n; k++) {
            first[k] = second[k] = 2.0;
        }
        expected = 4.0 * n;
    }
    else if (data_method == 4) {
        for (int k = 0; k < n; k++) {
            first[k] = second[k] = 1.0e300;
        }
    }

    double t1 = omp_get_wtime();
    double result = sp(n, first, second);
    double t2 = omp_get_wtime();
    t2 -= t1;

    // Проверки результатов
    if (result == -1) {
        std::cerr << "Error: Calculation failed due to invalid input." << std::endl;
        delete[] first;
        delete[] second;
        return 1;
    }

    if (data_method != 4 && (result > DBL_MAX || result < -DBL_MAX)) {
        std::cerr << "Error: Result overflow detected (result = " << result << ")" << std::endl;
        delete[] first;
        delete[] second;
        return 1;
    }

    if (data_method != 2 && data_method != 4 && !almostEqual(result, expected)) {
        std::cout << "Test case failed! Expected: " << expected
            << ", Actual: " << result << std::endl;
        delete[] first;
        delete[] second;
        return 1;
    }

    std::cout << t2 << std::endl;
    delete[] first;
    delete[] second;
    return 0;
}