#include <assert.h>
#include <iostream>

#include "graph.h"
#include "io.h"
#include "kernel_2k.h"
#include "vc.h"

#define DBG(code) code

VC solve(Graph G, int k) {
	if(k<0)
		return NO_instance;
	
	VC partSol;

	// remove vertices with degree > k
	remove_high_deg_nodes(G, k, partSol);

	// max_deg(G) <= k

	if(k * max_deg(G) < number_of_edges(G))
		return NO_instance;

	// k * max_deg(G) >= |E(G)|
	
	// check if G has multiple connected components
	std::vector<Graph> CCs;
	if(connected_components(G, CCs) > 1) {
		std::vector<VC> subproblems_solution(CCs.size());
		for(int i=0; i<CCs.size(); ++i) {
			subproblems_solution[i] = solve(CCs[i], k);
			if(invalid(subproblems_solution[i]))
				return NO_instance;
			k -= subproblems_solution[i].size();
		}
		return merge_VCs(partSol, merge_VCs(subproblems_solution));
	}

	// G is connected, and 2 <= degree <= k, and k * max_deg(G) >= |E(G)|

	// Branching

	int u = highest_degree_vertex(G);

	// branch on u
	auto res = solve(G-u, k-1);
	if(valid(res))
		return merge_VCs(partSol, res);

	// branch on N[u]
	auto Nu = G[u];
	res = solve(G - Nu, k - Nu.size());
	if(valid(res))
		return merge_VCs(partSol, res);
}

// Solve the instance
VC solve(Graph G) {
	// check if G has multiple connected components
	std::vector<Graph> CCs;
	if(connected_components(G, CCs) > 1) {
		std::vector<VC> subproblems_solution(CCs.size());
		for(int i=0; i<CCs.size(); ++i) {
			subproblems_solution[i] = solve(CCs[i]);
		}
		return merge_VCs(subproblems_solution);
	}

	// G is connected

	VC partSol;

	remove_leaves(G, partSol);

	// G is cyclic, and min_deg(G) >= 2
	
	if(max_deg(G) <= 2)
		return merge_VCs(partSol, solve_deg2(G));

	// max_deg(G) >= 3

	// Invariant: min_K < VC_opt(G) <= max_K
	int min_K=0, mid_K, max_K=G.size();
	while(min_K + 1 < max_K) {
		mid_K = (min_K + max_K)/2;
		auto res = solve(G, mid_K);
		if(valid(res))
			max_K = mid_K;
		else
			min_K = mid_K;
	}
	return merge_VCs(partSol, solve(G, max_K));
}

int main() {
	// Read the input
	int n;
	Graph G;
    std::tie(n, G) = read_input();

	// Solve the instance
	VC solution;
	remove_loops(G, solution);
	auto partSol = solve(G);
	solution = merge_VCs(solution, partSol);

	// Write the output
    write_output(n, solution);

    return 0;
}
