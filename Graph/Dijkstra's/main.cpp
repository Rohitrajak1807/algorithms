#include <iostream>
#include <queue>
#include <vector>

//A lazy implementation of Dijkstra's algorithm. It uses a priority queue.
//This algorithm fails on -ve edge weights
struct Edge {
    int to, weight;

    Edge(int to, int weight) : to(to), weight(weight) {}
};

struct Compare {
    bool operator()(const Edge &a, const Edge &b) {
        return a.weight > b.weight;
    }
};

std::vector<std::pair<int, int>> dijkstra_lazy(const std::vector<std::vector<Edge>> &graph, int start_node);

void print_path(const std::vector<std::pair<int, int>> &path, int dest) {
    if (path[dest].second == -1)
        return;
    print_path(path, path[dest].second);
    std::cout << path[dest].second;

}

int main() {
    std::vector<std::vector<Edge>> graph(5);
    graph[0].emplace_back(1, 4);
    graph[0].emplace_back(2, 1);
    graph[1].emplace_back(3, 1);
    graph[2].emplace_back(1, 2);
    graph[2].emplace_back(3, 5);
    graph[3].emplace_back(4, 3);
    std::vector<std::pair<int, int>> paths = dijkstra_lazy(graph, 0);
    for (auto &i : paths)
        std::cout << i.first << '\t' << i.second << std::endl;
    print_path(paths, 4);
    return 0;
}

std::vector<std::pair<int, int>> dijkstra_lazy(const std::vector<std::vector<Edge>> &graph, int start_node) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::pair<int, int>> paths(5, {INT32_MAX, -1});
    std::priority_queue<Edge, std::vector<Edge>, Compare> pq;
    pq.emplace(0, 0);
    paths[start_node].first = 0;
    while (!pq.empty()) {
        const Edge curr_node = pq.top();
        visited[curr_node.to] = true;
        pq.pop();
        if (paths[curr_node.to].first < curr_node.weight)
            continue;
        for (auto &adj_node : graph[curr_node.to]) {
            if (visited[adj_node.to])
                continue;
            int new_dist = paths[curr_node.to].first + adj_node.weight;
            if (new_dist < paths[adj_node.to].first) {
                paths[adj_node.to].first = new_dist;
                paths[adj_node.to].second = curr_node.to;
                pq.push(adj_node);
            }
        }
    }
    return paths;
}
