#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> Position;
const std::vector<Position> horse_moves = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {2, 1}
};

std::vector<std::vector<int>> get_target_distances( // BFS
    const Position &start,
    int rows,
    int cols,
    std::vector<std::string> &board
) {
    std::vector<std::vector<int>> distances(rows, std::vector<int>(cols, -1));
    std::queue<std::pair<Position, int>> queue;

    queue.push({start, 0});
    distances[start.first][start.second] = 0;

    while (!queue.empty()) {
        auto [current, dist] = queue.front();
        queue.pop();

        for (const auto &move : horse_moves) {
            Position next_pos = {current.first + move.first, current.second + move.second};

            bool inside_board = next_pos.first >= 0 && next_pos.first < rows && next_pos.second >= 0 && next_pos.second < cols;
            bool available_position = inside_board && board[next_pos.first][next_pos.second] != '#';
            bool not_visited = available_position && distances[next_pos.first][next_pos.second] == -1;

            if (not_visited) {
                distances[next_pos.first][next_pos.second] = dist + 1;
                queue.push({next_pos, dist + 1});
            }
        }
    }

    return distances;
}

std::vector<std::vector<int>> get_all_target_distances(
    std::vector<std::string> board,
    Position horse_pos,
    std::vector<Position> pawns_pos
) {
    int pawns = pawns_pos.size();
    int rows = board.size();
    int cols = board[0].size();

    std::vector<Position> targets;
    targets.push_back(horse_pos);
    targets.insert(targets.end(), pawns_pos.begin(), pawns_pos.end());

    std::vector<std::vector<int>> all_target_distances(pawns + 1, std::vector<int>(pawns+1));
    for (int i = 0; i < pawns + 1; i++) {
        auto target_distances = get_target_distances(targets[i], rows, cols, board);
        for (int j = 0; j < pawns + 1; j++) {
            all_target_distances[i][j] = target_distances[targets[j].first][targets[j].second];
        }
    }

    return all_target_distances;
}

std::vector<std::vector<int>> get_all_distances(
    int pawns,
    std::vector<std::vector<int>> all_targets_distances
) { // Traveling Salesman Problem (TSP)
    std::vector<std::vector<int>> dp(1 << pawns, std::vector<int>(pawns, INF));
    for (int i = 0; i < pawns; i++) {
        dp[1 << i][i] = all_targets_distances[0][i + 1];
    }

    for (int mask = 1; mask < (1 << pawns); mask++) {
        for (int curr_pawn = 0; curr_pawn < pawns; curr_pawn++) {
            if (!(mask & (1 << curr_pawn))) continue; // If current pawn is not in the mask

            int last_mask = mask ^ (1 << curr_pawn);
            if (last_mask == 0) continue; // Base case, no previous pawn

            for (int last_pawn = 0; last_pawn < pawns; last_pawn++) {
                if ((last_mask >> last_pawn) & 1) {
                    int new_distance = dp[last_mask][last_pawn] + all_targets_distances[last_pawn + 1][curr_pawn + 1];
                    dp[mask][curr_pawn] = std::min(dp[mask][curr_pawn], new_distance);
                }
            }
        }
    }

    return dp;
}

int main() {
    int rows, cols, pawns;
    std::cin >> rows >> cols >> pawns;

    while (rows > 0 && cols > 0 && pawns > 0) {
        Position horse_pos;
        std::vector<Position> pawns_pos;

        std::vector<std::string> board(rows);
        for (int i = 0; i < rows; ++i) {
            std::cin >> board[i];

            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'C') {
                    horse_pos = {i, j};
                } else if (board[i][j] == 'P') {
                    pawns_pos.push_back({i, j});
                }
            }
        }
    
        auto all_target_distances = get_all_target_distances(board, horse_pos, pawns_pos);
        auto all_distances = get_all_distances(pawns, all_target_distances);

        int min_distance = INF;
        int final_mask = (1 << pawns) - 1;
        for (int final_pawn = 0; final_pawn < pawns; final_pawn++) {
            int return_distance = all_target_distances[final_pawn + 1][0];
            int total_distance = all_distances[final_mask][final_pawn] + return_distance;
            min_distance = std::min(min_distance, total_distance);
        }

        std::cout << min_distance << std::endl;

        std::cin >> rows >> cols >> pawns;
    }

    return 0;
}