#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <omp.h>
#include <cfenv> // ��� ������ � ������� ����������
#include <cmath> // ��� std::fabs

extern "C" {
    double* mxv(int n, double* matrix, double* vector, double* result) {
        if (n < 1 || matrix == nullptr || vector == nullptr || result == nullptr) return nullptr;

        // ������� ������ ���������� ����� ������������
        std::feclearexcept(FE_ALL_EXCEPT);

        for (int i = 0; i < n; ++i) {
            result[i] = 0;
            for (int j = 0; j < n; ++j) {
                result[i] += matrix[i * n + j] * vector[j];

                // �������� �� ������������ ����� ������� ��������� � ��������
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
    int flag = std::stoi(argv[2]);
    double* matrix = new double[n * n];
    double* vector = new double[n];
    double* result = new double[n];
    double* expected = new double[n];

    if (flag == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i * n + j] = 0.0;
            }
        }
        for (int k = 0; k < n; k++) {
            vector[k] = 0.0;
            expected[k] = 0.0;
        }
    }
    else if (flag == 2) {
        std::random_device rd;  // �������� ��������� �����
        std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)
        std::uniform_real_distribution<> dis(0.0, 1.0); // ����������� ������������� �� 0 �� 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i * n + j] = dis(gen);
            }
        }
        for (int k = 0; k < n; k++) {
            vector[k] = dis(gen);
            result[k] = 0.0;
        }
    }
    else if (flag == 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i * n + j] = 2.0;
            }
        }
        for (int k = 0; k < n; k++) {
            vector[k] = 2.0;
            expected[k] = 4.0 * n;
        }
    }
    else {
        std::cerr << "The data filling flag is incorrect." << std::endl;
        return 1;
    }

    double t1 = omp_get_wtime();

    result = mxv(n, matrix, vector, result);

    double t2 = omp_get_wtime();
    t2 -= t1;

    // �������� �� ������ � ������� mxv
    if (result == nullptr) {
        std::cerr << "Error: Calculation failed due to floating-point exception." << std::endl;
        delete[] matrix;
        delete[] vector;
        delete[] result;
        delete[] expected;
        return 1;
    }

    // �������� ������������ ���������� (��� ������� 1 � 3)
    if (flag != 2) {
        if (!almostEqual(n, result, expected)) {
            std::cout << "Test case " << n << " " << flag << " failed! Expected: ";
            for (int j = 0; j < n; j++) {
                std::cout << expected[j] << " ";
            }
            std::cout << ", but got: ";
            for (int j = 0; j < n; j++) {
                std::cout << result[j] << " ";
            }
            std::cout << std::endl;
            std::cerr << "Error: result is incorrect" << std::endl;
            delete[] matrix;
            delete[] vector;
            delete[] result;
            delete[] expected;
            return 1;
        }
    }

    std::cout << t2 << std::endl;
    delete[] matrix;
    delete[] vector;
    delete[] result;
    delete[] expected;
    return 0;
}