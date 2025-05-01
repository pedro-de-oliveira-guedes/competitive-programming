#include <bits/stdc++.h>

class ProblemInfo {
    public:
        std::vector<int> woods_lengths;
        std::map<int, int> accumulated_woods;
        int woods_width;
        int ballroom_width;
        int ballroom_height;

    ProblemInfo(
        std::vector<int> woods_lengths,
        int woods_width,
        int ballroom_width,
        int ballroom_height
    ) {
        std::sort(woods_lengths.begin(), woods_lengths.end(), std::greater<int>());
        this->woods_lengths = woods_lengths;

        std::map<int, int> acc_w;
        for (const int& wood_length : woods_lengths) {
            if (acc_w.find(wood_length) != acc_w.end()) acc_w[wood_length] += 1;
            else acc_w[wood_length] = 1;
        }
        this->accumulated_woods = acc_w;

        this->woods_width = woods_width;
        this->ballroom_width = ballroom_width;
        this->ballroom_height = ballroom_height;
    }
};

int place_woods(ProblemInfo pi, int ballroom_slots_dim, int ballroom_space_dim) {
    if ((ballroom_slots_dim * 100) % pi.woods_width) return 0;

    int woods_amount = 0;
    int remaining_slots = (ballroom_slots_dim * 100) / pi.woods_width;

    for (const int& wood_length : pi.woods_lengths) {
        int remaining_space = ballroom_space_dim - wood_length;
        if (remaining_space == 0) {
            woods_amount += 1;
            pi.accumulated_woods[wood_length] -= 1;
        }
        else if (remaining_space > 0) {
            pi.accumulated_woods[wood_length] -= 1;
            if (
                pi.accumulated_woods.find(remaining_space) != pi.accumulated_woods.end() &&
                pi.accumulated_woods[remaining_space]
            ) {
                woods_amount += 2;
                pi.accumulated_woods[remaining_space] -= 1;
            }
            else {
                pi.accumulated_woods[wood_length] += 1;
                continue;
            }
        }
        else continue;

        remaining_slots--;
        if (!remaining_slots) return woods_amount;
    }

    return 0;
}

int determine_feasibility(ProblemInfo pi) {
    int vertical_placement = place_woods(pi, pi.ballroom_width, pi.ballroom_height);
    int horizontal_placement = place_woods(pi, pi.ballroom_height, pi.ballroom_width);

    if (vertical_placement == 0 && horizontal_placement == 0) return 0;
    else if (vertical_placement > horizontal_placement && horizontal_placement == 0) return vertical_placement;
    else if (horizontal_placement > vertical_placement && vertical_placement == 0) return horizontal_placement;
    else return std::min(vertical_placement, horizontal_placement);
}

int main() {
    std::vector<int> answers;

    int ballroom_width, ballroom_height;
    std::cin >> ballroom_width >> ballroom_height;

    while (ballroom_width > 0 && ballroom_height > 0) {
        int woods_width, woods_amount;
        std::cin >> woods_width >> woods_amount;

        std::vector<int> woods_lengths;
        while (woods_amount--) {
            int wood_length;
            std::cin >> wood_length;
            woods_lengths.push_back(wood_length);
        }
        
        ProblemInfo pi = ProblemInfo(woods_lengths, woods_width, ballroom_width, ballroom_height);
        answers.push_back(determine_feasibility(pi));

        std::cin >> ballroom_width >> ballroom_height;
    }

    for (const int& answer : answers) {
        if (answer == 0) std::cout << "impossivel" << std::endl;
        else std::cout << answer << std::endl;
    }

    return 0;
}
