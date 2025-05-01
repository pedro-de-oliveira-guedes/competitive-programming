// Este problema é mentiroso. Ele diz claramente que existe uma restrição 1 <= S <= 300, mas ela não é respeitada
// nos casos de teste. Existem vários problemas com tempo de solução S igual a 0, que devem ser considerados como
// resolvidos também.
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

int lower_bound = 1, upper_bound = INF;

class Score {
    public:
        int failed_attempts{}, time_penalty{}, solved_problems{};

        Score(std::vector<int> failed_attempts, std::vector<int> time_penalties) {
            for (int i = 0; i < failed_attempts.size(); i++) {
                if (time_penalties[i] >= 0) {
                    solved_problems += 1;
                    this->failed_attempts += failed_attempts[i];
                    this->time_penalty += time_penalties[i];
                }
            }
        }

        int get_interception_point(Score score) {
            if (this->failed_attempts == score.failed_attempts) {
                return 0;
            }
            else {
                return (int)((score.time_penalty - this->time_penalty) / (this->failed_attempts - score.failed_attempts));
            }
        }

        int get_score(int error_penalty) {
            return this->time_penalty + this->failed_attempts * error_penalty;
        }
};

std::pair<std::vector<int>, std::vector<int>> read_teams_problems(int problems) {
    std::vector<int> failed_attempts{}, time_penalties{};

    for (int i = problems; i > 0; i--) {
        int attempts, time_penalty;
        char trash;
        std::string submission;
        std::cin >> attempts >> trash >> submission;

        if (submission[0] == '-') time_penalty = -1;
        else time_penalty = std::stoi(submission);

        failed_attempts.emplace_back(attempts);
        time_penalties.emplace_back(time_penalty);
    }

    return {failed_attempts, time_penalties};
}

void check_interceptions(std::vector<Score> bin) {
    for (int i = 0; i < bin.size(); i++) {
        for (int j = i+1; j < bin.size(); j++) {
            int point = bin[i].get_interception_point(bin[j]);

            if (point < 20) lower_bound = std::max(lower_bound, point + 1);
            else if (
                point > 20 ||
                (point == 20 && bin[i].get_score(point) != bin[j].get_score(point))
            ) {
                if (bin[i].get_score(point) == bin[j].get_score(point))
                    upper_bound = std::min(upper_bound, point - 1);
                else
                    upper_bound = std::min(upper_bound, point);
            }
            else lower_bound = upper_bound = 20;

            if (lower_bound == upper_bound == 20) return;
        }
    }
}

int main() {
    int teams, problems;
    std::cin >> teams >> problems;

    while (teams > 0 && problems > 0) {
        std::vector<std::vector<Score>> teams_bins(problems);
        while(teams--) {
            auto team_problems = read_teams_problems(problems);
            auto score = Score(team_problems.first, team_problems.second);
            teams_bins[std::max(0, score.solved_problems-1)].emplace_back(score);
        }

        for (const auto &score_bin : teams_bins) {
            check_interceptions(score_bin);
            if (lower_bound == upper_bound == 20) break;
        }
        lower_bound < 0 ? std::cout << "1 " : std::cout << lower_bound << " ";
        upper_bound == INF ? std::cout << "*" << std::endl : std::cout << upper_bound << std::endl;

        std::cin >> teams >> problems;
        lower_bound = 1;
        upper_bound = INF;
    }

    return 0;
}
