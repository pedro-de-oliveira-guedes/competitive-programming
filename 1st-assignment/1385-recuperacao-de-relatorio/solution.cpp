#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> table;
vector<int> employee_sell_offset;

bool rebuild_table(vector<string> sell_values, int curr_employee, int curr_product, int products_total) {
    if (curr_product < table[0].size()-1) { // The actual values for the products
        int curr_offset = employee_sell_offset[curr_employee];
        int sell_digits;
        if (curr_employee == sell_values.size() - 1) {
            sell_digits = sell_values[curr_employee].size(); // Last line with the sums of the sells for every employee
        } else {
            sell_digits = min(curr_offset + 3, (int)sell_values[curr_employee].size()); // No employee sold over 999 products
        }

        int acc = 0;
        for (int i = curr_offset; i < sell_digits; i++) {
            acc = (acc*10) + (sell_values[curr_employee][i] - '0'); // The possible value for the current product and the current employee
            employee_sell_offset[curr_employee] = i + 1; // The string start position for the possibilities of the current employee's next product
            table[curr_employee][curr_product] = acc;

            if ( // Tries the current possibility for the current employee and product with the next employee
                (curr_employee < sell_values.size() - 1) && rebuild_table(sell_values, curr_employee + 1, curr_product, products_total+acc)
            ) return true;

            if (curr_employee == sell_values.size() - 1) {
                if (products_total == acc) { // Possibilities for all employees matched with total sells for the current product
                    if (rebuild_table(sell_values, 0, curr_product+1, 0)) return true; // Restarts the process with the next product
                }

                if (acc > products_total) { // When the possible value for the current product sum exceeds the total sells
                    employee_sell_offset[curr_employee] = curr_offset; // Resets the string start position for the total sells
                    break;
                }
            }

            employee_sell_offset[curr_employee] = curr_offset;
            if (sell_values[curr_employee][curr_offset] == '0') break;
        }
    } else { // The LAST COLUMN (products) with the total sells for the current employee
        int val = 0, acc = 0;
        for (int i = employee_sell_offset[curr_employee]; i < sell_values[curr_employee].size(); i++)
            val = (val*10) + (sell_values[curr_employee][i] - '0'); // The remaining value in the string for the current employee

        for (int i = 0; i < table[0].size()-1; i++) acc += table[curr_employee][i]; // The sum of the products sold by the current employee

        if (acc != val) return false; // The sum of the products sold by the current employee must be equal to the total sells for the current employee

        table[curr_employee][curr_product] = val;
        if (curr_employee == sell_values.size() - 1) return true;
        else return rebuild_table(sell_values, curr_employee + 1, curr_product, 0);
    }

    return false;
}

int main() {
    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        vector<string> names, sell_values;
        string line;
        int products = 0;

        while (cin >> line) {
            if (line.back() == 's') { // Header line
                for (const char &c : line) if (c == 'P') products++;
                continue;
            }
            if (line[0] == 'T' && line[1] == 'P') { // Totals line
                names.emplace_back("TP");
                sell_values.emplace_back(line.substr(2));
                break;
            }

            string name;
            for (const char &c : line) {
                if (isalpha(c)) name += c;
                else break;
            }
            names.emplace_back(name);
            sell_values.emplace_back(line.substr(name.size()));
        }

        table.clear();
        table.resize(names.size(), vector<int>(products+1, 0));

        employee_sell_offset.clear();
        employee_sell_offset.resize(names.size(), 0);

        rebuild_table(sell_values, 0, 0, 0);

        // Print Header
        for (int i = 0; i < products; i++) cout << "P" << i+1 << " ";
        cout << "Totals" << endl;

        // Print Table
        for (int i = 0; i < table.size(); i++) {
            cout << names[i];
            for (int j = 0; j < table[i].size(); j++) cout << " " << table[i][j];
            cout << endl;
        }
    }

    return 0;
}
