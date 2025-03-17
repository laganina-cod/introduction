#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <string>
#include <omp.h>
#include <cfenv> // Для работы с флагами исключений
#include <cmath> // Для std::fabs

extern "C" {
    double* mxv(int n, double** matrix, double* vector, double* result) {
        if (n < 1 || matrix == nullptr || vector == nullptr || result == nullptr) return nullptr;

        // Очистка флагов исключений перед вычислениями
        std::feclearexcept(FE_ALL_EXCEPT);

        for (int i = 0; i < n; ++i) {
            result[i] = 0;
            for (int j = 0; j < n; ++j) {
                result[i] += matrix[i][j] * vector[j];

                // Проверка на переполнение после каждого умножения и сложения
                if (std::fetestexcept(FE_OVERFLOW)) {
                    std::cerr << "Error: Floating-point overflow detected in result[" << i << "]." << std::endl;
                    return nullptr;
                }
                if (std::fetestexcept(FE_INVALID)) {
                    std::cerr << "Error: Invalid operation detected in result[" << i << "]." << std::endl;
                    return nullptr;
                }
            }
        }

        return result;
    }
}

bool almostEqual(int n, const double* a, const double* b, double epsilon = 1e-6) {
    if (a == nullptr || b == nullptr) {
        return false;
    }

    if (n <= 0) {
        return true;
    }

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
    double** matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }
    double* vector = new double[n];
    double* result = new double[n];
    double* expected = new double[n];

    if (data_method == 1) {
        for (int k = 0; k < n; k++) {
            vector[k] = 0.0;
            for (int j = 0; j < n; j++) {
                matrix[k][j] = 0;
            }
            expected[k] = 0.0;
        }
    }
    else if (data_method == 2) {
        std::random_device rd;  // Источник случайных чисел
        std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)
        std::uniform_real_distribution<> dis(0.0, 1.0); // Равномерное распределение от 0 до 1
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
            expected[k] = 4.0 * n;
        }
    }

    double t1 = omp_get_wtime();

    result = mxv(n, matrix, vector, result);

    double t2 = omp_get_wtime();
    t2 -= t1;

    // Проверка на ошибку в функции mxv
    if (result == nullptr) {
        std::cerr << "Error: Calculation failed due to floating-point exception." << std::endl;
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] vector;
        delete[] result;
        delete[] expected;
        return 1;
    }

    // Проверка корректности результата (для методов 1 и 3)
    if (data_method != 2) {
        if (!almostEqual(n, result, expected)) {
            std::cout << "Test case " << n << " " << data_method << " failed! Expected: ";
            for (int j = 0; j < n; j++) {
                std::cout << expected[j] << " ";
            }
            std::cout << ", but got: ";
            for (int j = 0; j < n; j++) {
                std::cout << result[j] << " ";
            }
            std::cout << std::endl;
            std::cerr << "Error: result is incorrect" << std::endl;
            for (int i = 0; i < n; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            delete[] vector;
            delete[] result;
            delete[] expected;
            return 1;
        }
    }

    std::cout << t2 << std::endl;
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vector;
    delete[] result;
    delete[] expected;
    return 0;
}