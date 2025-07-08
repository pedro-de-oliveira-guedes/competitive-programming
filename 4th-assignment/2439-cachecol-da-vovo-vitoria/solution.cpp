#include <bits/stdc++.h>

#define MODULO 1000000007

typedef std::vector<std::vector<long long>> Matrix;

Matrix mutiply_matrices(const Matrix &a, const Matrix &b) {
    Matrix result = {{0, 0}, {0, 0}};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MODULO;
            }
        }
    }

    return result;
}

Matrix matrix_power(Matrix &matrix, long long exponent) {
    Matrix result = {{1, 0}, {0, 1}}; // Identity matrix

    matrix[0][0] %= MODULO;
    matrix[0][1] %= MODULO;
    matrix[1][0] %= MODULO;
    matrix[1][1] %= MODULO;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = mutiply_matrices(result, matrix);
        }
        matrix = mutiply_matrices(matrix, matrix);
        exponent /= 2;
    }

    return result;
}

int main() {
    long long patchworks;
    std::cin >> patchworks;

    Matrix transformation_matrix = {{3, 2}, {2, 2}};
    Matrix result_matrix = matrix_power(transformation_matrix, patchworks - 1);

    long long same_edge_colors = (result_matrix[0][0] * 6 + result_matrix[0][1] * 6) % MODULO;
    long long different_edge_colors = (result_matrix[1][0] * 6 + result_matrix[1][1] * 6) % MODULO;

    long long total_scarfs = (same_edge_colors + different_edge_colors) % MODULO;
    std::cout << total_scarfs << std::endl;

    return 0;
}
