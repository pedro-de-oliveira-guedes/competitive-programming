#include <bits/stdc++.h>

bool check_stripped_divisor(long long candidate_divisor) {
    bool prime_divisor = true;

    for (long long i = 2; i <= std::sqrt(candidate_divisor); i++) {
        if (candidate_divisor % (i*i) == 0) return false;
        if (candidate_divisor % i == 0) prime_divisor = false;
    }

    return !prime_divisor;
}

int main() {
    long long number;
    std::cin >> number;

    long long stripped_divisors = 0, number_sqrt = std::sqrt(number);
    for (long long candidate_divisor = 1; candidate_divisor < number_sqrt; candidate_divisor++) {
        if (number % candidate_divisor == 0) {
            stripped_divisors += check_stripped_divisor(candidate_divisor);
            stripped_divisors += check_stripped_divisor(number/candidate_divisor);
        }
    }

    if (number % number_sqrt == 0)
        stripped_divisors += check_stripped_divisor(std::sqrt(number));

    std::cout << stripped_divisors << std::endl;

    return 0;
}
