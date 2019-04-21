#include <cassert>

#include "folding.h"
#include "graph.h"
#include "solve.h"
#include "vc.h"

int find_fold_2deg(const Graph& G){
    int u, w, v;
    for(const auto& x: G) {
        u = x.first;
        if(G.at(u).size() != 2) {
            continue;
        }
        auto it = G.at(u).cbegin();
        v = *it;
        ++it;
        w = *it;
        if(G.at(v).find(w) == G.at(v).cend()) {
            return u;
        }
    }
    return -1;
}

bool fold_2deg(const Graph& G, int k, int node) {
    // ensure deg(node) == 2
    assert(G.at(node).size() == 2);
    // (node, v), (node, w) in E(G)
    // ensure (v, w) not in E(G)
    auto it = *G.find(node);
	auto jt = it.second.cbegin();
    int v = *jt;
    ++jt;
    int w = *jt;
    assert(G.at(v).find(w) == G.at(v).end());
    int up = node;
    Graph Gp = G;
    std::vector<int> neighs;
    std::copy(G.at(w).cbegin(), G.at(w).cend(), std::inserter(neighs, neighs.end()));
    std::copy(G.at(v).cbegin(), G.at(v).cend(), std::inserter(neighs, neighs.end()));
	std::vector<Graph::value_type> vw;
    remove_vertices(Gp, it, vw);
    for(const auto& neigh: neighs) {
        if(neigh == node) {
            continue;
        }
        Gp[up].insert(neigh);
        Gp[neigh].insert(up);
	}
    
	ExtGraph XGp(Gp);
    return solve(XGp, k-1);
}
