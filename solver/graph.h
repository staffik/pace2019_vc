#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// typedef moved due to cyclical includes breaking everything
typedef std::unordered_set<int> VC;
typedef std::unordered_map<int, std::unordered_set<int> > Graph;

size_t max_deg(const Graph&);
Graph induced_subgraph(const Graph&, const std::unordered_set<int>&);
std::ostream& operator<<(std::ostream&, const Graph&);

void remove_single_vertex(Graph &G, int u);
void remove_vertices(Graph& G, const std::unordered_set<int> &vertices);
Graph difference(Graph G, std::unordered_set<int> to_remove);
Graph get_connected_component(const Graph& G, int node);
int connected_components(const Graph &G, std::vector<Graph> &CCs);
void remove_loops(Graph &G, VC &partSol);
int number_of_edges(const Graph &G);
int highest_degree_vertex(const Graph &G);

Graph operator-(Graph G, int u);
Graph operator-(Graph G, const std::unordered_set<int> & vertices);

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
