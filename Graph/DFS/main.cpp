#include <iostream>
#include <unordered_map>
#include <vector>

struct Edge {
    int32_t from;
    int32_t to;

    Edge(int32_t from, int32_t to) : from(from), to(to) {}
};

std::pair<std::vector<int32_t>, int64_t> dfs(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start);

int64_t dfs_impl(const std::unordered_map<int32_t, std::vector<Edge>>& g, int32_t  curr_vertex, std::vector<bool> &visited, std::vector<int32_t> &path);

int32_t main() {
    std::unordered_map<int32_t, std::vector<Edge>> g = {
            {0, {
                        Edge(0,1),
                        Edge(0,9),
                }},
            {1, {
                        Edge(1, 8),
                        Edge(1, 0)
                }},
            {2, {
                        Edge(2, 3)
                }},
            {3, {
                        Edge(3, 2),
                        Edge(3, 4),
                        Edge(3, 5),
                        Edge(3, 7),
                }},
            {4, {
                        Edge(4, 3)
                }},
            {5, {
                        Edge(5, 3),
                        Edge(5, 6)
                }},
            {6, {
                        Edge(6, 5),
                        Edge(6, 7),
                }},
            {7, {
                        Edge(7, 3),
                        Edge(7, 6),
                        Edge(7, 8),
                }},
            {8, {
                        Edge(8, 1),
                        Edge(8, 7),
                        Edge(8, 9)
                }},
            {9, {
                        Edge(9, 0),
                        Edge(9, 8),
                }}
    };
    auto res = dfs(g, 2);
    std::cout << res.second << '\n';
    for(int32_t& i : res.first)
        std::cout << i << '\t';
    return 0;
}

std::pair<std::vector<int32_t>, int64_t> dfs(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start) {
    size_t n = g.size();
    std::vector<bool> visited(n, false);
    std::vector<int32_t> path;
    path.reserve(n);
    return std::pair<std::vector<int32_t>, int64_t>(path, dfs_impl(g, start, visited, path));
}

int64_t dfs_impl(const std::unordered_map<int32_t, std::vector<Edge>>& g, int32_t  curr_vertex, std::vector<bool> &visited, std::vector<int32_t> &path) {
    if(visited[curr_vertex])
        return 0;
    visited[curr_vertex] = true;
    path.emplace_back(curr_vertex);
    int64_t count = 1;
    auto& neighbours = g.at(curr_vertex);
    for(auto& neighbour : neighbours) {
        count += dfs_impl(g, neighbour.to, visited, path);
        std::cout << neighbour.from << ", " << neighbour.to << '\n';
    }
    return count;
}