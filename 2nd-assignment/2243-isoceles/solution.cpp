#include <bits/stdc++.h>

int main() {
    int total_columns;
    std::cin >> total_columns;

    std::vector<int> columns(total_columns, 0);
    for (int i = 0; i < total_columns; i++) std::cin >> columns[i];

    std::vector<int> left_sides(total_columns, 1);
    for (int i = 1; i < total_columns; i++)
        left_sides[i] = std::min(left_sides[i - 1] + 1, columns[i]);

    std::vector<int> right_sides(total_columns, 1);
    for (int i = total_columns - 2; i >= 0; i--)
        right_sides[i] = std::min(right_sides[i + 1] + 1, columns[i]);

    int max_height = 0;
    for (int i = 0; i < total_columns; i++)
        max_height = std::max(max_height, std::min(left_sides[i], right_sides[i]));

    std::cout << max_height << std::endl;

    return 0;
}
