#include <bits/stdc++.h>

bool matching_strips(const std::vector<int> &bent_strip, const std::vector<int> &expected_strip) {
    for (int i = 0; i < bent_strip.size(); i++)
        if (bent_strip[i] != expected_strip[i]) return false;
    return true;
}

std::vector<int> bend_strip(std::vector<int> strip, int pos) {
    std::vector<int> bent_strip{};

    for (int i = strip.size()-1; i >= pos*2; i--)
        bent_strip.emplace_back(strip[i]);

    for (int i = 0; i < pos; i++) {
        if (2*pos-1-i < strip.size()) {
            bent_strip.emplace_back(strip[i] + strip[2*pos-1-i]);
        } else {
            bent_strip.emplace_back(strip[i]);
        }
    }

    return bent_strip;
}

bool should_be_pruned(
    const std::vector<int> &input_strip,
    const std::vector<int> &expected_strip,
    std::set<std::vector<int>> *cache
) {
    if (input_strip.size() < expected_strip.size()) return true;
    if (*std::min_element(expected_strip.begin(), expected_strip.end()) < *std::min_element(input_strip.begin(), input_strip.end())) return true;
    if (cache->find(input_strip) != cache->end()) return true;
    return false;
}

bool bending_machine(
    const std::vector<int> &input_strip,
    const std::vector<int> &expected_strip,
    std::set<std::vector<int>> *cache,
    bool inverted_last_time
) {
    if (input_strip.size() == expected_strip.size() && matching_strips(input_strip, expected_strip)) {
        return true;
    }
    else if (should_be_pruned(input_strip, expected_strip, cache)) {
        return false;
    }
    cache->insert(input_strip);

    if (!inverted_last_time) {
        std::vector<int> inverted_strip{};
        for (int i = input_strip.size()-1; i >= 0; i--) inverted_strip.emplace_back(input_strip[i]);
        if (bending_machine(inverted_strip, expected_strip, cache, true)) return true;
    }

    for (int i = 1; i < input_strip.size(); i++) {
        std::vector<int> bent_strip = bend_strip(input_strip, i);
        if (bending_machine(bent_strip, expected_strip, cache, false)) return true;
    }

    return false;
}

int main() {
    int input_strip_size;
    while (std::cin >> input_strip_size) {
        std::vector<int> input_strip{};
        while (input_strip_size--) {
            int value;
            std::cin >> value;
            input_strip.emplace_back(value);
        }

        int output_strip_size;
        std::cin >> output_strip_size;
        std::vector<int> output_strip{};
        while(output_strip_size--) {
            int value;
            std::cin >> value;
            output_strip.emplace_back(value);
        }

        std::set<std::vector<int>> cache;
        if (bending_machine(input_strip, output_strip, &cache, false)) std::cout << "S" << std::endl;
        else std::cout << "N" << std::endl;
    }

    return 0;
}
