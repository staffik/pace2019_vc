#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::unordered_map<int, std::unordered_set<int>> Graph;
size_t max_deg(const Graph&);
Graph induced_subgraph(const Graph&, const std::unordered_set<int>&);

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
