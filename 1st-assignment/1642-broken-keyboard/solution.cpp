#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

int get_subsequence_size(const std::unordered_map<char, std::vector<int>> &subsequence) {
    int size = 0;
    for (const auto &p : subsequence) size += p.second.size();
    return size;
}

std::pair<char, int> get_removed_char(const std::unordered_map<char, std::vector<int>> &subsequence) {
    char key;
    int last_pos = INF;
    for (const auto &p : subsequence) {
        if (p.second.at(p.second.size() - 1) < last_pos) {
            last_pos = p.second.at(p.second.size() - 1);
            key = p.first;
        }
    }
    return {key, last_pos};
}

void resize_arrays(
    std::vector<int> *subsequence,
    int index
) {
    int start = 0, end = subsequence->size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (subsequence->at(mid) < index) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    subsequence->erase(subsequence->begin(), subsequence->begin() + start);
}

int main() {
    int remaining_keys, max_subsequence = 0;

    std::string line;
    std::getline(std::cin, line);
    remaining_keys = std::stoi(line);

    while (remaining_keys > 0) {
        std::unordered_map<char, std::vector<int>> subsequence;

        std::getline(std::cin, line);
        for (int i = 0; i < line.size(); i++) { // O(n)
            if (subsequence.find(line[i]) != subsequence.end()) {
                subsequence[line[i]].emplace_back(i);
            }
            else {
                if (subsequence.size() + 1 <= remaining_keys) {
                    subsequence.emplace(line[i], std::vector<int>{i});
                } else {
                    auto removed_char = get_removed_char(subsequence); // O(m)
                    subsequence.erase(removed_char.first);
                    for (auto &p : subsequence) resize_arrays(&p.second, removed_char.second); // O(log m)

                    subsequence.emplace(line[i], std::vector<int>{i});
                }
            }
            max_subsequence = std::max(max_subsequence, get_subsequence_size(subsequence)); // O(m)
        }

        std::cout << max_subsequence << std::endl;
        
        std::getline(std::cin, line);
        remaining_keys = std::stoi(line);
        max_subsequence = 0;
    }

    return 0;
}
