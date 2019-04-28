#ifndef HOPCROFT_CARP_H
#define HOPCROFT_CARP_H

#include <vector>

#include "graph.h"

struct hopcroft_carp {
	using vi = std::vector<int>

	// BG as bipartite graph, each v -> v1 u v2
	hopcroft_carp(GraphAdj BG);

	// minimum vertex cover of this bipartite graph
	std::pair<vi, vi> vc;

private:
	int n, m;
	vi pairU, pairV, dist;
	vector<bool> vis[2];

	bool bfs();
	bool dfs();
	void alternate();

	calculateMaximumMatching();
	calculateVertexCover();
}

#endif // HOPCROFT_CARP_H
