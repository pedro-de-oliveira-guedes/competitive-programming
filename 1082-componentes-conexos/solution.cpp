#include <bits/stdc++.h>

std::set<char> dfs(
    std::map<char, std::vector<char>> graph,
    std::map<char, bool>* visited,
    char vertex
) {
    if (visited->at(vertex)) return {};
    else visited->at(vertex) = true;

    std::set<char> component = {vertex};
    for (const char& neighboor : graph[vertex]) {
        // component += (vertex + "," + dfs(graph, visited, neighboor));
        component.merge(dfs(graph, visited, neighboor));
    }

    return component;
}

std::vector<std::set<char>> get_connected_components(
    std::map<char, std::vector<char>> graph,
    int vertices_amount
) {
    std::map<char, bool> visited;
    std::vector<char> available_vertices;
    for (int i = 97; i < 97 + vertices_amount; i++) {
        visited.insert(std::make_pair((char) i, false));
        available_vertices.push_back((char) i);
    }

    std::vector<std::set<char>> connected_components;
    for (const char& vertex : available_vertices) {
        if (visited[vertex]) continue;
        else connected_components.push_back(dfs(graph, &visited, vertex));
    }

    return connected_components;
}

int main() {
    int test_cases_amount;
    std::cin >> test_cases_amount;
    std::vector<std::map<char, std::vector<char>>> test_cases(test_cases_amount);

    std::vector<std::vector<std::set<char>>> answers;
    for (int i = 0; i < test_cases_amount; i++) {
        int vertices, edges;
        std::cin >> vertices >> edges;
        
        // build graph
        for (int v = 97; v < 97 + vertices; v++) test_cases[i][(char) v] = {};
        while (edges--) {
            char v1, v2;
            std::cin >> v1 >> v2;

            test_cases[i][v1].push_back(v2);
            test_cases[i][v2].push_back(v1);
        }

        // check connected components
        std::vector<std::set<char>> connected_components = get_connected_components(
            test_cases[i],
            vertices
        );

        // store response
        answers.push_back(connected_components);
    }

    // print results
    for (int i = 0; i < test_cases_amount; i++) {
        std::cout << "Case #" << i+1 << ":" << std::endl;
        for (const std::set<char>& connected_component : answers[i]) {
            for (const char& vertex : connected_component) {
                std::cout << vertex << ",";
            }
            std::cout << std::endl;
        }
        std::cout << answers[i].size() << " connected components\n" << std::endl;
    }

    return 0;
}