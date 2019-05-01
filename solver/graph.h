#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::unordered_map<int, std::unordered_set<int> > Graph;
size_t max_deg(const Graph&);
Graph induced_subgraph(const Graph&, const std::unordered_set<int>&);
std::ostream& operator<<(std::ostream&, const Graph&);

void remove_single_vertex(Graph &G, int u);
void remove_vertices(Graph& G, std::unordered_set<int> vertices);
Graph difference(Graph G, std::unordered_set<int> to_remove);
std::unordered_set<int> get_connected_component(const Graph& G, int node);
std::vector<std::unordered_set<int> > get_connected_components(const Graph&);

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
