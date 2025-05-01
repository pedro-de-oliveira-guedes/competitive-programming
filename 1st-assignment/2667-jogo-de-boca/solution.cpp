#include <bits/stdc++.h>

int main() {
    std::string number;
    std::cin >> number;

    int sum = 0;
    for (auto const &n : number) sum += ((char) n - '0');

    std::cout << sum % 3 << std::endl;

    return 0;
}
