#include <bits/stdc++.h>
#include <cmath>

int max_pieces = 0;

void get_max_pieces(
    std::vector<std::vector<int>> *board,
    std::pair<int, int> my_piece_pos,
    int captured_pieces
) {
    if ((my_piece_pos.first - 1 > 0) && (my_piece_pos.second - 1 > 0) &&
        board->at(my_piece_pos.first-1).at(my_piece_pos.second-1) == 2 &&
        board->at(my_piece_pos.first-2).at(my_piece_pos.second-2) == 0
    ) {
        board->at(my_piece_pos.first).at(my_piece_pos.second) = 0;
        board->at(my_piece_pos.first-1).at(my_piece_pos.second-1) = -1;
        max_pieces = std::max({max_pieces, captured_pieces+1});
        get_max_pieces(board, {my_piece_pos.first-2, my_piece_pos.second-2}, captured_pieces+1);
        board->at(my_piece_pos.first-1).at(my_piece_pos.second-1) = 2;
        // board->at(my_piece_pos.first).at(my_piece_pos.second) = 1;
    }

    if ((my_piece_pos.first - 1 > 0) && (my_piece_pos.second + 1 < board->at(0).size()-1) &&
        board->at(my_piece_pos.first-1).at(my_piece_pos.second+1) == 2 &&
        board->at(my_piece_pos.first-2).at(my_piece_pos.second+2) == 0
    ) {
        board->at(my_piece_pos.first).at(my_piece_pos.second) = 0;
        board->at(my_piece_pos.first-1).at(my_piece_pos.second+1) = -1;
        max_pieces = std::max({max_pieces, captured_pieces+1});
        get_max_pieces(board, {my_piece_pos.first-2, my_piece_pos.second+2}, captured_pieces+1);
        board->at(my_piece_pos.first-1).at(my_piece_pos.second+1) = 2;
        // board->at(my_piece_pos.first).at(my_piece_pos.second) = 1;
    }

    if ((my_piece_pos.first + 1 < board->size()-1) && (my_piece_pos.second - 1 > 0) &&
        board->at(my_piece_pos.first+1).at(my_piece_pos.second-1) == 2 &&
        board->at(my_piece_pos.first+2).at(my_piece_pos.second-2) == 0
    ) {
        board->at(my_piece_pos.first).at(my_piece_pos.second) = 0;
        board->at(my_piece_pos.first+1).at(my_piece_pos.second-1) = -1;
        max_pieces = std::max({max_pieces, captured_pieces+1});
        get_max_pieces(board, {my_piece_pos.first+2, my_piece_pos.second-2}, captured_pieces+1);
        board->at(my_piece_pos.first+1).at(my_piece_pos.second-1) = 2;
        // board->at(my_piece_pos.first).at(my_piece_pos.second) = 1;
    }

    if ((my_piece_pos.first + 1 < board->size()-1) && (my_piece_pos.second + 1 < board->at(0).size()-1) &&
        board->at(my_piece_pos.first+1).at(my_piece_pos.second+1) == 2 &&
        board->at(my_piece_pos.first+2).at(my_piece_pos.second+2) == 0
    ) {
        board->at(my_piece_pos.first).at(my_piece_pos.second) = 0;
        board->at(my_piece_pos.first+1).at(my_piece_pos.second+1) = -1;
        max_pieces = std::max({max_pieces, captured_pieces+1});
        get_max_pieces(board, {my_piece_pos.first+2, my_piece_pos.second+2}, captured_pieces+1);
        board->at(my_piece_pos.first+1).at(my_piece_pos.second+1) = 2;
        // board->at(my_piece_pos.first).at(my_piece_pos.second) = 1;
    }
}

int main() {
    int rows, columns;
    std::cin >> rows >> columns;

    while (rows >= 3 && columns >= 3) {
        std::vector<std::vector<int>> board(rows, std::vector<int>(columns, -1));
        int available_spots = (std::ceil((float) rows / 2) * std::ceil((float) columns / 2) +
                               std::floor((float) rows / 2) * std::floor((float) columns / 2));
        std::vector<std::pair<int, int>> my_pieces{};

        int curr_row = 0, curr_col = 0;
        while (available_spots--) {
            int spot;
            std::cin >> spot;

            board[curr_row][curr_col] = spot;
            if (spot == 1) my_pieces.push_back({curr_row, curr_col});

            curr_col += 2;
            if (curr_col >= columns) {
                curr_row += 1;
                curr_col = 0 + (curr_row % 2);
            }
        }

        for (auto &piece_pos : my_pieces) {
            get_max_pieces(&board, piece_pos, 0);
            board[piece_pos.first][piece_pos.second] = 1;
        }
        std::cout << max_pieces << std::endl;
        max_pieces = 0;

        std::cin >> rows >> columns;
    }
    return 0;
}
