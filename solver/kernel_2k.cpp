#include "kernel_2k.h"

#include <unordered_set>

#include "hopcroft_carp.h"


// returns pair of lists <do_not_get_to_solution, get_to_solution>
auto get_half_ones(const Graph &G) {
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


VC kernel_2k_reduction(const VC &partVC) {
	const Graph &G = std::get<0>(partVC);
	int old_K = std::get<1>(partVC);
	const auto& oldPartSol = std::get<2>(partVC);

	std::unordered_set<int> remaining;
	std::vector<int> newPartSol;
	
	std::tie(remaining, newPartSol) = get_half_ones(G);
	auto induced = induced_subgraph(G, remaining);
	int new_K = old_K - newPartSol.size();

	newPartSol.insert(newPartSol.end(), oldPartSol.begin(), oldPartSol.end());

	return std::make_tuple(induced, new_K, newPartSol);
}
