#include "kernel_2k.h"

#include <assert.h>
#include <iostream>
#include <unordered_set>

#include "graph.h"
#include "hopcroft_carp.h"

#define DBG(code) code


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

// apply LPVC OneHalf reduction -> |G'(V)| <= 2k
VC kernel_2k_reduction(const VC &partVC) {
	const Graph &G = std::get<0>(partVC);
	if(G.empty()) return partVC;

	int old_K = std::get<1>(partVC);
	const auto& oldPartSol = std::get<2>(partVC);

	std::unordered_set<int> remaining;
	std::vector<int> newPartSol;

	std::tie(remaining, newPartSol) = get_half_ones(G);
	auto induced = induced_subgraph(G, remaining);
	int new_K = old_K - newPartSol.size();

	newPartSol.insert(newPartSol.end(), oldPartSol.begin(), oldPartSol.end());

/*
	if(induced.size() > 2 * new_K) {
		new_K = -1; // 2*K < |LPVC_opt| <= |VC_opt|
	}
	*/
	return std::make_tuple(induced, new_K, newPartSol);
}

int double_all_half_solution_size(const VC &LPVC) {
	return std::get<0>(LPVC).size() + 2*std::get<2>(LPVC).size();
}

bool all_half_negative_RR(const VC &vc) {
	return std::get<0>(vc).size() > 2*std::get<1>(vc);
}

VC all_half_reduction(const VC &partVC) {
	auto res = kernel_2k_reduction(partVC);
	if(all_half_negative_RR(res)) {
		std::get<1>(res) = -1;
		return res;
	}

	std::vector<int> vertices;
	for(auto &it : std::get<0>(res)) vertices.push_back(it.first);
	for(auto u : vertices) if(std::get<0>(res).find(u) != std::get<0>(res).end()) {
		VC tmp = res;
		remove_single_vertex(std::get<0>(tmp), u);
		tmp = kernel_2k_reduction(tmp);
		if(double_all_half_solution_size(tmp) <= double_all_half_solution_size(res)-2) {
			remove_single_vertex(std::get<0>(res), u);
			std::get<1>(res)--;
			std::get<2>(res).push_back(u);
		
			if(all_half_negative_RR(res)) {
				std::get<1>(res) = -1;
				return res;
			}
		}
	}

	return res;
}
