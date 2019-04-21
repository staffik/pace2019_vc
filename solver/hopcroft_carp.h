#ifndef HOPCROFT_CARP_H
#define HOPCROFT_CARP_H

#include <vector>

#include "graph.h"

struct hopcroft_carp {
	using vi = std::vector<int>;

	// BG as bipartite graph, each v -> v1 u v2
	hopcroft_carp(const GraphAdj &BG);

	// minimum vertex cover of this bipartite graph
	std::pair<vi, vi> vc;
	// size of maximal matching for this bipartite graph
	int result;

private:
	const GraphAdj &BG;
	
	int n, m;
	vi pairU, pairV, dist;
	std::vector<bool> vis[2];

	bool bfs();
	bool dfs(int u);
	void alternate(int u);

	void calculateMaximumMatching();
	void calculateVertexCover();
};

#endif // HOPCROFT_CARP_H
