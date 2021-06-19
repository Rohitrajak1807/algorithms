//
// Created on 6/19/21.
//
#include <JarnikPrim.h>

MSTResult::MSTResult(std::vector<Edge> &mst, int32_t cost) : mst(mst), cost(cost) {}

MSTResult::MSTResult(std::vector<Edge> &&mst, int32_t cost) : mst(mst), cost(cost) {}

Edge::Edge(int32_t from, int32_t to, int32_t weight) : from(from), to(to), weight(weight) {}

struct Compare {
	bool operator()(const Edge &a, const Edge &b) {
		return a.weight > b.weight;
	}
};

void add_edges(const std::vector<std::vector<Edge>> &g, int32_t idx, std::vector<bool> &visited,
               std::priority_queue<Edge, std::vector<Edge>, Compare> &pq) {
	visited[idx] = true;
	for (auto &edge: g[idx]) {
		if (!visited[edge.to]) {
			pq.emplace(edge);
		}
	}
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