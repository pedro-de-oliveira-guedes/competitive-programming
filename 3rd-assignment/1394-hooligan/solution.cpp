#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

class Edge {
    public:
        Edge(int source, int destine, int capacity, int flow = 0) {
            this->source = source;
            this->destine = destine;
            this->capacity = capacity;
            this->flow = flow;
        }
    protected:
        friend class Graph;
        int source, destine, capacity, flow;
};

class Graph {
    public:
        Graph(int size, int source, int sink) {
            this->source = source;
            this->sink = sink;
            this->adj_list.resize(size);
            this->bfs_parent.resize(size, -1);
            this->last_edge_index = 0;
        }

        void add_edge(int origin, int destine, int capacity) {
            this->edges.emplace_back(origin, destine, capacity);
            this->adj_list[origin].push_back(last_edge_index++);

            this->edges.emplace_back(destine, origin, 0); // reverse edge with 0 capacity
            this->adj_list[destine].push_back(last_edge_index++);
        }

        int get_max_flow() {
            int max_flow = 0;

            while (this->found_path_to_sink()) {
                int available_flow;
                while (available_flow = this->get_available_flow(this->source, INT_MAX)) max_flow += available_flow;
            }

            return max_flow;
        }

    private:
        std::vector<Edge> edges;
        std::vector<std::vector<int>> adj_list;
        int source, sink;
        int last_edge_index;
        std::vector<int> bfs_parent;

        bool found_path_to_sink() { // BFS
            std::fill(this->bfs_parent.begin(), this->bfs_parent.end(), -1);
            this->bfs_parent[this->source] = 0;

            std::queue<int> q;
            q.push(this->source);

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (const int &edge_idx : this->adj_list[current]) {
                    bool already_visited = this->bfs_parent[this->edges[edge_idx].destine] != -1;
                    bool has_capacity = this->edges[edge_idx].capacity > this->edges[edge_idx].flow;
                    if (!already_visited && has_capacity) {
                        this->bfs_parent[this->edges[edge_idx].destine] = this->bfs_parent[current] + 1;
                        q.push(this->edges[edge_idx].destine);
                    }
                }
            }

            return this->bfs_parent[this->sink] != -1;
        }

        int get_available_flow(int origin, int current_flow) {
            if (current_flow == 0) return 0;
            if (origin == this->sink) return current_flow;

            for (const int &edge_idx : this->adj_list[origin]) {
                int dst = this->edges[edge_idx].destine;

                bool available_path = this->bfs_parent[dst] == this->bfs_parent[origin] + 1;
                bool has_capacity = this->edges[edge_idx].capacity > this->edges[edge_idx].flow;
                if (available_path && has_capacity) {
                    int available_flow = get_available_flow(dst, std::min(current_flow, this->edges[edge_idx].capacity - this->edges[edge_idx].flow));
                    if (available_flow > 0) {
                        this->edges[edge_idx].flow += available_flow;
                        this->edges[edge_idx ^ 1].flow -= available_flow; // reverse edge

                        return available_flow;
                    }
                }
            }

            return 0;
        }
};

#define WIN_SCORE 2

int main() {
    int teams, matches_by_team, played_matches;
    while (true) {
        std::cin >> teams >> matches_by_team >> played_matches;
        if (teams == 0 && matches_by_team == 0 && played_matches == 0) break;

        std::vector<std::vector<int>> matches_count(teams + 1, std::vector<int>(teams + 1, 0));
        std::vector<int> team_score(teams + 1, 0);
        int dream_team_matches = 0;
        while (played_matches--) {
            int team_a, team_b;
            char result;
            std::cin >> team_a >> result >> team_b;

            matches_count[team_a][team_b]++;
            matches_count[team_b][team_a]++;

            if (result == '<') {
                team_score[team_b] += WIN_SCORE;
            } else {
                team_score[team_a]++;
                team_score[team_b]++;
            }

            if (team_a == 0 || team_b == 0) dream_team_matches++;
        }

        int second_place_max_score = team_score[0] + ((matches_by_team * (teams - 1)) - dream_team_matches) * WIN_SCORE - 1;
        bool winnable = true;
        for (int team = 1; team < teams; team++) {
            if (team_score[team] > second_place_max_score) {
                winnable = false;
                break;
            }
        }
        if (!winnable) {
            std::cout << "N" << std::endl;
            continue;
        }

        int total_nodes = teams; // One node for each team and one node for each match between them
        std::vector<std::vector<int>> future_matches(teams, std::vector<int>(teams, 0));
        int max_future_scores_sum = 0;
        for (int team_a = 1; team_a < teams; team_a++) {
            for (int team_b = team_a + 1; team_b < teams; team_b++) {
                max_future_scores_sum += (matches_by_team - matches_count[team_a][team_b]) * WIN_SCORE;
                future_matches[team_a][team_b] = total_nodes++;
            }
        }

        auto graph = Graph(total_nodes + 2, 0, total_nodes + 1);
        for (int team_a = 1; team_a < teams; team_a++) {
            graph.add_edge(0, team_a, second_place_max_score - team_score[team_a]);
            for (int team_b = team_a + 1; team_b < teams; team_b++) {
                int future_match = future_matches[team_a][team_b];

                graph.add_edge(team_a, future_match, INF);
                graph.add_edge(team_b, future_match, INF);
                graph.add_edge(future_match, total_nodes + 1, (matches_by_team - matches_count[team_a][team_b]) * WIN_SCORE);
            }
        }

        winnable = graph.get_max_flow() == max_future_scores_sum;
        std::cout << (winnable ? "Y" : "N") << std::endl;
    }

    return 0;
}
