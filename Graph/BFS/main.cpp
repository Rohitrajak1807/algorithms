#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

//included for test drive xD
#include <ranges>

struct Edge {
    int32_t from;
    int32_t to;

    Edge(int32_t from, int32_t to) : from(from), to(to) {}
    Edge(Edge &&E)  noexcept : from(E.from), to(E.to) {}
};

std::vector<int32_t> bfs(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start, int32_t end);

std::vector<int32_t> bfs_impl(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start);

std::vector<int32_t> reconstruct_path(const std::vector<int32_t> &prev, int32_t end);

int main() {
    std::unordered_map<int32_t, std::vector<Edge>> g{
            {0, {
                        {0, 1},
                        {0, 9},
                }},
            {1, {
                        {1, 8},
                        {1, 0}
                }},
            {2, {
                        {2, 3}
                }},
            {3, {
                        {3, 2},
                        {3, 4},
                        {3, 5},
                        {3, 7},
                }},
            {4, {
                        {4, 3}
                }},
            {5, {
                        {5, 3},
                        {5, 6}
                }},
            {6, {
                        {6, 5},
                        {6, 7},
                }},
            {7, {
                        {7, 3},
                        {7, 6},
                        {7, 8},
                }},
            {8, {
                        {8, 1},
                        {8, 7},
                        {8, 9}
                }},
            {9, {
                        {9, 0},
                        {9, 8},
                }}
    };
    auto res = bfs(g, 0, 4);
    for (int32_t const &i : res | std::views::reverse)
        std::cout << i << '\t';
    return 0;
}

std::vector<int32_t> bfs(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start, int32_t end) {
    auto prev = bfs_impl(g, start);
    return reconstruct_path(prev, end);
}

std::vector<int32_t> bfs_impl(const std::unordered_map<int32_t, std::vector<Edge>> &g, int32_t start) {
    size_t n = g.size();
    std::vector<bool> visited(n, false);
    std::vector<int32_t> prev(n, -1);
    std::queue<int32_t> q;

    visited[start] = true;
    q.emplace(start);
    while (!q.empty()) {
        int32_t curr_node = q.front();
        q.pop();
        const std::vector<Edge> &neighbours = g.at(curr_node);
        for (auto &neighbour : neighbours) {
            if (visited[neighbour.to])
                continue;

            q.emplace(neighbour.to);
            visited[neighbour.to] = true;
            prev[neighbour.to] = neighbour.from;
        }
    }
    return prev;
}

std::vector<int32_t> reconstruct_path(const std::vector<int32_t> &prev, int32_t end) {
    std::vector<int32_t> path;
    path.reserve(prev.size());
    for (int32_t at = end; at != -1; at = prev[at])
        path.emplace_back(at);
    return path;
}