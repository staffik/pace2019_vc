#include "kernel_2k.h"

#include <assert.h>
#include <iostream>
#include <unordered_set>

#include "graph.h"
#include "hopcroft_carp.h"

#define DBG(code) code


// returns pair <V1/2, V1>
auto LPVC_solution(const Graph &G) {
	// bipartite version of G
	GraphAdj BG(G);

	// calculate VC in BG
	hopcroft_carp HC(BG);

	// recover LPVC solution for G
	std::vector<int> V1, V2;
	std::tie(V1, V2) = HC.vc;

	int n = BG.n;
	std::vector<int> V(n, 0);

	for(int i=0; i<V1.size(); ++i) {
		int v = V1[i]-1;
		V[v]++;
	}

	for(int i=0; i<V2.size(); ++i) {
		int v = V2[i]-1;
		V[v]++;
	}

	std::unordered_set<int> half;
	std::vector<int> ones;
	for(int v=0; v<n; ++v) {
		if(V[v] == 1)
			half.insert(v);
		else if(V[v]==2)
			ones.push_back(v);
	}

	return std::make_tuple(half, ones);
}

// apply LPVC OneHalf reduction
void kernel_2k_reduction(Graph &G, VC &partSol) {
	std::unordered_set<int> half_ones;
	std::vector<int> ones;

	std::tie(half_ones, ones) = LPVC_solution(G);
	G = induced_subgraph(G, half_ones);

	partSol.insert(partSol.end(), ones.begin(), ones.end());
}

void all_half_reduction(Graph &G, VC &partVC) {
	kernel_2k_reduction(G, partVC);

	// G is V1/2

	std::vector<int> vertices;
	for(auto &it : G)
		vertices.push_back(it.first);

	for(auto u : vertices) if(G.find(u) != G.end()) {
		Graph copy = G;
		std::vector<int> dummy;

		remove_single_vertex(copy, u);
		kernel_2k_reduction(copy, dummy);

		if(copy.size() + 2*dummy.size() <= G.size() - 2) {
			remove_single_vertex(G, u);
			partVC.push_back(u);
		}
	}
}
