#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

class VodkaProduction {
    public:
        int periods, initial_age, max_age, price;
        std::vector<int> maintenance_costs, sell_costs;
        std::vector<std::vector<int>> should_replace;
        bool valid;

        VodkaProduction() {
            if (!(std::cin >> this->periods >> this->initial_age >> this->max_age >> this->price)) {
                this->valid = false;
                return;
            }
            this->valid = true;

            this->maintenance_costs.resize(this->max_age);
            for (int i = 0; i < this->max_age; ++i)
                std::cin >> this->maintenance_costs[i];

            this->sell_costs.resize(this->max_age + 1);
            for (int i = 1; i <= max_age; ++i)
                std::cin >> this->sell_costs[i];

            this->should_replace.resize(this->periods + 2, std::vector<int>(this->max_age + 2, -1));
        }

        std::pair<int, std::vector<int>> get_production_results() {
            int min_cost = this->get_min_production_cost();
            std::vector<int> replacement_years = this->get_replacement_years();

            return {min_cost, replacement_years};
        }

    private:
        int get_min_production_cost() {
            std::vector<std::vector<int>> dp(this->periods + 2, std::vector<int>(this->max_age + 2, INF));
            for (int age = 1; age <= this->max_age; age++) dp[periods + 1][age] = 0;

            for (int year = this->periods; year >= 1; year--) {
                for (int age = 1; age <= this->max_age; age++) {
                    if (age < this->max_age) {
                        int keep_cost = this->maintenance_costs[age] + dp[year + 1][age + 1];
                        dp[year][age] = keep_cost;
                        this->should_replace[year][age] = 0;
                    } else {
                        dp[year][age] = INF;
                    }

                    int replace_cost = this->maintenance_costs[0] + this->price - this->sell_costs[age] + dp[year + 1][1];
                    if (replace_cost <= dp[year][age]) {
                        dp[year][age] = replace_cost;
                        this->should_replace[year][age] = 1;
                    }
                }
            }

            return dp[1][this->initial_age];
        }

        std::vector<int> get_replacement_years() {
            std::vector<int> replacement_years;

            int current_year = 1, current_age = this->initial_age;
            while (current_year <= this->periods) {
                if (this->should_replace[current_year][current_age] == 1) {
                    replacement_years.push_back(current_year);
                    current_age = 1; // Reset age after replacement
                } else {
                    current_age++;
                }
                current_year++;
            }

            return replacement_years;
        }
};

int main() {
    auto great_vodka = VodkaProduction();

    while (great_vodka.valid) {
        auto [min_cost, replacement_years] = great_vodka.get_production_results();

        std::cout << min_cost << std::endl;
        if (replacement_years.empty()) {
            std::cout << "0" << std::endl;
        } else {
            for (int i = 0; i < replacement_years.size(); i++) {
                if (i > 0) std::cout << " ";
                std::cout << replacement_years[i];
            }
            std::cout << std::endl;
        }

        great_vodka = VodkaProduction();
    }

    return 0;
}