#include <bits/stdc++.h>

int main() {
    std::vector<float> values_available = {100.0, 50.0, 20.0, 10.0, 5.0, 2.0, 1.0, 0.5, 0.25, 0.10, 0.05, 0.01};
    std::vector<int> amount_of_each_value;

    float user_value;
    std::cin >> user_value;
    user_value += 0.001;

    for (const float& value : values_available) {
        int amount_of_value = (int) (user_value / value);
        amount_of_each_value.push_back(amount_of_value);

        user_value -= (amount_of_value * value);
    }

    std::cout << "NOTAS:" << std::endl;
    for (int i = 0; i < values_available.size(); i++) {
        if (i < 6) {
            std::cout << amount_of_each_value[i] << " nota(s) de R$ " << std::fixed << std::setprecision(2) << values_available[i] << std::endl;
        } else {
            if (i == 6) std::cout << "MOEDAS:" << std::endl;

            std::cout << amount_of_each_value[i] << " moeda(s) de R$ " << std::fixed << std::setprecision(2) << values_available[i] << std::endl;
        }
    }

    return 0;
}
