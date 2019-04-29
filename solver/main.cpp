#include <assert.h>
#include <iostream>

#include "graph.h"
#include "io.h"
#include "kernel_2k.h"
#include "lp.h"
#include "vc.h"

#define DBG(code) code

VC tryBranch(const VC &partVC, std::unordered_set<int> vertices);

// The branching algorithm
VC branch(VC partVC) {
	const auto& G = std::get<0>(partVC);
	const auto& k = std::get<1>(partVC);
	const auto& partSol = std::get<2>(partVC);

	if(G.empty() || k<=0) return partVC;

	auto it = G.begin();
	auto firstBranch = tryBranch(partVC, {it->first});

	if(successfull(firstBranch))
		return firstBranch;

	// second branch
	return tryBranch(partVC, it->second);
}

VC tryBranch(const VC &partVC, std::unordered_set<int> vertices) {
	Graph reduced = difference(std::get<0>(partVC), vertices);

	int k = std::get<1>(partVC) - vertices.size();

	std::vector<int> partSol = std::get<2>(partVC);
	partSol.insert(partSol.end(), vertices.begin(), vertices.end());

	return branch(std::make_tuple(reduced, k, partSol));
}

VC solve(VC partVC) {
    auto res = remove_high_deg_nodes(partVC);
	res = kernel_2k_reduction(res);
	res = branch(res);
	return res;
}

int main() {
	// Init
    Graph G = read_input();

	/*
    std::cout << max_deg(G) << "\n";
    auto subG = induced_subgraph(G, {1, 3, 5, 7, 8});
    std::cout << max_deg(subG) << "\n";
	*/


	// Binary search
	// Invariant: beg <= |VC_opt| < end
	int beg = 0, mid, end = max_deg(G)+1;
	while(beg+1<end) {
		mid = (beg+end)/2;
		auto res = solve({G, mid, {}});
		if(successfull(res))
			beg = mid;
		else
			end = mid;
	}
	auto res = solve({G, beg, {}});

	// Write output

    auto partial_solution = std::get<2>(res);
	DBG(assert(partial_solution.size() == beg));
    std::cout << partial_solution.size() << "\n";
    if(partial_solution.size()) {
        for(const auto node: partial_solution) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    // write_output(5, {2, 4});
    return 0;
}
