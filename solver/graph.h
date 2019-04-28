#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <vector>

struct Graph {
	using vi = std::unordered_set<int>;

	int n;
	std::vector<vi> adj;
	
	void init(int N);
	vi& operator[](int idx);
	unsigned size();
};

struct GraphAdj {
	using vi = std::vector<int>;

	GraphAdj(const Graph &G);

	int n;
	std::vector<vi> adj;
};

#endif // GRAPH_H
