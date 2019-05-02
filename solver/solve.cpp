#include <assert.h>
#include <iostream>

#include "graph.h"
#include "kernel_2k.h"
#include "vc.h"
#include "folding.h"

VC solve(Graph G, int min_K, int max_K);

VC solve(Graph G, int k) {
	if(k<0)
		return NO_instance;

	VC partSol;

	// remove vertices with degree > k
	remove_high_deg_nodes(G, k, partSol);

	if(k<0)
		return NO_instance;

	if(G.empty())
		return YES_instance;

	// 2 deg folding
	int node = find_fold_2deg(G);
	if(node > 0) {
		return fold_2deg(G, k, node);
	}

	// max_deg(G) <= k

	if(k * max_deg(G) < number_of_edges(G))
		return NO_instance;

	// k * max_deg(G) >= |E(G)|

	// check if G has multiple connected components
	std::vector<Graph> CCs;
	if(connected_components(G, CCs) > 1) {
		std::vector<VC> subproblems_solution(CCs.size());
		for(int i=0; i<CCs.size(); ++i) {
			//subproblems_solution[i] = solve(CCs[i], k);
			subproblems_solution[i] = solve(CCs[i], 0, k);
			if(invalid(subproblems_solution[i]))
				return NO_instance;
			k -= subproblems_solution[i].size();
		}
		return merge_VCs(partSol, merge_VCs(subproblems_solution));
	}

	// G is connected, and 2 <= degree <= k, and k * max_deg(G) >= |E(G)|


	// Fold 2deg
	/*
	int v = find_fold_2deg(G);
	if(v!=-1) {
		auto sol = fold_2deg(G, k, v);
		if(valid(sol))
			return merge_VCs(partSol, sol);
		else
			return NO_instance;
	}
	*/

	// Branching

	int u = highest_degree_vertex(G);

	// branch on u
	auto res = solve(G-u, k-1);
	if(valid(res)) {
		partSol = merge_VCs(partSol, res);
		partSol.insert(u);
		return partSol;
	}

	// branch on N[u]
	auto Nu = G[u];
	res = solve(G - Nu, k - Nu.size());
	if(valid(res)) {
		partSol = merge_VCs(partSol, res);
		// partSol.insert(partSol.end(), Nu.begin(), Nu.end());
		std::copy(Nu.cbegin(), Nu.cend(), std::inserter(partSol, partSol.end()));
		return partSol;
	}
	else {
		return NO_instance;
	}
}

int dummy_cnt;
// Solve the instance, assume G is connected
VC solve(Graph G, int min_K, int max_K) {
	bool first_call = (dummy_cnt==0);
	++dummy_cnt;

	VC partSol;
	remove_leaves(G, partSol);

	// G is cyclic, and min_deg(G) >= 2

	if(max_deg(G) <= 2)
		return merge_VCs(partSol, solve_deg2(G));

	// max_deg(G) >= 3
	
	//kernel_2k_reduction(G, partSol);
	// Invariant: min_K <= VC_opt(G) <= max_K
	//min_K = std::max(min_K, (int)G.size()/2);
	//max_K = std::min(max_K, (int)G.size());
	int mid_K;
	while(min_K < max_K) {
		mid_K = (min_K + max_K - 1)/2;

		if(first_call)
			std::cerr<<"Solving for "<<mid_K<<std::endl;

		auto res = solve(G, mid_K);
		if(valid(res))
			max_K = mid_K;
		else
			min_K = mid_K+1;
	}

	return merge_VCs(partSol, solve(G, max_K));
}

VC do_solve(Graph G) {
	VC solution;
	remove_loops(G, solution);
	//kernel_2k_reduction(G, solution);
	//all_half_reduction(G, solution);

	std::vector<Graph> CCs;
	connected_components(G, CCs);
	for(int i=0; i<CCs.size(); ++i) {
		int n = CCs[i].size();
		solution = merge_VCs(solution, solve(CCs[i], n/2, n));
	}

	return solution;
}
