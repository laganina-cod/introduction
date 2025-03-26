#include <iostream>
#include <random>
#include <omp.h>
#include <cfloat>
#include <cmath>
#include <string>

extern "C" {
    double** mxm(int n, double** m1, double** m2, double** result) {
        if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) {
            return nullptr;
        }

        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                result[i][k] = 0;
                for (int j = 0; j < n; ++j) {
                    result[i][k] += m1[i][j] * m2[j][k];
                }
            }
        }
        return result;
    }
}

bool almostEqual(int n, double** a, double** b, double epsilon = 1e-6) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (std::fabs(a[i][j] - b[i][j]) > epsilon) {
                return false;
            }
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

    // Выделение памяти
    double** m1 = new double* [n];
    double** m2 = new double* [n];
    double** result = new double* [n];
    double** expected = new double* [n];
    for (int i = 0; i < n; ++i) {
        m1[i] = new double[n];
        m2[i] = new double[n];
        result[i] = new double[n];
        expected[i] = new double[n];
    }

    // Инициализация данных
    if (data_method == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m1[i][j] = 0.0;
                m2[i][j] = 0.0;
                expected[i][j] = 0.0;
            }
        }
    }
    else if (data_method == 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m1[i][j] = dis(gen);
                m2[i][j] = dis(gen);
            }
        }
    }
    else if (data_method == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m1[i][j] = 2.0;
                m2[i][j] = 2.0;
                expected[i][j] = 4.0 * n;
            }
        }
    }
    else if (data_method == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                m1[i][j] = 1.0e300;
                m2[i][j] = 1.0e300;
            }
        }
    }
    else {
        std::cerr << "Invalid data method" << std::endl;
        // Освобождение памяти
        for (int i = 0; i < n; ++i) {
            delete[] m1[i];
            delete[] m2[i];
            delete[] result[i];
            delete[] expected[i];
        }
        delete[] m1;
        delete[] m2;
        delete[] result;
        delete[] expected;
        return 1;
    }

    double t1 = omp_get_wtime();
    double** res = mxm(n, m1, m2, result);
    double t2 = omp_get_wtime();
    t2 -= t1;

    // Проверки результатов
    if (res == nullptr) {
        std::cerr << "Error: Calculation failed due to invalid input." << std::endl;
        for (int i = 0; i < n; ++i) {
            delete[] m1[i];
            delete[] m2[i];
            delete[] result[i];
            delete[] expected[i];
        }
        delete[] m1;
        delete[] m2;
        delete[] result;
        delete[] expected;
        return 1;
    }

    // Проверка на переполнение (для всех случаев кроме data_method == 4)
    if (data_method != 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (result[i][j] > DBL_MAX || result[i][j] < -DBL_MAX) {
                    std::cerr << "Error: Result overflow detected at [" << i << "][" << j
                        << "] (result = " << result[i][j] << ")" << std::endl;
                    for (int i = 0; i < n; ++i) {
                        delete[] m1[i];
                        delete[] m2[i];
                        delete[] result[i];
                        delete[] expected[i];
                    }
                    delete[] m1;
                    delete[] m2;
                    delete[] result;
                    delete[] expected;
                    return 1;
                }
            }
        }
    }

    // Проверка корректности результата (для методов 1 и 3)
    if (data_method != 2 && data_method != 4) {
        if (!almostEqual(n, result, expected)) {
            std::cout << "Test case failed!" << std::endl;
            std::cout << "Expected: " << std::endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << expected[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "Actual: " << std::endl;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << result[i][j] << " ";
                }
                std::cout << std::endl;
            }
            for (int i = 0; i < n; ++i) {
                delete[] m1[i];
                delete[] m2[i];
                delete[] result[i];
                delete[] expected[i];
            }
            delete[] m1;
            delete[] m2;
            delete[] result;
            delete[] expected;
            return 1;
        }
    }

    std::cout << t2 << std::endl;

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        delete[] m1[i];
        delete[] m2[i];
        delete[] result[i];
        delete[] expected[i];
    }
    delete[] m1;
    delete[] m2;
    delete[] result;
    delete[] expected;

    return 0;
}