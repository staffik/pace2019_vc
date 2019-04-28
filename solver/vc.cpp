#include<iostream>
#include<map>
#include<set>
#include<tuple>
#include<unordered_map>
#include<unordered_set>

#include "vc.h"

bool successfull(const VC &res) {
	// The graph is empty and K >= 0
	return std::get<0>(res).empty() && std::get<1>(res)>=0;
}

VC remove_high_deg_nodes(VC vc) {
    Graph G;
    int k;
    std::vector<int> partial_solution;
    std::tie(G, k, partial_solution) = vc;
    // locate the vertices with deg > k, remove all the edges between them and
    // the rest of the graph and return all those vertices. method creates a
    // copy of the input graph

    // node to degree mapping
    std::unordered_map<int, int> node_deg;
    // degree to set of nodes mapping
    std::map<int, std::unordered_set<int>> deg_node;

    int deg;
    for(size_t i = 0; i < G.size(); i++) {
        deg = G[i].size();
        node_deg[i] = deg;
        deg_node[deg].insert(i);
    }

    std::map<int, std::unordered_set<int>>::reverse_iterator deg_node_it;
    int neigh_deg;

    while(true) {
        deg_node_it = deg_node.rbegin();

        deg = deg_node_it->first;
        if(deg <= k || k < 0) {
            break;
        }

        const auto& nodes = deg_node_it->second;
        const auto node = *nodes.begin();
        partial_solution.push_back(node);
        k--;

        // iterate neighbours
        const auto neighs = G[node];
        for(auto neigh: neighs) {
            // remove edges
            G[node].erase(neigh);
            G[neigh].erase(node);

            neigh_deg = node_deg[neigh];
            // decrement neigh deg
            node_deg[neigh]--;
            deg_node[neigh_deg].erase(neigh);
            if(deg_node[neigh_deg].empty()) {
                deg_node.erase(neigh_deg);
            }
            deg_node[neigh_deg-1].insert(neigh);
        }

        node_deg[node] = 0;
        deg_node[deg].erase(node);
        if(deg_node[deg].empty()) {
            deg_node.erase(deg);
        }
        deg_node[0].insert(node);
    }

    return {G, k, partial_solution};
}
