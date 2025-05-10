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
                // Each position (i, j) represents the amount of available seats in the column j until row i-1.
                available_seats[row + 1][col] = available_seats[row][col] + (seat == '.' ? 1 : 0);
            }
        }

        int min_area = INT_MAX;

        for (int row1 = 0; row1 < rows; row1++) {
            for (int row2 = row1; row2 < rows; row2++) {
                std::vector<int> col_free_seats(columns);
                for (int col = 0; col < columns; col++) {
                    // The number of available seats in column j, between row1 and row2
                    col_free_seats[col] = available_seats[row2 + 1][col] - available_seats[row1][col];
                }

                int total_free_seats = 0, cols_left = 0;
                for (int col = 0; col < columns; col++) {
                    total_free_seats += col_free_seats[col];

                    // At some point, the total free seats between row1 and row2, counting up to column col,
                    // may be greater than the number of friends.
                    // If that is the case, free seats to the left of col can be removed from the total sum,
                    // trying to minimize the area.
                    while (cols_left <= col && total_free_seats - col_free_seats[cols_left] >= friends) {
                        total_free_seats -= col_free_seats[cols_left];
                        cols_left++;
                    }

                    // If the total free seats is greater than or equal to the number of friends,
                    // we can calculate the area and check if it is the minimum area found so far.
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
