#include <bits/stdc++.h>

bool is_valid_solution(int max_time, int competitors, int popcorns_per_second, std::vector<int>& popcorn_bags) {
    int popcorns_eaten = 0, required_competitors = 0;

    for (int popcorn_amount : popcorn_bags) {
        if (std::ceil((double)popcorn_amount / popcorns_per_second) > max_time || required_competitors == competitors) {
            required_competitors = competitors + 1; // Makes the current time invalid
            return false;
        }

        if (std::ceil((double)(popcorns_eaten + popcorn_amount) / popcorns_per_second) <= max_time) {
            popcorns_eaten += popcorn_amount; // Increases the amount of popcorn eaten by the current competitor
        } else { // Add a new competitor to the contest and initialize the amount of popcorn eaten by him
            required_competitors++;
            popcorns_eaten = popcorn_amount;

            if (required_competitors >= competitors) return false;
        }
    }

    return true;
}

int main() {
    int min_time;
    int popcorn, competitors, popcorns_per_second;
    std::cin >> popcorn >> competitors >> popcorns_per_second;

    std::vector<int> popcorn_bags(popcorn);
    int all_popcorns = 0;
    for (int i = 0; i < popcorn; ++i) {
        std::cin >> popcorn_bags[i];
        all_popcorns += popcorn_bags[i];
    }

    int lower_bound = 0;
    int upper_bound = std::ceil((double)all_popcorns / popcorns_per_second); // Maximum time to eat all popcorns
    while (lower_bound <= upper_bound) {
        int current_time = lower_bound + (upper_bound - lower_bound) / 2;
        if (is_valid_solution(current_time, competitors, popcorns_per_second, popcorn_bags)) {
            min_time = current_time;
            upper_bound = current_time - 1;
        } else {
            lower_bound = current_time + 1;
        }
    }

    std::cout << min_time << std::endl;

    return 0;
}
