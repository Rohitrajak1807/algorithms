//
// Created on 6/19/21.
//

#ifndef JARNIKPRIMMST_JARNIKPRIM_H
#define JARNIKPRIMMST_JARNIKPRIM_H

#include <vector>
#include <queue>
#include <limits>

struct Edge {
	int32_t from;
	int32_t to;
	int32_t weight;

	Edge(int32_t from, int32_t to, int32_t weight);

};

struct MSTResult {
	std::vector<Edge> mst;
	int32_t cost;

	MSTResult(std::vector<Edge> &mst, int32_t cost);
	MSTResult(std::vector<Edge> &&mst, int32_t cost);
};

MSTResult lazy_jarnik_prim(std::vector<std::vector<Edge>> &g, int32_t start = 0);

#endif //JARNIKPRIMMST_JARNIKPRIM_H
