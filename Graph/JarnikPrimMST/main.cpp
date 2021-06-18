#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge {
	int32_t from;
	int32_t to;
	int32_t weight;

	Edge(int32_t from, int32_t to, int32_t weight) : from(from), to(to), weight(weight) {}
};

struct MSTResult {
	std::vector<Edge> mst;
	int32_t cost;
	MSTResult(std::vector<Edge>& mst, int32_t cost) : mst(mst), cost(cost) {}
	MSTResult(std::vector<Edge>&& mst, int32_t cost) : mst(mst), cost(cost) {}
};

struct Compare {
	bool operator()(const Edge &a, const Edge &b) {
		return a.weight > b.weight;
	}
};

void init_example_graph(std::vector<std::vector<Edge>> &g);

MSTResult lazy_jarnik_prim(std::vector<std::vector<Edge>> &g, int32_t start = 0);

void add_edges(const std::vector<std::vector<Edge>> &g, int32_t idx, std::vector<bool> &visited,
               std::priority_queue<Edge, std::vector<Edge>, Compare> &pq);

int main() {
	const size_t n = 8;
	std::vector<std::vector<Edge>> g(n);
	init_example_graph(g);
	auto [mst, cost] = lazy_jarnik_prim(g);
	for (auto &edge: mst) {
		std::cout << edge.from << '\t' << edge.to << '\t' << edge.weight << '\n';
	}
	std::cout << cost << '\n';
	return 0;
}

void init_example_graph(std::vector<std::vector<Edge>> &g) {
	g[0].emplace_back(0, 1, 10);
	g[0].emplace_back(0, 2, 1);
	g[0].emplace_back(0, 3, 4);

	g[1].emplace_back(1, 0, 10);
	g[1].emplace_back(1, 2, 3);
	g[1].emplace_back(1, 4, 0);

	g[2].emplace_back(2, 0, 1);
	g[2].emplace_back(2, 1, 3);
	g[2].emplace_back(2, 3, 2);
	g[2].emplace_back(2, 5, 8);

	g[3].emplace_back(3, 0, 4);
	g[3].emplace_back(3, 2, 2);
	g[3].emplace_back(3, 5, 2);
	g[3].emplace_back(3, 6, 7);

	g[4].emplace_back(4, 1, 0);
	g[4].emplace_back(4, 5, 1);
	g[4].emplace_back(4, 7, 8);

	g[5].emplace_back(5, 2, 8);
	g[5].emplace_back(5, 3, 2);
	g[5].emplace_back(5, 4, 1);
	g[5].emplace_back(5, 6, 6);
	g[5].emplace_back(5, 7, 9);

	g[6].emplace_back(6, 3, 7);
	g[6].emplace_back(6, 5, 6);
	g[6].emplace_back(6, 7, 12);

	g[7].emplace_back(7, 4, 8);
	g[7].emplace_back(7, 6, 12);
	g[7].emplace_back(7, 5, 9);
}

MSTResult lazy_jarnik_prim(std::vector<std::vector<Edge>> &g, int32_t start) {
	size_t req_edges = g.size() - 1;
	size_t edges = 0;
	int32_t cost = 0;
	std::vector<Edge> mst;
	std::priority_queue<Edge, std::vector<Edge>, Compare> pq;
	std::vector<bool> visited(g.size(), false);
	add_edges(g, start, visited, pq);

	while (!pq.empty() && edges != req_edges) {
		const Edge curr_edge = pq.top();
		pq.pop();
		const int32_t &idx = curr_edge.to;
		if (visited[curr_edge.to])
			continue;
		mst.emplace_back(curr_edge);
		edges++;
		cost += curr_edge.weight;
		add_edges(g, idx, visited, pq);
	}
	if (edges != req_edges) {
		return MSTResult(std::vector<Edge>{}, std::numeric_limits<int32_t>::infinity());
	}
	return MSTResult(mst, cost);
}

void add_edges(const std::vector<std::vector<Edge>> &g, int32_t idx, std::vector<bool> &visited,
               std::priority_queue<Edge, std::vector<Edge>, Compare> &pq) {
	visited[idx] = true;
	for (auto &edge: g[idx]) {
		if (!visited[edge.to]) {
			pq.emplace(edge);
		}
	}
}