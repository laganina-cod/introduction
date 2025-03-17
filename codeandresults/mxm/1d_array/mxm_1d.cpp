#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>
#include <cfenv> // Для работы с флагами исключений
#include <cmath> // Для std::abs

extern "C" {
    double* mxm(int n, double* m1, double* m2, double* result) {
        if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) return nullptr;

        // Очистка флагов исключений перед вычислениями
        std::feclearexcept(FE_ALL_EXCEPT);

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                result[i * n + k] = 0;
                for (int j = 0; j < n; j++) {
                    result[i * n + k] += m1[i * n + j] * m2[j * n + k];

                    // Проверка на переполнение после каждого умножения и сложения
                    if (std::fetestexcept(FE_OVERFLOW)) {
                        std::cerr << "Error: Floating-point overflow detected in result[" << i << "][" << k << "]." << std::endl;
                        return nullptr;
                    }
                    if (std::fetestexcept(FE_INVALID)) {
                        std::cerr << "Error: Invalid operation detected in result[" << i << "][" << k << "]." << std::endl;
                        return nullptr;
                    }
                }
            }
        }

        return result;
    }
}

bool almostEqual(int n, double* a, double* b, double epsilon = 1e-6) {
    if (n <= 0) {
        return true;
    }

    if (a == nullptr || b == nullptr) {
        return false;
    }

    for (int i = 0; i < n * n; i++) {
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
    int flag = std::stoi(argv[2]);

    double* m1 = new double[n * n];
    double* m2 = new double[n * n];
    double* result = new double[n * n];
    double* expected = new double[n * n];

    if (flag == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m1[i * n + j] = 0.0;
                m2[i * n + j] = 0.0;
                expected[i * n + j] = 0.0;
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
                expected[i * n + j] = 4.0 * n;
            }
        }
    }

    double t1 = omp_get_wtime();

    result = mxm(n, m1, m2, result);

    double t2 = omp_get_wtime();
    t2 -= t1;

    // Проверка на ошибку в функции mxm
    if (result == nullptr) {
        std::cerr << "Error: Calculation failed due to floating-point exception." << std::endl;
        delete[] m1;
        delete[] m2;
        delete[] result;
        delete[] expected;
        return 1;
    }

    // Проверка корректности результата (для методов 1 и 3)
    if (flag != 2) {
        if (!almostEqual(n, result, expected)) {
            std::cout << "Test case " << n << " " << flag << " failed! Expected: " << std::endl;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    std::cout << expected[j * n + k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "But got: " << std::endl;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    std::cout << result[j * n + k] << " ";
                }
                std::cout << std::endl;
            }
            std::cerr << "Error: result is incorrect!" << std::endl;
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