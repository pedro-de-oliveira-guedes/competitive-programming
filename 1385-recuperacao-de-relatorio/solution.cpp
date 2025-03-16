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

bool arrangement_is_valid(std::vector<std::string> employee_sells, std::string line, int curr_col) {
    if (line.size() == 0 && employee_sells[employee_sells.size() - 1] == "") return false;
    if (employee_sells[curr_col].size() > 1 && employee_sells[curr_col][0] == '0') return false;
    if (curr_col < employee_sells.size() - 1 && employee_sells[curr_col].size() > 3) return false;
    return true;
}

bool check_sum(std::vector<std::string> values) {
    int sum = 0;
    for (int i = 0; i < values.size() - 1; i++) sum += std::stoi(values[i]);
    return sum == std::stoi(values[values.size() - 1]);
}

// Backtracking
std::pair<bool, std::vector<std::string>> split_values(
    std::string line,
    std::vector<std::string> employee_sells,
    int curr_col
) {
    if (!arrangement_is_valid(employee_sells, line, curr_col)) return {false, employee_sells};
    if (curr_col == employee_sells.size() - 1 && line.size() == 0) {
        // return check_sum(employee_sells) ? &employee_sells : nullptr;
        return {check_sum(employee_sells), employee_sells};
    }

    // Try increase current column
    employee_sells[curr_col] += line[0];
    std::pair<bool, std::vector<std::string>> answer = split_values(line.substr(1), employee_sells, curr_col);
    if (answer.first) return answer;
    else employee_sells[curr_col] = employee_sells[curr_col].substr(0, employee_sells[curr_col].size() - 1);

    // Try increase next column
    if (curr_col < employee_sells.size() - 1) {
        employee_sells[curr_col + 1] += line[0];
        return split_values(line.substr(1), employee_sells, curr_col + 1);
    }
    else return {false, employee_sells};
}

std::string backtrack(
    int columns,
    std::string line
) {
    std::string answer = "";

    std::vector<std::string> employee_sells(columns, "");
    std::vector<std::string> backtrack_answer = split_values(line, employee_sells, 0).second;

    for (const std::string& value : backtrack_answer) answer += " " + value;
    return answer;
}

std::string parse_employee_line(std::string line, int columns) {
    std::string employee_line = "";

    std::string name = "";
    for (const char& c : line) {
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) name += c;
        else break;
    }

    employee_line += name;
    line = line.substr(name.size());

    std::string values = backtrack(columns, line);
    employee_line += values;

    return employee_line;
}

std::vector<int> extract_employee_values(std::string employee_line, int columns) {
    std::vector<int> employee_values;
    
    std::stringstream values;
    values << employee_line.substr(employee_line.find(' ') + 1);
    
    while (columns--) {
        int value;
        values >> value;
        employee_values.push_back(value);
    }
    
    return employee_values;
}

std::string parse_last_line(int columns, std::vector<std::vector<int>> table_values) {
    std::string last_line = "TP";

    std::vector<int> values_sum(columns, 0);
    for (const std::vector<int>& table_line : table_values) {
        for (int i = 0; i < table_line.size(); i++) {
            values_sum[i] += table_line[i];
        }
    }

    for (const int& value : values_sum) last_line += " " + std::to_string(value);
    return last_line;
}

int main() {
    std::vector<std::string> answers;

    std::string test_cases_line;
    std::getline(std::cin, test_cases_line);
    int test_cases = std::stoi(test_cases_line);

    while (test_cases--) {
        std::string line;
        std::getline(std::cin, line);
        
        std::string header = parse_first_line(line);
        answers.push_back(header);

        int columns = 0;
        for (const char& c : header) {
            if (c == ' ') columns++;
        }
        columns++;

        std::vector<std::vector<int>> table_values;
        while(std::getline(std::cin, line)) {
            if (line[0] == 'T' && line[1] == 'P') {
                answers.push_back(parse_last_line(columns, table_values));
                break;
            }
            else {
                std::string employee_line = parse_employee_line(line, columns);
                answers.push_back(employee_line);
                table_values.push_back(extract_employee_values(employee_line, columns));
            }
        }
    }

    for (std::string& answer : answers) std::cout << answer << std::endl;

    return 0;
}
