#include <bits/stdc++.h>

#define MAX_UPPER_BOUND 2000000
#define MAX_DIVISORS 300

std::vector<int> get_divisors_amount() {
    std::vector<int> divisors_amount(MAX_UPPER_BOUND + 1, 0);

    for (int i = 1; i <= MAX_UPPER_BOUND; i++) {
        for (int j = i; j <= MAX_UPPER_BOUND; j += i) {
            divisors_amount[j]++;
        }
    }

    return divisors_amount;
}

std::vector<bool> get_primes() { // Crivo de Eratóstenes
    std::vector<bool> is_prime(MAX_DIVISORS + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i*i <= MAX_DIVISORS; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_DIVISORS; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return is_prime;
}

std::vector<int> get_hyperprimes() {
    std::vector<int> hyperprimes_count(MAX_UPPER_BOUND + 1, 0);
    hyperprimes_count[0] = hyperprimes_count[1] = 0;

    std::vector<int> divisors_amount = get_divisors_amount();
    std::vector<bool> is_prime = get_primes();

    for (int i = 2; i <= MAX_UPPER_BOUND; i++) {
        hyperprimes_count[i] = hyperprimes_count[i - 1];

        if (is_prime[divisors_amount[i]]) {
            hyperprimes_count[i]++;
        }
    }

    return hyperprimes_count;
}

int main() {
    std::vector<int> hyperprimes_divisors = get_hyperprimes();

    int upper_bound;
    while (std::cin >> upper_bound) {
        std::cout << hyperprimes_divisors[upper_bound] << std::endl;
    }

    return 0;
}
