#include <bits/stdc++.h>

#define MAX_DIFF 5

std::vector<int> presents;

bool organize_presents() {
    std::vector<bool> last_present(MAX_DIFF * 2 + 1, false);
    last_present[MAX_DIFF] = true; // When no presents are placed, the difference is 0.

    std::vector<bool> current_present(MAX_DIFF * 2 + 1, false);

    for (int i = 0; i < presents.size(); i++) { // O(n)
        bool organizable = false;
        for (int diff = -MAX_DIFF; diff <= MAX_DIFF; diff++) { // O(1)
            if (last_present[diff + MAX_DIFF] == false) continue; // Ignore impossible differences.

            int place_right = diff + presents[i];
            if (std::abs(place_right) <= MAX_DIFF) {
                current_present[place_right + MAX_DIFF] = true;
                organizable = true;
            }

            int place_left = diff - presents[i];
            if (std::abs(place_left) <= MAX_DIFF) {
                current_present[place_left + MAX_DIFF] = true;
                organizable = true;
            }
        }
        if (!organizable) return false;

        last_present = current_present;
        current_present.assign(MAX_DIFF * 2 + 1, false);
    }

    return true;
}

int main() {
    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        int total_presents;
        std::cin >> total_presents;

        presents.clear();
        presents.resize(total_presents);
        for (int i = 0; i < total_presents; i++) std::cin >> presents[i];

        if (organize_presents()) {
            std::cout << "Feliz Natal!" << std::endl;
        } else {
            std::cout << "Ho Ho Ho!" << std::endl;
        }
    }

    return 0;
}
