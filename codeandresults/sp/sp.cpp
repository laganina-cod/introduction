#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>
#include <cmath>   // Для std::fabs, std::isinf, std::isnan
#include <cfenv>   // Для работы с флагами исключений

extern "C" {
    double sp(int n, double* first, double* second) {
        if (n < 1 || first == nullptr || second == nullptr) return -1;
        double result = 0;
        std::feclearexcept(FE_ALL_EXCEPT); // Очистка флагов перед вычислениями

        for (int i = 0; i < n; i++) {
            double term = first[i] * second[i];
            result += term;

            // Проверка на переполнение или NaN
            if (std::isinf(term) || std::isnan(term)) {
                std::cerr << "Error: Invalid term detected (term is infinite or NaN)." << std::endl;
                return -1;
            }
        }

        // Проверка флагов исключений
        if (std::fetestexcept(FE_OVERFLOW)) {
            std::cerr << "Error: Floating-point overflow detected in result." << std::endl;
            return -1;
        }
        if (std::fetestexcept(FE_DIVBYZERO)) {
            std::cerr << "Error: Division by zero detected." << std::endl;
            return -1;
        }
        if (std::fetestexcept(FE_INVALID)) {
            std::cerr << "Error: Invalid operation detected." << std::endl;
            return -1;
        }

        return result;
    }
}

extern "C" {
    double sp_inf(int n, double* first, double* second) {
        if (n < 1 || first == nullptr || second == nullptr) return -1;
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

    if (data_method == 1) {
        for (int k = 0; k < n; k++) {
            first[k] = 0.0;
            second[k] = 0.0;
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
            first[k] = 2.0;
            second[k] = 2.0;
        }
        expected = 4.0 * n;
    }

    else if (data_method == 4) {
        for (int k = 0; k < n; k++) {
            first[k] = 1.0e300;
            second[k] = 1.0e300;
        }
    }

    if(data_method==4){
    
        double t1 = omp_get_wtime();
        double result = sp_inf(n, first, second);
        double t2 = omp_get_wtime();
        t2 -= t1;
    
        if (result == -1) {
            std::cerr << "Error: Calculation failed due to floating-point exception." << std::endl;
            delete[] first;
            delete[] second;
            return 1;
        }
        std::cout << t2 << std::endl;
        delete[] first;
        delete[] second;
        return 0;
    
    }

    double t1 = omp_get_wtime();
    double result = sp(n, first, second);
    double t2 = omp_get_wtime();
    t2 -= t1;


    // Проверка на ошибку в функции sp
    if (result == -1) {
        std::cerr << "Error: Calculation failed due to floating-point exception." << std::endl;
        delete[] first;
        delete[] second;
        return 1;
    }

    // Проверка корректности результата (для методов 1 и 3)
    if (data_method != 2) {
        if (!almostEqual(result, expected)) {
            std::cout << "Test case failed! Expected: " << expected
                << ", Actual: " << result << std::endl;
            delete[] first;
            delete[] second;
            return 1;
        }
    }

    std::cout << t2 << std::endl;
    delete[] first;
    delete[] second;
    return 0;
}