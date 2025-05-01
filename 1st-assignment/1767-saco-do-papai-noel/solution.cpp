#include <bits/stdc++.h>

typedef std::pair<int, int> pii;
#define MAX_BAG_weight 50

pii get_bag_total_packages_and_weight(std::vector<pii> packages, std::vector<std::vector<int>> santas_bag) {
    int total_weight = 0, total_packages = 0;
    int curr_package = packages.size(), curr_weight = MAX_BAG_weight;

    while (curr_package > 0 && curr_weight > 0) {
        if (santas_bag[curr_package][curr_weight] != santas_bag[curr_package-1][curr_weight]) {
            total_weight += packages[curr_package-1].second;
            curr_weight -= packages[curr_package-1].second;
            total_packages++;
        }
        curr_package--;
    }

    return {total_packages, total_weight};
}

std::pair<int, pii> build_bag(std::vector<pii> packages) {
    std::vector<std::vector<int>> santas_bag(packages.size()+1, std::vector<int>(MAX_BAG_weight+1));

    for (int i = 1; i <= packages.size(); i++) {
        for (int j = 1; j <= MAX_BAG_weight; j++) {
            if (packages[i-1].second <= j) {
                santas_bag[i][j] = std::max(
                    santas_bag[i-1][j], // Not including the current "i" package
                    santas_bag[i-1][j-packages[i-1].second] + packages[i-1].first // Including the current "i" package
                );
            } else {
                santas_bag[i][j] = santas_bag[i-1][j]; // Current package "i" does not fit into the bag
            }
        }
    }

    int max_toys_amount = santas_bag[packages.size()][MAX_BAG_weight];
    pii packages_and_weight = get_bag_total_packages_and_weight(packages, santas_bag);

    return {max_toys_amount, packages_and_weight};
}

int main() {
    int deliveries;
    std::cin >> deliveries;

    while(deliveries--) {
        int num_packages;
        std::cin >> num_packages;
        std::vector<pii> packages;

        while(num_packages--) {
            int toys, weight;
            std::cin >> toys >> weight;
            packages.emplace_back(pii{toys, weight});
        }

        auto bag_stats = build_bag(packages);

        std::cout << bag_stats.first << " brinquedos" << std::endl;
        std::cout << "Peso: " << bag_stats.second.second << " kg" << std::endl;
        std::cout << "sobra(m) " << std::to_string(packages.size() - bag_stats.second.first) << " pacote(s)" << std::endl << std::endl;
    }
}
