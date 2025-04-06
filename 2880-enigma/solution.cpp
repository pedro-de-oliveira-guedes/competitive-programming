#include <bits/stdc++.h>

bool possible_crib(const std::string &crypt, const std::string &crib, int pos) {
    int crib_pos = crib.size();
    while (pos-- && crib_pos--) {
        if (crypt[pos] == crib[crib_pos]) return false;
    }
    return true;
}

int main() {
    std::string encrypted_message, crib;
    std::cin >> encrypted_message >> crib;

    std::unordered_set<char> letters;
    for (const char &letter : crib) {
        letters.insert(letter);
    }

    int possibilities = 0, i;
    for (i = crib.size(); i < encrypted_message.size(); i++) {
        if (possible_crib(encrypted_message, crib, i)) possibilities++;
    }

    possibilities += possible_crib(encrypted_message, crib, i);

    std::cout << possibilities << std::endl;

    return 0;
}
