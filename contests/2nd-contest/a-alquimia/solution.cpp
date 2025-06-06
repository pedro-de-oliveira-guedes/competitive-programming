#include <bits/stdc++.h>

int main() {
    unsigned long long yellow_crystals, blue_crystals;
    std::cin >> yellow_crystals >> blue_crystals;

    unsigned long long yellow_balls, green_balls, blue_balls;
    std::cin >> yellow_balls >> green_balls >> blue_balls;

    unsigned long long yellow_crystals_needed = 2*yellow_balls + green_balls;
    unsigned long long blue_crystals_needed = 3*blue_balls + green_balls;

    unsigned long long total_crystals_needed = 0;

    if (yellow_crystals_needed > yellow_crystals) {
        total_crystals_needed += yellow_crystals_needed - yellow_crystals;
    }
    if (blue_crystals_needed > blue_crystals) {
        total_crystals_needed += blue_crystals_needed - blue_crystals;
    }

    std::cout << total_crystals_needed << std::endl;

    return 0;
}
