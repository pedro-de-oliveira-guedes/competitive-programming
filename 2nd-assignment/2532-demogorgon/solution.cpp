#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

std::vector<int> spell_damage;
std::vector<int> spell_mana;
std::vector<std::vector<int>> dp;

int get_minimum_mana(int demogorgon_health, int current_spell) {
    // If Demogorgon is defeated with the last spell, the current spell is not needed
    if (demogorgon_health <= 0) return 0;
    // If all spells are used and Demogorgon is not defeated, the task is impossible
    if (current_spell >= spell_damage.size()) return INF;
    // Avoiding recomputation of the same state
    if (dp[demogorgon_health][current_spell] != -1) return dp[demogorgon_health][current_spell];

    int required_mana_without_spell = get_minimum_mana(demogorgon_health, current_spell + 1);
    int required_mana_with_spell = get_minimum_mana(demogorgon_health - spell_damage[current_spell], current_spell + 1) + spell_mana[current_spell];

    dp[demogorgon_health][current_spell] = std::min(required_mana_without_spell, required_mana_with_spell);
    return dp[demogorgon_health][current_spell];
}

int main() {
    int num_spells, demogorgon_health;

    while (std::cin >> num_spells >> demogorgon_health) {
        spell_damage.clear();
        spell_damage.resize(num_spells);
        spell_mana.clear();
        spell_mana.resize(num_spells);

        for (int i = 0; i < num_spells; i++) std::cin >> spell_damage[i] >> spell_mana[i];

        dp.clear();
        dp.resize(demogorgon_health + 1, std::vector<int>(num_spells + 1, -1));

        int min_mana = get_minimum_mana(demogorgon_health, 0);
        if (min_mana >= INF) {
            std::cout << "-1" << std::endl;
        } else {
            std::cout << min_mana << std::endl;
        }
    }

    return 0;
}
