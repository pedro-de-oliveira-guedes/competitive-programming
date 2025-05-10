#include <bits/stdc++.h>

int main() {
    int questions, skips;

    while (std::cin >> questions >> skips) {
        std::vector<int> prizes(questions + 1);
        for (int i = 1; i <= questions; i++) std::cin >> prizes[i];

        std::vector<int> chances(questions + 1);
        for (int i = 1; i <= questions; i++) std::cin >> chances[i];

        // dp[i][j] = max score when answering question i with j skips left
        std::vector<std::vector<double>> dp(questions + 2, std::vector<double>(skips + 1, 0.0));

        for (int i = questions; i >= 1; i--) {
            for (int skip = 0; skip <= skips; skip++) {
                double answering = (chances[i] / 100.0) * (prizes[i] + dp[i + 1][skip]);
                double skipping = 0.0;
                if (skip > 0) {
                    skipping = prizes[i] + dp[i + 1][skip - 1];
                }
                dp[i][skip] = std::max(answering, skipping);
            }
        }

        std::cout << std::fixed << std::setprecision(2) << dp[1][skips] << "\n";
    }

    return 0;
}
