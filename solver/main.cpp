#include<iostream>

#include "graph.h"
#include "io.h"
#include "lp.h"
#include "vc.h"

VC solve(VC partSol) {
    auto res = remove_high_deg_nodes(partSol);
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
	// beg <= VC_opt < end
	int beg = 0, mid, end = max_deg(G)+1;
	while(beg+1<end) {
		mid = (beg+end)/2;
		auto res = solve({G, 5, {}});
		if (std::get<1>(res) >= 0)
			beg = mid;
		else
			end = mid;
	}
	auto res = solve({G, beg, {}});



	// Write output
    auto partial_solution = std::get<2>(res);
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
