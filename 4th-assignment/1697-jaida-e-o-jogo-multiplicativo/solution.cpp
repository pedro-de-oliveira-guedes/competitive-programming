#include <bits/stdc++.h>

#define MAX_PRIMES_RANGE 20000000

std::vector<int> get_all_primes() { // Crivo de Eratóstenes
    std::vector<bool> is_prime(MAX_PRIMES_RANGE + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= MAX_PRIMES_RANGE; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_PRIMES_RANGE; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    std::vector<int> primes;
    for (int i = 2; i <= MAX_PRIMES_RANGE; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    std::vector<int> all_primes = get_all_primes();

    int test_cases;
    std::cin >> test_cases;
    while (test_cases--) {
        int numbers;
        std::cin >> numbers;

        std::unordered_set<int> list_numbers;
        while (numbers--) {
            int number;
            std::cin >> number;
            list_numbers.insert(number);
        }

        if (list_numbers.find(1) == list_numbers.end()) {
            std::cout << 0 << std::endl;
            continue;
        }

        for (const auto &prime : all_primes) {
            if (list_numbers.find(prime) == list_numbers.end()) {
                std::cout << prime - 1 << std::endl;
                break;
            }
        }
    }

    return 0;
}
