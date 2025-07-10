#include <bits/stdc++.h>

long long multiplicative_inverse(long long a, long long b) {
    long long b0 = b;
    long long y = 0, x = 1;

    if (b == 1) return 0;

    while (a > 1) {
        long long quotient = a / b;
        long long temp = b;

        b = a % b;
        a = temp;
        temp = y;

        y = x - quotient * y;
        x = temp;
    }

    if (x < 0) x += b0;

    return x;
}

long long modular_exponentiation(long long base, long long exponent, long long mod) {
    long long result = 1;
    base %= mod;

    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % mod;

        exponent /= 2;
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    long long secret_encryption_number, encryption_key, encrypted_message;
    std::cin >> secret_encryption_number >> encryption_key >> encrypted_message;

    long long first_prime = 0, second_prime = 0;
    long long limit = std::sqrt(secret_encryption_number);

    for (long long i = 3; i <= limit; i += 2) { // Os primos são necessariamente ímpares, portanto começamos de 3
        if (secret_encryption_number % i == 0) {
            first_prime = i;
            second_prime = secret_encryption_number / i;
            break;
        }
    }

    long long totient = (first_prime - 1) * (second_prime - 1);
    long long decryption_key = multiplicative_inverse(encryption_key, totient);

    long long decrypted_message = modular_exponentiation(encrypted_message, decryption_key, secret_encryption_number);
    std::cout << decrypted_message << std::endl;

    return 0;
}