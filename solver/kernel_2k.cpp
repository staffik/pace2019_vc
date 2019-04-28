#include "kernel_2k.h"

#include "hopcroft_carp.h"

std::pair<vi, vi> kernel_2k_reduction(const Graph &G) {
	GraphAdj BG(G);
	hopcroft_carp HC(BG);

	vi V1, V2;
	std::tie(V1, V2) = HC.vc;

	int n = BG.n;
	vi V(n, 0);

	for(int i=0; i<V1.size(); ++i) {
		int v = V1[i]-1;
		V[v]++;
	}

	for(int i=0; i<V2.size(); ++i) {
		int v = V2[i]-1;
		V[v]++;
	}

	vi zeros, ones;
	for(int v=0; v<n; ++v) {
		if(V[v] == 0)
			zeros.push_back(v);
		else if(V[v] == 2)
			ones.push_back(v);
	}
	return std::make_pair(zeros, ones);
}

