#include <bits/stdc++.h>

#define MODULO 1000000
#define MICROBUS_LENGTH 5
#define BUS_LENGTH 10

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
    long long queue_length, microbus_colors, bus_colors;

    while (std::cin >> queue_length >> microbus_colors >> bus_colors) {
        if (queue_length < MICROBUS_LENGTH) {
            std::cout << std::setw(6) << std::setfill('0') << 1 << std::endl;
            continue;
        }
        else if (queue_length == MICROBUS_LENGTH) {
            std::cout << std::setw(6) << std::setfill('0') << microbus_colors % MODULO << std::endl;
            continue;
        }

        long long length_units = queue_length / MICROBUS_LENGTH;

        Matrix transition_matrix = {
            {microbus_colors % MODULO, bus_colors % MODULO},
            {1, 0}
        };
        Matrix result_matrix = matrix_power(transition_matrix, length_units - 1);

        long long base_case_0 = 1; // queue_length < MICROBUS_LENGTH -> 1 way to fill the queue (no buses)
        long long base_case_1 = microbus_colors % MODULO; // queue_length == MICROBUS_LENGTH -> microbus_colors ways to fill the queue

        long long total_ways = (result_matrix[0][0] * base_case_1 + result_matrix[0][1] * base_case_0) % MODULO;
        std::cout << std::setw(6) << std::setfill('0') << total_ways << std::endl;
    }

    return 0;
}
