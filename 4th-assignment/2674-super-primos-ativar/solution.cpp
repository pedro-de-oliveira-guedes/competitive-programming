#include <bits/stdc++.h>

#define MAX_PRIMES_RANGE 1000000

std::vector<bool> get_all_primes() { // Crivo de Eratóstenes
    std::vector<bool> is_prime(MAX_PRIMES_RANGE + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= MAX_PRIMES_RANGE; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_PRIMES_RANGE; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return is_prime;
}

bool all_digits_are_primes(int number) {
    if (number == 0) return false;

    int temp = number;
    while (temp > 0) {
        int digit = temp % 10;

        if (digit != 2 && digit != 3 && digit != 5 && digit != 7) {
            return false;
        }

        temp /= 10;
    }

    return true;
}

int main() {
    std::vector<bool> all_primes = get_all_primes();

    int number;
    while (std::cin >> number) {
        if (all_primes[number]) {
            if (all_digits_are_primes(number)) {
                std::cout << "Super" << std::endl;
            } else {
                std::cout << "Primo" << std::endl;
            }
        } else {
            std::cout << "Nada" << std::endl;
        }
    }

    return 0;
}
