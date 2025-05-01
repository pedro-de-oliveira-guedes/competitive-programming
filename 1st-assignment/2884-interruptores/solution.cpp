#include <bits/stdc++.h>

bool all_turned_off(const std::vector<bool> &lamps_state) {
    for (const auto &lamp : lamps_state) {
        if (lamp) return false;
    }
    return true;
}

bool lamps_reseted(const std::vector<bool> &lamps_state, const std::vector<bool> &initial_state) {
    for (int i = 0; i < lamps_state.size(); i++) {
        if (lamps_state[i] != initial_state[i]) return false;
    }
    return true;
}

int main () {
    int switches, lamps;
    std::cin >> switches >> lamps;

    std::vector<bool> lamps_state(lamps, false), initial_state(lamps, false);
    std::vector<std::vector<int>> switches_connections(switches);

    int turned_on_lamps;
    std::cin >> turned_on_lamps;
    while (turned_on_lamps--) {
        int lamp;
        std::cin >> lamp;
        lamps_state[lamp-1] = true;
        initial_state[lamp-1] = true;
    }

    for (int i = 0; i < switches; i++) {
        int connections;
        std::cin >> connections;
        while (connections--) {
            int lamp;
            std::cin >> lamp;
            switches_connections[i].emplace_back(lamp-1);
        }
    }

    int janitor_try = 0;
    while (!all_turned_off(lamps_state)) {
        for (const auto &lamp : switches_connections[janitor_try % switches])
            lamps_state[lamp] = !lamps_state[lamp];
        janitor_try++;

        if (janitor_try % lamps == 0 && lamps_reseted(lamps_state, initial_state)) break;
    }

    if (all_turned_off(lamps_state))
        std::cout << janitor_try << std::endl;
    else
        std::cout << "-1" << std::endl;

    return 0;
}
