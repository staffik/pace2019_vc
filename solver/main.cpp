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
	partVC = remove_leaves(partVC);
	const auto& G = std::get<0>(partVC);
	const auto& k = std::get<1>(partVC);
	const auto& partSol = std::get<2>(partVC);

	int m=0, m_deg=0;
	for(auto& u : G) {
		m += u.second.size();
		m_deg = std::max(m_deg, (int)u.second.size());
	}
	m /= 2;

	if(k * m_deg < m) return partVC;

	if(G.empty() || k<=0) return partVC;

	if(m_deg<=2) return solve_deg2(partVC);

	//std::cerr<<G.size()<<" "<<m<<" "<<m_deg<<" "<<k<<std::endl;

	// remove random vertex with the highest degree
	std::vector<Graph::const_iterator> nodes;
	for(Graph::const_iterator it=G.cbegin(); it!=G.end(); it++)
		if(it->second.size() == m_deg)
			nodes.push_back(it);
	auto it = nodes[rand()%nodes.size()];

	auto firstBranch = tryBranch(partVC, {it->first});

	if(successfull(firstBranch) || k < it->second.size())
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
	res = remove_leaves(res);
	res = kernel_2k_reduction(res);
	res = branch(res);
	return res;
}

int main() {
	// Init
	int n;
	Graph G;
    std::tie(n, G) = read_input();

	/*
    std::cout << max_deg(G) << "\n";
    auto subG = induced_subgraph(G, {1, 3, 5, 7, 8});
    std::cout << max_deg(subG) << "\n";
	*/


	// Binary search
	// Invariant: beg < |VC_opt| <= end
	int beg = -1, mid, end = n;
	while(beg+1<end) {
		mid = (beg+end)/2;
		std::cerr <<"Solving for k = "<<mid<<std::endl;
		auto res = solve({G, mid, {}});
		if(successfull(res))
			end = mid;
		else
			beg = mid;
	}
	auto res = solve({G, end, {}});

	// Write output

    auto partial_solution = std::get<2>(res);
	DBG(assert(partial_solution.size() == end));
	/*
    std::cout << partial_solution.size() << "\n";
    if(partial_solution.size()) {
        for(const auto node: partial_solution) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }
	*/

    write_output(n, partial_solution);
    return 0;
}
