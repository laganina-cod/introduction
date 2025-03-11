#include <iostream>
#include <cmath>
#include <limits>

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
extern "C" {
	double* mxv_2d(int n, double** matrix, double* vector, double* result) {
		if (n < 1 || matrix == nullptr || vector == nullptr || result == nullptr) return nullptr;
		for (int i = 0; i < n; ++i) {
			result[i] = 0;
			for (int j = 0; j < n; ++j) {
				result[i] = result[i] + matrix[i][j] * vector[j];
			}
		}
		return result;
	}
}

int main() {
    // Тестовые данные
    double a1[3][3] = { {1.1, 2.2, 3.3}, {5.5, 6.6, 7.7}, {9.9, 10.1, 11.2} };
    double b1[] = { 1.0, 2.0, 3.0};
    double expected1[] = { 15.4,41.8,63.7 };

    double a2[2][2] = { {1.0, 0.0}, {0.0, 1.0} };
    double b2[] = { 5.0, 6.0 };
    double expected2[] = { 5.0, 6.0 };

    double a3[3][3] = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
    double b3[] = { 1.0, 0.0, 0.0 };
    double expected3[] = { 1.0, 4.0, 7.0 };

    double a4[3][3] = { {0.0,0.0,0.0},{0.0,0.0,0.0},{0.0,0.0,0.0} };
    double b4[]= { 1.0, 2.0, 3.0 };
    double expected4[] = { 0.0,0.0,0.0 };

    double a5[3][3] = { {1.1, 2.2, 3.3}, {5.5, 6.6, 7.7}, {9.9, 10.1, 11.2} };
    double b5[] = { 0.0,0.0,0.0 };
    double expected5[] = { 0.0,0.0,0.0 };

    double a6[1][1] = { {1.0} };
    double b6[] = { 1.0 };
    double expected6[] = { 1.0 };

    double a7[2][2] = { {1.1,2.2},{5.5,6.6} };
    double b7[] = { 1.0,2.0 };
    double expected7[] = { 5.5,18.7 };

    double a8[4][4] = { {1.1,2.2,3.3,4.4}, {5.5,6.6	,7.7,8.8} ,{9.9,10.1,11.11,12.12},{13.13,14.14,15.15,16.16} };
    double b8[] = { 1.0,2.0,3.0,4.0 };
    double expected8[] = {33.0,77.0,111.91,151.5};
    int n_1 = 100;
    int n_2 = 200;

    double** a9 = new double* [n_1];
    double* b9 = new double[n_1];
    double* expected9 = new double[n_1];
    for (int i = 0; i < n_1; i++) {
        a9[i] = new double[n_1];
        for (int j = 0; j < n_1; j++) {
            a9[i][j] = 2.0;
        }
        b9[i] = 2.0;
        expected9[i] = 4.0 * n_1;
    }

    double** a10 = new double* [n_2];
    double* b10 = new double[n_2];
    double* expected10 = new double[n_2];
    for (int i = 0; i < n_2; i++) {
        a10[i] = new double[n_2];
        for (int j = 0; j < n_2; j++) {
            a10[i][j] = 2.0;
        }
        b10[i] = 2.0;
        expected10[i] = 4.0 * n_2;
    }


    // Указатели на матрицы
    double* matrix1[] = { a1[0], a1[1], a1[2] };
    double* matrix2[] = { a2[0], a2[1] };
    double* matrix3[] = { a3[0], a3[1], a3[2] };
    double* matrix4[] = { a4[0], a4[1], a4[2] };
    double* matrix5[] = { a5[0], a5[1], a5[2] };
    double* matrix6[] = { a6[0] };
    double* matrix7[] = { a7[0], a7[1]};
    double* matrix8[] = { a8[0], a8[1], a8[2],a8[3]};


    struct TestCase {
        int n; // Размерность векторов
        double** matrix; // Первый вектор
        double* vector; // Второй вектор
        double* result;
        double* expected; // Ожидаемый результат
    };
    
    TestCase testCases[] = {
           {3, matrix1, b1,nullptr, expected1},
           {2, matrix2, b2,nullptr, expected2},
           {3, matrix3, b3,nullptr, expected3},
           {3, matrix4, b4,nullptr, expected4},
           {3, matrix5, b5,nullptr, expected5},
           {1, matrix6, b6,nullptr, expected6},
           {2, matrix7, b7,nullptr, expected7},
           {4, matrix8, b8,nullptr, expected8},
           {n_1,a9,b9,nullptr,expected9},
           {n_2,a10,b10,nullptr,expected10}
    };

    // Проверка всех тестовых случаев
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        testCases[i].result = new double[testCases[i].n];
        mxv_2d(testCases[i].n, testCases[i].matrix, testCases[i].vector, testCases[i].result);
        if (!almostEqual(testCases[i].n, testCases[i].result, testCases[i].expected)) {
            std::cout << "Test case " << i + 1 << " failed! Expected: ";
            for (int j = 0; j < testCases[i].n; j++) {
                std::cout << testCases[i].expected[j]<<" ";
            }
            std::cout << ", but got: ";
            for (int j = 0; j < testCases[i].n; j++) {
                std::cout << testCases[i].result[j] <<" ";
            }
            std::cout<<std::endl;
        }
        else {
            std::cout << "Test case " << i + 1 << " passed!" << std::endl;
        }
        delete[] testCases[i].result;
        testCases[i].result = nullptr;
    }

    for (int i = 0; i < n_1; i++) {
        delete[] a9[i];
    }
    delete[] a9;
    delete[] b9;
    delete[] expected9;

    for (int i = 0; i < n_2; i++) {
        delete[] a10[i];
    }
    delete[] a10;
    delete[] b10;
    delete[] expected10;
    a9 = a10 =nullptr;
    b9 = expected9 = b10 = expected10 = nullptr;


    return 0;
}