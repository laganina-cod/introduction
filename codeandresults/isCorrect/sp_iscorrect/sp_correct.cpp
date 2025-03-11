#include <iostream>
#include <cmath>
#include <limits>

bool almostEqual(double a, double b, double epsilon = 1e-6) {
    return std::fabs(a - b) < epsilon;
}

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

int main() {
    // Инициализация тестовых данных
    double a1[] = { 1.5, 2.3, 3.7, 4.1 };
    double b1[] = { 0.5, 1.2, 2.4, 3.0 };
    double c1 =24.69;

    double a2[] = { 0.0, 0.0, 0.0, 0.0 };
    double b2[] = { 1.2, 2.5, 3.8, 4.0 };
    double c2 = 0.0;

    double a3[] = { -1.2, -2.5, -3.8, -4.0 };
    double b3[] = { 1.2, 2.5, 3.8, 4.0 };
    double c3 =-38.13;

    double a4[] = { 10.5, 20.3, 30.1, 40.7 };
    double b4[] = { 0.1, 0.2, 0.3, 0.4 };
    double c4 =30.42;

    double a5[] = { 1.0, 0.0, 0.0, 0.0 };
    double b5[] = { 0.0, 1.0, 0.0, 0.0 };
    double c5 = 0.0;

    double a6[] = { 2.2, 3.3, 4.4, 5.5 };
    double b6[] = { 1.1, 2.2, 3.3, 4.4 };
    double c6 =48.4;

    double a7[] = { 1.0, 1.0, 1.0 };
    double b7[] = { 1.0, 1.0, 1.0 };
    double c7 =3.0;

    double a8[] = { 1.0 };
    double b8[] = { 1.0 };
    double c8 =1.0;

    double a9[] = { 1.5, 2.3 };
    double b9[] = { 1.0, 1.0 };
    double c9 =3.8;

    double a10[] = { 1.5, 2.3, 3.7 };
    double b10[] = { 1.0, 1.0, 1.0 };
    double c10 =7.5;
    
    int n_1 = 100;
    double* a11 = new double[n_1];
    double* b11 = new double[n_1];
    for (int i = 0; i < n_1; i++) {
        a11[i] = b11[i] = 2.0;

    }
    double c11 = 4.0 * n_1;

    struct TestCase {
        int n; // Размерность векторов
        double* a; // Первый вектор
        double* b; // Второй вектор
        double expected; // Ожидаемый результат
    };

    // Массив тестовых случаев
    TestCase testCases[] = {
        {4, a1, b1, c1},
        {4, a2, b2, c2},
        {4, a3, b3, c3},
        {4, a4, b4, c4},
        {4, a5, b5, c5},
        {4, a6, b6, c6},
        {3, a7, b7, c7},
        {1, a8, b8, c8},
        {2, a9, b9, c9},
        {3, a10, b10, c10},
        {n_1,a11,b11,c11}
    };

    // Проверка всех тестовых случаев
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        double result = sp(testCases[i].n, testCases[i].a, testCases[i].b);
        if (!almostEqual(result, testCases[i].expected)) {
            std::cout << "Test case " << i + 1 << " failed! Expected: " << testCases[i].expected
                << ", but got: " << result << std::endl;
        }
        else {
            std::cout << "Test case " << i + 1 << " passed!" << std::endl;
        }
    }
    delete[] a11;
    delete[] b11;
    return 0;
}