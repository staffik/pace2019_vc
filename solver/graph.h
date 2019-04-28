#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::unordered_map<int, std::unordered_set<int>> Graph;
size_t max_deg(const Graph&);
Graph induced_subgraph(const Graph&, const std::unordered_set<int>&);

void remove_single_vertex(Graph &G, int u);
Graph difference(Graph G, std::unordered_set<int> to_remove);

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
