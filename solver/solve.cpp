#include <assert.h>
#include <iostream>

#include "graph.h"
#include "kernel_2k.h"
#include "vc.h"
#include "folding.h"

int solve(ExtGraph &G);

bool solve(ExtGraph &G, int k) {
	if(k<0)
		return false;

	if(k >= G.n)
		return true;

	if(k * G.max_deg() < G.m)
		return false;
		
	//std::cerr << G.n << " " << G.m << " " << G.max_deg() << " "<< k << std::endl;

	auto u = *(G.G.find(G.highest_degree_node()));

	// branch on u
	G.remove_single_vertex(u);
	bool solved = solve(G, k-1);
	G.add_single_vertex(u);
	if(solved)
		return true;

	// branch on N[u]
	std::vector<Graph::value_type> neighbors;
	G.remove_vertices(u, neighbors);
	solved = solve(G, k - u.second.size());
	G.add_vertices(neighbors);
	return solved;
}

int dummy_cnt;
// Solve the instance, assume G is connected
int solve(ExtGraph &G) {
	bool first_call = (dummy_cnt==0);
	++dummy_cnt;

	int ti = time(NULL);
	// Invariant: min_K <= VC_opt(G) <= max_K
	int min_K=-1, mid_K, max_K=G.n/2-23;
	while(min_K + 1< max_K) {
		mid_K = (min_K + max_K)/2;

		if(first_call)
			std::cerr<<"Solving for "<<mid_K<<std::endl;

		if(solve(G, mid_K))
			max_K = mid_K;
		else
			min_K = mid_K;
	}
	std::cerr << "Solved in "<<(int)time(NULL)-ti<<std::endl;

	return max_K;
}

int do_solve(Graph &G) {
	int res = remove_loops(G);
	ExtGraph XG(G);
	return res + solve(XG);
}
