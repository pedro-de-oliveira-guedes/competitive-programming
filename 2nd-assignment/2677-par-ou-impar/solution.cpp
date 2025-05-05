#include <bits/stdc++.h>

int main() {
    int evens_amount;
    while (std::cin >> evens_amount && evens_amount > 0) {
        int seq_size = 2 * evens_amount;

        std::vector<int> sequence(seq_size);
        for (int i = 0; i < seq_size; i++) std::cin >> sequence[i];

        // Differences between the amount of even numbers picked in subsequences dp[i][j]
        std::vector<std::vector<int>> dp(seq_size, std::vector<int>(seq_size, 0));
        // When i=j, meaning the subsequence starts and ends at the same index, the first player would pick it.
        // So all that matters is if the number is even or odd.
        for (int i = 0; i < seq_size; i++) dp[i][i] = (sequence[i] % 2 == 0);

        // For all subsequences of size "len" in the sequence
        for (int len = 2; len <= seq_size; len++) {
            // For all starting points "left" of the subsequence
            for (int left = 0; (left + len - 1) < seq_size; left++) {
                int right = left + len - 1; // Ending point "right" of the subsequence

                int left_pick  = (sequence[left] % 2 == 0) - dp[left+1][right];
                int right_pick = (sequence[right] % 2 == 0) - dp[left][right-1];

                dp[left][right] = std::max(left_pick, right_pick);
            }
        }

        // first_pick_evens - second_pick_evens = dp[0][seq_size-1]
        // first_pick_evens + second_pick_evens = evens_amount
        // Summing both equations gives us: 2 * first_pick_evens = evens_amount + dp[0][seq_size-1]
        // So we can calculate first_pick_evens as:
        int first_pick_evens = (evens_amount + dp[0][seq_size-1]) / 2;
        std::cout << first_pick_evens << std::endl;
    }

    return 0;
}
