#include <bits/stdc++.h>

int main() {
    int rows, columns, friends;
    std::cin >> rows >> columns >> friends;

    while (rows != 0 || columns != 0 || friends != 0) {
        std::vector<std::vector<int>> available_seats(rows + 1, std::vector<int>(columns, 0));
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < columns; col++) {
                char seat;
                std::cin >> seat;
                available_seats[row + 1][col] = available_seats[row][col] + (seat == '.' ? 1 : 0);
            }
        }

        int min_area = INT_MAX;

        for (int row1 = 0; row1 < rows; row1++) {
            for (int row2 = row1; row2 < rows; row2++) {
                std::vector<int> col_free_seats(columns);
                for (int col = 0; col < columns; col++) {
                    col_free_seats[col] = available_seats[row2 + 1][col] - available_seats[row1][col];
                }

                int total_free_seats = 0, cols_left = 0;
                for (int col = 0; col < columns; col++) {
                    total_free_seats += col_free_seats[col];

                    while (cols_left <= col && total_free_seats - col_free_seats[cols_left] >= friends) {
                        total_free_seats -= col_free_seats[cols_left];
                        cols_left++;
                    }

                    if (total_free_seats >= friends) {
                        int height = row2 - row1 + 1;
                        int width = col - cols_left + 1;
                        min_area = std::min(min_area, height * width);
                    }
                }
            }
        }

        std::cout << min_area << std::endl;

        std::cin >> rows >> columns >> friends;
    }

    return 0;
}
