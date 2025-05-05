#include <bits/stdc++.h>

int main() {
    int sequence_length, subsequence_length;
    
    while (std::cin >> sequence_length >> subsequence_length && sequence_length > 0 && subsequence_length > 0) {
        std::vector<int> sequence(sequence_length);
        for (int i = 0; i < sequence_length; i++) std::cin >> sequence[i];

        std::vector<std::vector<long long>> dp(sequence_length, std::vector<long long>(subsequence_length, 0));
        for (int i = 0; i < sequence_length; i++) dp[i][0] = 1;

        for (int num = 1; num < sequence_length; num++) {
            for (int aux_num = 0; aux_num < num; aux_num++) {
                if (sequence[num] > sequence[aux_num]) {
                    for (int subseq_size = 1; subseq_size < subsequence_length; subseq_size++) {
                        dp[num][subseq_size] += dp[aux_num][subseq_size - 1];
                    }
                }
            }
        }

        long long total_subsequences = 0;
        for (int i = 0; i < sequence_length; i++) total_subsequences += dp[i][subsequence_length - 1];

        std::cout << total_subsequences << std::endl;
    }

    return 0;
}
