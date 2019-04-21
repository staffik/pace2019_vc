#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>

// typedef moved due to cyclical includes breaking everything
typedef std::unordered_set<int> VC;
typedef std::unordered_map<int, std::unordered_set<int> > Graph;


struct ExtGraph {
	ExtGraph(const Graph &G);

	Graph G;
	int n; // number of nodes
	int m; // number of edges
	std::map<int, std::unordered_set<int>> deg_2_nodes;

	void verify();
	int max_deg();
	int highest_degree_node();

	void remove_single_vertex(Graph::value_type &u);
	void add_single_vertex(Graph::value_type &u);

	void remove_vertices(Graph::value_type &u, std::vector<Graph::value_type> &neighbors);
	void add_vertices(std::vector<Graph::value_type> &neighbors);

};

size_t max_deg(const Graph&);
Graph induced_subgraph(const Graph&, const std::unordered_set<int>&);
std::ostream& operator<<(std::ostream&, const Graph&);

void remove_single_vertex(Graph &G, Graph::value_type &u);
void add_single_vertex(Graph &G, Graph::value_type &u);

void remove_vertices(Graph &G, Graph::value_type &u,
                    std::vector<Graph::value_type> &neighbors);
void add_vertices(Graph &G, std::vector<Graph::value_type> &neighbors);
void remove_vertices(Graph& G, const std::unordered_set<int> &vertices);

Graph difference(Graph G, std::unordered_set<int> to_remove);
Graph get_connected_component(const Graph& G, int node);
int connected_components(const Graph &G, std::vector<Graph> &CCs);
int remove_loops(Graph &G);
int number_of_edges(const Graph &G);
int highest_degree_vertex(const Graph &G);

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
