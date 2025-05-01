#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> pii; 

std::vector<int> get_enemies_locations(int strategic_points) {
    int enemies_amount;
    std::cin >> enemies_amount;

    std::vector<int> enemies_location(strategic_points, 0);
    while (enemies_amount--) {
        int enemy_location;
        std::cin >> enemy_location;
        enemy_location--;

        enemies_location[enemy_location]++;
    }

    return enemies_location;
}

std::vector<std::vector<int>> build_leningrad(int strategic_points, int roads_amount) {
    std::vector<std::vector<int>> leningrad(strategic_points);

    while(roads_amount--) {
        int sp1, sp2;
        std::cin >> sp1 >> sp2;
        sp1--;
        sp2--;

        leningrad[sp1].push_back(sp2);
        leningrad[sp2].push_back(sp1);
    }

    return leningrad;
}

// Dijkstra Algorithm
std::vector<int> get_shortest_paths(
    int strategic_points, int start_point,
    std::vector<int> enemies_locations,
    std::vector<std::vector<int>> leningrad
) {
    std::vector<int> distances(strategic_points, INF);
    std::vector<bool> visited(strategic_points, false);

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> next_points;

    distances[start_point] = enemies_locations[start_point];
    next_points.push(std::make_pair(enemies_locations[start_point], start_point));

    while (!next_points.empty()) {
        int curr_point = next_points.top().second;
        next_points.pop();

        if (visited[curr_point]) continue;

        visited[curr_point] = true;

        for (int j = 0; j < leningrad[curr_point].size(); j++) {
            int neighboor = leningrad[curr_point][j];
            int enemies = enemies_locations[neighboor];

            if (distances[neighboor] > distances[curr_point] + enemies) {
                distances[neighboor] = distances[curr_point] + enemies;
                next_points.push(std::make_pair(distances[neighboor], neighboor));
            }
        }
    }

    return distances;
}

int main() {
    std::vector<double> answers;

    int strategic_points, roads_amount, soldier_ammo;
    double soldier_prob;
    while(std::cin >> strategic_points >> roads_amount >> soldier_ammo >> soldier_prob) {
        std::vector<std::vector<int>> leningrad = build_leningrad(strategic_points, roads_amount);
        std::vector<int> enemies_locations = get_enemies_locations(strategic_points);

        int start_point, destine_point;
        std::cin >> start_point >> destine_point;
        start_point--;
        destine_point--;

        std::vector<int> shortest_paths = get_shortest_paths(
            strategic_points, start_point,
            enemies_locations,
            leningrad
        );

        int shortest_path = shortest_paths[destine_point];

        if (shortest_path == INF) answers.push_back(0.000);
        else if (shortest_path > soldier_ammo) answers.push_back(0.000);
        else if (shortest_path == 0) answers.push_back(1.000);
        else answers.push_back(std::pow(soldier_prob, shortest_path));
    }

    for (const double& answer : answers) {
        std::cout << std::fixed << std::setprecision(3) << answer << std::endl;
    }

    return 0;
}
