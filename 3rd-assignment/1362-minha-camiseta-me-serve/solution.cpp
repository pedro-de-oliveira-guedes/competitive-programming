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

#define TSHIRT_SIZES 6
const std::unordered_map<std::string, int> TSHIRT_CODES = {
    {"XS", 1}, {"S", 2}, {"M", 3}, {"L", 4}, {"XL", 5}, {"XXL", 6}
};

int main() {
    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        int available_tshirts, volunteers;
        std::cin >> available_tshirts >> volunteers;

        int total_nodes = volunteers + TSHIRT_SIZES + 2, source = 0, sink = total_nodes - 1;
        auto graph = Graph(total_nodes, source, sink);
        for (int i = 1; i <= volunteers; i++) graph.add_edge(source, i, 1);
        for (int i = 1; i <= TSHIRT_SIZES; i++) graph.add_edge(volunteers + i, sink, available_tshirts/TSHIRT_SIZES);

        for (int i = 1; i <= volunteers; i++) {
            std::string size1, size2;
            std::cin >> size1 >> size2;

            graph.add_edge(i, volunteers + TSHIRT_CODES.at(size1), 1);
            graph.add_edge(i, volunteers + TSHIRT_CODES.at(size2), 1);
        }

        bool distributable = graph.get_max_flow() >= volunteers;
        std::cout << (distributable ? "YES" : "NO") << std::endl;
    }

    return 0;
}
