#include <bits/stdc++.h>

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

int main() {
    int instances = 0;
    int horses, soldiers, affinities;
    while (std::cin >> horses >> soldiers >> affinities) {
        instances++;

        int total_nodes = horses + soldiers + 2;
        int source = 0, sink = total_nodes - 1;
        auto graph = Graph(total_nodes, source, sink);

        for (int horse = 1; horse <= horses; ++horse) {
            int horse_capacity;
            std::cin >> horse_capacity;

            graph.add_edge(source, horse, horse_capacity);
        }

        for (int i = 0; i < affinities; i++) {
            int horse, soldier;
            std::cin >> horse >> soldier;

            graph.add_edge(horse, horses + soldier, 1);
        }

        for (int soldier = 1; soldier <= soldiers; soldier++) {
            graph.add_edge(horses + soldier, sink, 1);
        }

        std::cout << "Instancia " << instances << std::endl;
        std::cout << graph.get_max_flow() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
