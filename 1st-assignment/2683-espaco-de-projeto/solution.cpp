#include <bits/stdc++.h>

using namespace std;

class UnionFind {
    public:
        vector<int> parent{}, component_size{};
        int num_components;

        UnionFind(int elements) {
            this->num_components = elements;
            for (int i = 0; i < elements; i++) {
                this->parent.emplace_back(i);
                this->component_size.emplace_back(1);
            }
        }

        int find(int element) {
            int component_root = element;
            while (component_root != this->parent[component_root])
                component_root = this->parent[component_root];

            // Path compression
            while (element != component_root) {
                int element_parent = this->parent[element];
                this->parent[element] = component_root;
                element = element_parent;
            }

            return component_root;
        }

        // Returns true when the union find is complete, meaning there is only one component
        bool unify(int node1, int node2) {
            int root1 = this->find(node1);
            int root2 = this->find(node2);

            if (root1 == root2) return false;

            if (this->component_size[root1] < this->component_size[root2]) {
                this->component_size[root2] += this->component_size[root1];
                this->parent[root1] = root2;
            } else {
                this->component_size[root1] += this->component_size[root2];
                this->parent[root2] = root1;
            }

            this->num_components--;
            return true;
        }
};

// Kruskal
int build_spanning_tree(
    vector<pair<int, pair<int, int>>> graph,
    bool maximum_st = false
) {
    if (maximum_st)
        sort(graph.begin(), graph.end(), greater<>());
    else
        sort(graph.begin(), graph.end());

    UnionFind uf = UnionFind((1 + std::sqrt(1 + 8 * graph.size())) / 2);

    int spanning_tree_cost = 0;
    for (const auto &edge : graph) {
        if (uf.find(edge.second.first) != uf.find(edge.second.second)) {
            bool unified = uf.unify(edge.second.first, edge.second.second);
            if (unified) spanning_tree_cost += edge.first;
            if (uf.num_components == 1) return spanning_tree_cost;
        }
    }

    return spanning_tree_cost;
}

int main() {
    int galleries;
    cin >> galleries;

    vector<pair<int, pair<int, int>>> space;
    while (galleries--) {
        int origin, destine, weight;
        cin >> origin >> destine >> weight;
        space.emplace_back(weight, make_pair(origin-1, destine-1));
    }

    int minimum_spanning_tree = build_spanning_tree(space);
    int maximum_spanning_tree = build_spanning_tree(space, true);

    cout << maximum_spanning_tree << endl << minimum_spanning_tree << endl;

    return 0;
}
