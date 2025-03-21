#include <bits/stdc++.h>

std::string parse_first_line (std::string line) {
    std::string first_line = "";

    while (line.size() > 0) {
        std::string p_code;
        p_code = line.substr(0, 2);
        if (p_code[0] == 'P') {
            first_line += p_code + " ";
            line = line.substr(2);
        }
        else {
            first_line += line;
            break;
        }
    }

    return first_line;
}

bool arrangement_is_valid(
    std::vector<std::string> employee_sells,
    std::string line,
    int curr_col,
    bool last_line
) {
    if (line.size() == 0 && employee_sells[employee_sells.size() - 1] == "") return false;
    if (employee_sells[curr_col].size() > 1 && employee_sells[curr_col][0] == '0') return false;
    if (curr_col < employee_sells.size() - 1) {
        if (employee_sells[curr_col].size() > (3 + last_line)) return false;
    }
    else {
        if (employee_sells[curr_col].size() > (4 + last_line)) return false;
    }
    for (int i = 0; i < curr_col; i++) if (employee_sells[i] == "") return false;
    return true;
}

bool check_sum(std::vector<std::string> values) {
    if (values[values.size() - 1].size() > 4) return false;
    int sum = 0;
    for (int i = 0; i < values.size() - 1; i++) sum += std::stoi(values[i]);
    return sum == std::stoi(values[values.size() - 1]);
}

// Backtracking
void split_values(
    std::string line,
    bool last_line,
    std::vector<std::string> employee_sells,
    int curr_col,
    std::set<std::vector<int>> *valid_solutions
) {
    if (!arrangement_is_valid(employee_sells, line, curr_col, last_line)) return;
    if (curr_col == employee_sells.size() - 1 && line.size() == 0) {
        if (check_sum(employee_sells)) {
            std::vector<int> valid_solution;
            for (const std::string& value : employee_sells) valid_solution.push_back(std::stoi(value));
            valid_solutions->insert(valid_solution);
        }
        return;
    }

    // Try increase current column
    employee_sells[curr_col] += line[0];
    split_values(line.substr(1), last_line, employee_sells, curr_col, valid_solutions);
    
    // Try increase next column
    if (curr_col < employee_sells.size() - 1) {
        employee_sells[curr_col] = employee_sells[curr_col].substr(0, employee_sells[curr_col].size() - 1);
        employee_sells[curr_col + 1] += line[0];
        return split_values(line.substr(1), last_line, employee_sells, curr_col + 1, valid_solutions);
    }
}

std::set<std::vector<int>> backtrack(
    int columns,
    std::string line,
    bool last_line = false
) {
    std::set<std::vector<int>> valid_answers;

    std::vector<std::string> employee_sells(columns, "");
    split_values(line, last_line, employee_sells, 0, &valid_answers);

    return valid_answers;
}

std::pair<std::string, std::set<std::vector<int>>> parse_employee_data(
    std::string line,
    int columns
) {
    std::string name = "";
    for (const char& c : line) {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) name += c;
        else break;
    }

    line = line.substr(name.size());
    std::set<std::vector<int>> values = backtrack(columns, line);

    return {name, values};
}

bool validate_table(std::vector<std::vector<int>> valid_solution) {
    for (int i = 0; i < valid_solution[0].size(); i++) {
        int col_sum = 0;
        for (int j = 0; j < valid_solution.size() - 1; j++) col_sum += valid_solution[j][i];
        if (col_sum != valid_solution[valid_solution.size() - 1][i]) return false;
    }
    return true;
}

bool determine_valid_solution(
    std::vector<std::set<std::vector<int>>> table_values,
    std::vector<std::vector<int>> *valid_solution,
    int curr_table_line
) {
    if (curr_table_line == table_values.size()) return validate_table(*valid_solution);

    for (const std::vector<int> &possible_solution : table_values[curr_table_line]) {
        valid_solution->push_back(possible_solution);
        if (determine_valid_solution(table_values, valid_solution, curr_table_line+1)) return true;
        else valid_solution->pop_back();
    }

    return false;
}

int main() {
    std::string test_cases_line;
    std::getline(std::cin, test_cases_line);
    int test_cases = std::stoi(test_cases_line);

    while (test_cases--) {
        std::string line;
        std::getline(std::cin, line);
        
        std::string header = parse_first_line(line);

        int columns = 0;
        for (const char& c : header) {
            if (c == ' ') columns++;
        }
        columns++;

        std::vector<std::set<std::vector<int>>> table_values;
        while(std::getline(std::cin, line)) {
            if (line[0] == 'T' && line[1] == 'P') {
                std::set<std::vector<int>> total_sum_possibilities = backtrack(columns, line.substr(2), true);
                table_values.push_back(total_sum_possibilities);
                break;
            }
            else {
                std::pair<std::string, std::set<std::vector<int>>> employee_data = parse_employee_data(line, columns);
                table_values.push_back(employee_data.second);
            }
        }

        std::vector<std::vector<int>> valid_solution;
        determine_valid_solution(table_values, &valid_solution, 0);

        std::cout << header << std::endl;
        for (int i = 0; i < valid_solution.size(); i++) {
            std::vector<int> table_line = valid_solution[i];

            std::string full_line = "";
            for (const int &number : table_line) full_line += std::to_string(number) + " ";
            full_line.erase(full_line.size() - 1);

            if (i == valid_solution.size() - 1) std::cout << "TP ";
            std::cout << full_line << std::endl;
        }
    }

    return 0;
}
