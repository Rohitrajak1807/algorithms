#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

struct Edge {
    int32_t from, to;

    Edge(int32_t from, int32_t to) : from(from), to(to) {}
};

std::vector<Edge> vertex_cover(const std::unordered_map<int32_t, std::vector<Edge>> &graph);

bool all_visited(const std::vector<bool> &visited);

ssize_t choose_vertex(const std::unordered_map<int32_t, std::vector<Edge>> &graph, const std::vector<bool> &visited);

int main() {
    std::unordered_map<int32_t, std::vector<Edge>> graph = {
            {0, {
                        Edge(0, 1),
                        Edge(0, 7)
                }},
            {1, {
                        Edge(1, 0),
                        Edge(1, 2)
                }},
            {2, {
                        Edge(2, 1),
                        Edge(2, 3),
                        Edge(2, 4)
                }},
            {3, {
                        Edge(3, 2),
                        Edge(3, 4),
                        Edge(3, 5),
                        Edge(3, 6),
                        Edge(3, 8),
                }},
            {4, {
                        Edge(4, 2),
                        Edge(4, 3),
                        Edge(4, 4),
                }},
            {5, {
                        Edge(5, 3),
                        Edge(5, 4)
                }},
            {6, {
                        Edge(6, 3),
                        Edge(6, 7),
                        Edge(6, 8),
                }},
            {7, {
                        Edge(7, 6),
                        Edge(7, 0),
                }},
            {8, {
                        Edge(8, 3),
                        Edge(8, 6),

                }}
    };
    auto edges = vertex_cover(graph);
    for (auto &e : edges) {
        std::cout << "From: " << e.from << ", " << "To: " << e.to << '\n';
    }
    return 0;
}

std::vector<Edge> vertex_cover(const std::unordered_map<int32_t, std::vector<Edge>> &graph) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<Edge> edges;
    while (!all_visited(visited)) {
        ssize_t curr_vertex = choose_vertex(graph, visited);
        const Edge &curr_edge = graph.at(curr_vertex)[0];
        for (auto edge : graph.at(curr_edge.from)) {
            visited[edge.to] = true;
        }
        for (auto &edge : graph.at(curr_edge.to)) {
            visited[edge.to] = true;
        }
        edges.emplace_back(curr_edge);
    }
    return edges;
}

inline bool all_visited(const std::vector<bool> &visited) {
    return std::accumulate(visited.begin(), visited.end(), true, [](bool a, bool b) {
        return a && b;
    });
}

ssize_t choose_vertex(const std::unordered_map<int32_t, std::vector<Edge>> &graph, const std::vector<bool> &visited) {
    ssize_t idx = -1;
    size_t max = 0;
    for (auto &vertex : graph) {
        if (!visited[vertex.first]) {
            if (max < vertex.second.size()) {
                idx = vertex.first;
                max = vertex.second.size();
            }
        }
    }
    return idx;
}