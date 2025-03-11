#include <iostream>
#include <cmath>
#include <limits>

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



extern "C" {
    double* mxm_1d(int n, double* m1, double* m2, double* result) {
        if (n < 1 || m1 == nullptr || m2 == nullptr || result == nullptr) return nullptr;

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                result[i * n + k] = 0;
                for (int j = 0; j < n; j++) {
                    result[i * n + k] = result[i * n + k] + m1[i * n + j] * m2[j * n + k];
                }
            }
        }
        return result;
    }
}

int main() {
    double a1[9] = { 1.1, 2.2, 3.3, 5.5, 6.6, 7.7, 9.9, 10.1, 11.2 };
    double b1[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double expected1[9] = { 33.0, 39.6, 46.2, 85.8, 105.6, 125.4, 128.7, 159.9, 191.1 };

    double a2[4] = { 1.0, 0.0, 0.0, 1.0 };
    double b2[4] = { 5.0, 6.0, 7.0, 8.0 };
    double expected2[4] = { 5.0, 6.0, 7.0, 8.0 };

    double a3[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double b3[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
    double expected3[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    double a4[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double b4[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double expected4[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    double a5[9] = { 1.1, 2.2, 3.3, 5.5, 6.6, 7.7, 9.9, 10.1, 11.2 };
    double b5[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    double expected5[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    double a6[1] = { 1.0 };
    double b6[1] = { 1.0 };
    double expected6[1] = { 1.0 };

    double a7[9] = { 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0 };
    double b7[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    double expected7[9] = { 11, 13, 15, 8, 10, 12, 5, 7, 9 };

    double a8[16] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16 };
    double b8[16] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16 };
    double expected8[16] = { 103.752, 112.486, 123.893, 135.3, 234.124, 257.862, 287.837, 317.812, 335.5646, 372.0278, 417.4901, 462.9524, 454.3788, 503.7274, 565.3475, 626.9676 };

    int n_1 = 100;
    int n_2 = 200;

    double* a9 = new double[n_1 * n_1];
    double* b9 = new double[n_1 * n_1];
    double* expected9 = new double[n_1 * n_1];
    double* a10 = new double[n_2 * n_2];
    double* b10 = new double[n_2 * n_2];
    double* expected10 = new double[n_2 * n_2];
    for (int i = 0; i < n_1*n_1; i++) {
        a9[i] = 2.0;
        b9[i] = 2.0;
        expected9[i] = 4 * n_1;
    }

    for (int i = 0; i < n_2 * n_2; i++) {
        a10[i] = 2.0;
        b10[i] = 2.0;
        expected10[i] = 4 * n_2;
    }

    // Структура для тестовых случаев
    struct TestCase {
        int n; // Размерность матрицы
        double* a; // Первая матрица
        double* b; // Вторая матрица
        double* result;
        double* expected; // Ожидаемый результат
    };

    TestCase testCases[] = {
        {3, a1, b1,nullptr, expected1},
        {2, a2, b2,nullptr, expected2},
        {3, a3, b3,nullptr, expected3},
        {3, a4, b4,nullptr, expected4},
        {3, a5, b5,nullptr, expected5},
        {1, a6, b6,nullptr, expected6},
        {3, a7, b7,nullptr, expected7},
        {4, a8, b8,nullptr, expected8},
        {n_1,a9,b9,nullptr, expected9},
        {n_2,a10,b10,nullptr,expected10}
    };

    // Проверка всех тестовых случаев
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        testCases[i].result = new double[testCases[i].n * testCases[i].n];
        mxm_1d(testCases[i].n, testCases[i].a, testCases[i].b, testCases[i].result);

        if (!almostEqual(testCases[i].n, testCases[i].result, testCases[i].expected)) {
            std::cout << "Test case " << i + 1 << " failed! Expected: " << std::endl;
            for (int j = 0; j < testCases[i].n; j++) {
                for (int k = 0; k < testCases[i].n; k++) {
                    std::cout << testCases[i].expected[j * testCases[i].n + k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "But got: " << std::endl;
            for (int j = 0; j < testCases[i].n; j++) {
                for (int k = 0; k < testCases[i].n; k++) {
                    std::cout << testCases[i].result[j * testCases[i].n + k] << " ";
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Test case " << i + 1 << " passed!" << std::endl;
        }
        delete[] testCases[i].result;
        testCases[i].result = nullptr;
        
    }

    delete[] a9;
    delete[] b9;
    delete[] expected9;
     
    
    delete[] a10;
    delete[] b10;
    delete[] expected10;
    
    a9 = b9 = expected9 = a10 = b10 = expected10 = nullptr;

    return 0;
}