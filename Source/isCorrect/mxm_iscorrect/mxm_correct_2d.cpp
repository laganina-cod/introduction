#include <iostream>
#include <cmath>
#include <limits>

bool almostEqual(int n, double** a, double** b, double epsilon = 1e-6) {
    if (a == nullptr || b == nullptr) {
        return false;
    }

    if (n <= 0) {
        return true;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (std::fabs(a[i][j] - b[i][j]) >= epsilon) {
                return false;
            }
        }
    }
    return true;
}

extern "C" {
    double** mxm_2d(int n, double** m1, double** m2, double** result) {
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

int main() {
    // Тестовые данные
    double a1[3][3] = { {1.1, 2.2, 3.3}, {5.5, 6.6, 7.7}, {9.9, 10.1, 11.2} };
    double b1[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double expected1[3][3] = { {33.0, 39.6, 46.2}, {85.8, 105.6, 125.4}, {128.7, 159.9, 191.1} };

    double a2[2][2] = { {1.0, 0.0}, {0.0, 1.0} };
    double b2[2][2] = { {5.0, 6.0}, {7.0, 8.0} };
    double expected2[2][2] = { {5.0, 6.0}, {7.0, 8.0} };

    double a3[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double b3[3][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
    double expected3[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };

    double a4[3][3] = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };
    double b4[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double expected4[3][3] = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };

    double a5[3][3] = { {1.1, 2.2, 3.3}, {5.5, 6.6, 7.7}, {9.9, 10.1, 11.2} };
    double b5[3][3] = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };
    double expected5[3][3] = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };

    double a6[1][1] = { {1.0} };
    double b6[1][1] = { {1.0} };
    double expected6[1][1] = { {1.0} };

    double a7[3][3] = { {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0} };
    double b7[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double expected7[3][3] = { {11, 13, 15}, {8, 10, 12}, {5, 7, 9} };

    double a8[4][4] = { {1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}, {9.9, 10.1, 11.11, 12.12}, {13.13, 14.14, 15.15, 16.16} };
    double b8[4][4] = { {1.1, 2.2, 3.3, 4.4}, {5.5, 6.6, 7.7, 8.8}, {9.9, 10.1, 11.11, 12.12}, {13.13, 14.14, 15.15, 16.16} };
    double expected8[4][4] = { {103.752, 112.486, 123.893, 135.3}, {234.124, 257.862, 287.837, 317.812}, {335.5646, 372.0278, 417.4901, 462.9524}, {454.3788, 503.7274, 565.3475, 626.9676} };

    // Указатели на матрицы
    double* a1_m[] = { a1[0], a1[1], a1[2] };
    double* b1_m[] = { b1[0], b1[1], b1[2] };
    double* expected1_m[] = { expected1[0], expected1[1], expected1[2] };

    double* a2_m[] = { a2[0], a2[1] };
    double* b2_m[] = { b2[0], b2[1] };
    double* expected2_m[] = { expected2[0], expected2[1] };

    double* a3_m[] = { a3[0], a3[1], a3[2] };
    double* b3_m[] = { b3[0], b3[1], b3[2] };
    double* expected3_m[] = { expected3[0], expected3[1], expected3[2] };

    double* a4_m[] = { a4[0], a4[1], a4[2] };
    double* b4_m[] = { b4[0], b4[1], b4[2] };
    double* expected4_m[] = { expected4[0], expected4[1], expected4[2] };

    double* a5_m[] = { a5[0], a5[1], a5[2] };
    double* b5_m[] = { b5[0], b5[1], b5[2] };
    double* expected5_m[] = { expected5[0], expected5[1], expected5[2] };

    double* a6_m[] = { a6[0] };
    double* b6_m[] = { b6[0] };
    double* expected6_m[] = { expected6[0] };

    double* a7_m[] = { a7[0], a7[1], a7[2] };
    double* b7_m[] = { b7[0], b7[1], b7[2] };
    double* expected7_m[] = { expected7[0], expected7[1], expected7[2] };

    double* a8_m[] = { a8[0], a8[1], a8[2], a8[3] };
    double* b8_m[] = { b8[0], b8[1], b8[2], b8[3] };
    double* expected8_m[] = { expected8[0], expected8[1], expected8[2], expected8[3] };

    int n_1 = 100;
    int n_2 = 100;

    double** a9 = new double* [n_1];
    double** b9 = new double*[n_1];
    double** expected9 = new double*[n_1];
    for (int i = 0; i < n_1; i++) {
        a9[i] = new double[n_1];
        b9[i] = new double[n_1];
        expected9[i] = new double[n_1];
        for (int j = 0; j < n_1; j++) {
            a9[i][j] = 2.0;
            b9[i][j] = 2.0;
            expected9[i][j] = 4.0 * n_1;
        }
    }
    double** a10 = new double* [n_2];
    double** b10 = new double* [n_2];
    double** expected10 = new double*[n_2];
    for (int i = 0; i < n_2; i++) {
        a10[i] = new double[n_2];
        b10[i] = new double[n_2];
        expected10[i] = new double[n_2];
        for (int j = 0; j < n_2; j++) {
            a10[i][j] = 2.0;
            b10[i][j] = 2.0;
            expected10[i][j] = 4.0 * n_2;
        }
    }
    

    struct TestCase {
        int n; // Размерность векторов
        double** a; // Первый вектор
        double** b; // Второй вектор
        double** result;
        double** expected; // Ожидаемый результат
    };

    TestCase testCases[] = {
        {3, a1_m, b1_m, nullptr, expected1_m},
        {2, a2_m, b2_m, nullptr, expected2_m},
        {3, a3_m, b3_m, nullptr, expected3_m},
        {3, a4_m, b4_m, nullptr, expected4_m},
        {3, a5_m, b5_m, nullptr, expected5_m},
        {1, a6_m, b6_m, nullptr, expected6_m},
        {3, a7_m, b7_m, nullptr, expected7_m},
        {4, a8_m, b8_m, nullptr, expected8_m},
        {n_1,a9,b9,nullptr,expected9},
        {n_2,a10,b10,nullptr,expected10}
    };

    // Проверка всех тестовых случаев
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        testCases[i].result = new double* [testCases[i].n];
        for (int k = 0; k < testCases[i].n; k++) {
            testCases[i].result[k] = new double[testCases[i].n];
        }
        mxm_2d(testCases[i].n, testCases[i].a, testCases[i].b, testCases[i].result);
        if (!almostEqual(testCases[i].n, testCases[i].result, testCases[i].expected)) {
            std::cout << "Test case " << i + 1 << " failed! Expected: " << std::endl;
            for (int j = 0; j < testCases[i].n; j++) {
                for (int k = 0; k < testCases[i].n; k++) {
                    std::cout << testCases[i].expected[j][k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << ", but got: " << std::endl;
            for (int j = 0; j < testCases[i].n; j++) {
                for (int k = 0; k < testCases[i].n; k++) {
                    std::cout << testCases[i].result[j][k] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Test case " << i + 1 << " passed!" << std::endl;
        }
        for (int s = 0; s < testCases[i].n; s++) {
            delete[] testCases[i].result[s];
        }
        delete[] testCases[i].result;
        testCases[i].result = nullptr;
    }


    for (int i = 0; i < n_1; i++) {
        delete[] a9[i];
        delete[] b9[i];
        delete[] expected9[i];
    }
    delete[] a9;
    delete[] b9;
    delete[] expected9;

    for (int i = 0; i < n_2; i++) {
        delete[] a10[i];
        delete[] b10[i];
        delete[] expected10[i];
    }

    delete[] a10;
    delete[] b10;
    delete[] expected10;

    a10 = b10 = expected10 = a9 = b9 = expected9 = nullptr;

    return 0;
}