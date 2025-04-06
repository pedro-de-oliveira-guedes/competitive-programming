#include <bits/stdc++.h>

int main() {
    std::unordered_set<std::string> dijkstra_jewelry;
    std::string jewelry;

    while (std::cin >> jewelry) {
        dijkstra_jewelry.insert(jewelry);
    }

    std::cout << dijkstra_jewelry.size() << std::endl;
    
    return 0;
}
