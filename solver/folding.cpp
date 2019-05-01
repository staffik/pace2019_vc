#include <cassert>

#include "folding.h"
#include "graph.h"
#include "solve.h"
#include "vc.h"

extern VC NO_instance;

int find_fold_2deg(const Graph& G){
    int u, w, v;
    for(const auto& x: G) {
        u = x.first;
        if(G.at(u).size != 2) {
            continue;
        }
        const auto& it = G.at(u).cbegin();
        v = *it;
        ++it;
        w = *it;
        if(G.at(v).find(w) == G.at(v).cend()) {
            return u;
        }
    }
    return -1;
}

VC fold_2deg(const Graph& G, int k, int node) {
    // ensure deg(node) == 2
    assert(G.at(node).size() == 2);
    // (node, v), (node, w) in E(G)
    // ensure (v, w) not in E(G)
    auto it = G.at(node).cbegin();
    int v = *it;
    ++it;
    int w = *it;
    int up = node;
    Graph Gp = G;
    std::vector<int> neighs;
    for(const auto& neigh: G.at(w)) {
        neighs.push_back(neigh);
    }
    for(const auto& neigh: G.at(v)) {
        neighs.push_back(neigh);
    }
    remove_vertices(Gp, {node, v, w});
    for(const auto& neigh: neighs) {
        Gp[up].insert(neigh);
        Gp[neigh].insert(up);
    }
    // return {};
    auto sol = solve(Gp, k-1);
    // check if produced a solution
    if(sol != NO_instance) {
        // if up in solution

        // if(sol.find(up) != sol.cend()) {
        //     sol.erase(up);
        //     sol.insert(v);
        //     sol.insert(w);
        // } else {
        //     sol.insert(node);
        // }

        return sol;
    } else {
        return NO_instance;
    }
}
