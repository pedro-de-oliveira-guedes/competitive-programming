#include <bits/stdc++.h>

const std::vector<std::string> braille_row1 = {".*", "*.", "*.", "**", "**", "*.", "**", "**", "*.", ".*"};
const std::vector<std::string> braille_row2 = {"**", "..", "*.", "..", ".*", ".*", "*.", "**", "**", "*."};
// Third row is always ".."

void convert_numbers(int digits) {
    std::string sequence;
    std::cin >> sequence;

    for (int i = 0; i < sequence.size()-1; i++) {
        char number = sequence[i];
        std::cout << braille_row1[number - '0'] << " ";
    }
    std::cout << braille_row1[sequence[sequence.size()-1] - '0'] << std::endl;

    for (int i = 0; i < sequence.size()-1; i++) {
        char number = sequence[i];
        std::cout << braille_row2[number - '0'] << " ";
    }
    std::cout << braille_row2[sequence[sequence.size()-1] - '0'] << std::endl;

    for (int i = 0; i < sequence.size()-1; i++) {
        std::cout << ".. ";
    }
    std::cout << ".." << std::endl;
}

void convert_braille(int digits) {
    std::vector<std::unordered_set<int>> possibilities(digits);
    std::string translation = "";

    for (int i = 0; i < digits; i++) {
        std::string braille_component;
        std::cin >> braille_component;

        for (int j = 0; j < braille_row1.size(); j++) {
            if (braille_component == braille_row1[j])
                possibilities[i].insert(j);
        }
    }

    for (int i = 0; i < digits; i++) {
        std::string braille_component;
        std::cin >> braille_component;

        for (int j = 0; j < braille_row2.size(); j++) {
            if (braille_component == braille_row2[j] &&
                possibilities[i].find(j) != possibilities[i].end()
            ) {
                translation += std::to_string(j);
                break;
            }
        }
    }

    for (int i = 0; i < digits; i++) {
        std::string trash;
        std::cin >> trash;
    }

    std::cout << translation << std::endl;
}

int main() {
    int digits;
    std::cin >> digits;

    while (digits > 0) {
        char read_mode;
        std::cin >> read_mode;

        if (read_mode == 'S') convert_numbers(digits);
        else convert_braille(digits);

        std::cin >> digits;
    }

    return 0;
}
