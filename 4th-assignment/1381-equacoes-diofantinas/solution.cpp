#include <bits/stdc++.h>

#define MODULO 1300031
#define MAX_FACTORIAL 2000001

std::vector<long long> factorials(MAX_FACTORIAL, 1);

long long modular_exponentiation(long long base, long long exponent) {
    long long result = 1;
    base %= MODULO;

    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % MODULO;

        exponent /= 2;
        base = (base * base) % MODULO;
    }

    return result;
}

long long modular_inverse(long long number) { // Pequeno Teorema de Fermat
    return modular_exponentiation(number, MODULO - 2);
}

long long combinatorial(int n, int k) {
    if (k > n || k < 0) return 0;
    if (k == 0 || k == n) return 1;
    if (factorials[k] == 0 || factorials[n - k] == 0) return 0;

    long long numerator = factorials[n];
    long long inverse_denominator = (modular_inverse(factorials[k]) * modular_inverse(factorials[n - k])) % MODULO;

    return (numerator * inverse_denominator) % MODULO;
}

int main() {
    int test_cases;
    std::cin >> test_cases;

    for (int i = 1; i < MAX_FACTORIAL; i++) {
        factorials[i] = (factorials[i - 1] * i) % MODULO;
    }

    while (test_cases--) {
        int variables, result;
        std::cin >> variables >> result;

        long long solutions = combinatorial(variables + result - 1, result);
        std::cout << solutions << std::endl;
    }

    return 0;
}
