#include <iostream>
#include <JarnikPrim.h>

std::vector<std::vector<Edge>> make_adj_list(const std::vector<Edge> &edges, size_t vertices);

std::vector<int32_t> reconstruct_tour(const std::vector<std::vector<Edge>>& graph, int32_t start = 0);

void dfs_impl(const std::vector<std::vector<Edge>> &graph, int32_t curr_node, std::vector<bool> &visited, std::vector<int32_t> &path);

int main() {
	std::vector<std::vector<Edge>> g = {
			{Edge(0, 1, 10), Edge(0, 2, 15), Edge(0, 3, 40), Edge(0, 4, 20)},
			{Edge(1, 0, 10), Edge(1, 2, 35), Edge(1, 3, 15), Edge(1, 4, 12)},
			{Edge(2, 0, 15), Edge(2, 1, 35), Edge(2, 3, 10), Edge(2, 4, 25)},
			{Edge(3, 0, 40), Edge(3, 1, 15), Edge(3, 2, 10), Edge(3, 4, 30)},
			{Edge(4, 0, 20), Edge(4, 1, 12), Edge(4, 2, 25), Edge(4, 3, 30)},
	};
	int32_t start = 0;
	auto&& [edges, cost] = lazy_jarnik_prim(g, start);
	std::vector<std::vector<Edge>> g_out = make_adj_list(edges, g.size());
	auto&& path = reconstruct_tour(g_out);
	for(int32_t& p : path) {
		std::cout << p << '\t';
	}
    return 0;
}

std::vector<std::vector<Edge>> make_adj_list(const std::vector<Edge> &edges, size_t vertices) {
	std::vector<std::vector<Edge>> graph(vertices);
	for (const Edge& edge : edges) {
		graph[edge.from].emplace_back(edge);
	}
	return graph;
}

std::vector<int32_t> reconstruct_tour(const std::vector<std::vector<Edge>>& graph, int32_t start) {
	std::vector<bool> visited(graph.size(), false);
	std::vector<int32_t> path;
	path.reserve(graph.size());
	dfs_impl(graph, start, visited, path);
	path.emplace_back(start);
	return path;
}

void dfs_impl(const std::vector<std::vector<Edge>> &graph, int32_t curr_node, std::vector<bool> &visited, std::vector<int32_t> &path) {
	if(visited[curr_node])
		return;
	visited[curr_node] = true;
	path.emplace_back(curr_node);
	auto& neighbours = graph[curr_node];
	for(auto &neighbour : neighbours) {
		dfs_impl(graph, neighbour.to, visited, path);
	}
}
