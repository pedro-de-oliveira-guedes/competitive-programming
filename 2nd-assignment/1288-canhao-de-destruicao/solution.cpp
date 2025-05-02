#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

// Backpack problem
int get_max_damage(const std::vector<pii> &projectiles, int max_weight) {
    std::vector<std::vector<int>> cannon(projectiles.size() + 1, std::vector<int>(max_weight + 1, 0));
    for (size_t i = 1; i <= projectiles.size(); ++i) {
        for (int j = 0; j <= max_weight; ++j) {
            cannon[i][j] = cannon[i - 1][j];
            if (j >= projectiles[i - 1].second) {
                cannon[i][j] = std::max(cannon[i][j], cannon[i - 1][j - projectiles[i - 1].second] + projectiles[i - 1].first);
            }
        }
    }
    return cannon[projectiles.size()][max_weight];
}

int main() {
    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        int projectiles_count;
        std::cin >> projectiles_count;

        std::vector<pii> projectiles;
        while (projectiles_count--) {
            int power, weight;
            std::cin >> power >> weight;
            projectiles.emplace_back(power, weight);
        }
        std::sort(projectiles.begin(), projectiles.end(), std::greater<pii>());

        int max_weight, castle_resistance;
        std::cin >> max_weight >> castle_resistance;

        int max_damage = get_max_damage(projectiles, max_weight);
        if (max_damage >= castle_resistance) {
            std::cout << "Missao completada com sucesso\n";
        } else {
            std::cout << "Falha na missao\n";
        }
    }

    return 0;
}
