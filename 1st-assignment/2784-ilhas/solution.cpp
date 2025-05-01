#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

#define INF 0x3f3f3f3f

// Dijkstra
std::vector<int> calculate_network_overhead(const std::vector<std::vector<pii>> &network, int server_island) {
    std::vector<int> accumulated_pings(network.size(), INF);
    accumulated_pings[server_island] = 0;

    std::priority_queue<pii> next_islands;
    next_islands.push(pii(0, server_island));

    while(!next_islands.empty()) {
        int island = next_islands.top().second;
        next_islands.pop();

        for (int i = 0; i < network[island].size(); i++) {
            int neighboor = network[island][i].first;
            int ping = network[island][i].second;

            if (accumulated_pings[neighboor] > accumulated_pings[island] + ping) {
                accumulated_pings[neighboor] = accumulated_pings[island] + ping;
                next_islands.push(pii(accumulated_pings[neighboor], neighboor));
            }
        }
    }

    return accumulated_pings;
}

int main() {
    int islands, cables;
    std::cin >> islands >> cables;

    std::vector<std::vector<pii>> network(islands);
    while (cables--) {
        int source, destine, ping;
        std::cin >> source >> destine >> ping;

        network[source-1].emplace_back(pii(destine-1, ping));
        network[destine-1].emplace_back(pii(source-1, ping));
    }

    int server_island;
    std::cin >> server_island;

    auto network_overhead = calculate_network_overhead(network, server_island-1);

    int min_overhead = INF, max_overhead = -INF;
    for (int i = 0; i < network_overhead.size(); i ++) {
        if (i == server_island-1) continue;
        if (network_overhead[i] < min_overhead) min_overhead = network_overhead[i];
        if (network_overhead[i] > max_overhead) max_overhead = network_overhead[i];
    }

    std::cout << max_overhead - min_overhead << std::endl;

    return 0;
}
