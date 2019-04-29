#include<cassert>
#include<iostream>
#include<map>
#include<set>
#include<tuple>
#include<unordered_map>
#include<unordered_set>

#include "vc.h"

std::ostream& operator<<(std::ostream& ostr, const VC& sol) {
    ostr << "k: " << std::get<1>(sol) << "\n";
    ostr << std::get<0>(sol);
    ostr << "sol: ";
    bool first = true;
    for(const auto el: std::get<2>(sol)) {
        if(!first) {
            ostr << ", ";
        }
        first = false;
        ostr << el;
    }
    return ostr;
}

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
    for(auto& it : G) {
		int u = it.first;
        deg = it.second.size();
        node_deg[u] = deg;
        deg_node[deg].insert(u);
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

        G.erase(node);
        node_deg[node] = 0;
        deg_node[deg].erase(node);
        if(deg_node[deg].empty()) {
            deg_node.erase(deg);
        }
        deg_node[0].insert(node);
    }

    return {G, k, partial_solution};
}

VC solve_deg2(VC vc) {
    Graph G;
    int k;
    std::vector<int> partial_solution;
    std::tie(G, k, partial_solution) = vc;
    // solve the graph with deg <= 2. method doesn't modify the input graph
    assert(max_deg(G) <= 2);

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

    while(true) {
        // if there is a leaf add it's neighbour to partial solution and continue
        if(deg_node[1].size()) {
            auto node = *deg_node.at(1).begin();
            auto neigh = *G[node].begin();
            // remove all the edges from the neighbour
            auto vertices = G.at(neigh);
            for(auto x: vertices) {
                G[neigh].erase(x);
                G[x].erase(neigh);

                auto x_deg = node_deg[x];
                deg_node[x_deg].erase(x);
                x_deg--;
                deg_node[x_deg].insert(x);

                auto neigh_deg = node_deg[neigh];
                deg_node[neigh_deg].erase(neigh);
                neigh_deg--;
                deg_node[neigh_deg].insert(neigh);
            }
            G.erase(node);
            G.erase(neigh);
            partial_solution.push_back(neigh);
            k--;
        }
        // no leafs, just cycles
        else if(deg_node[2].size()) {
            auto node = *deg_node.at(2).begin();
            std::vector<int> path = {node};
            int prev, curr = *G[node].begin(), next;
            while(true) {
                prev = path[path.size()-1];
                path.push_back(curr);
                for(auto x: G[curr]) {
                    if(x != prev) {
                        next = x;
                        break;
                    }
                }
                if(next == node) {
                    break;
                }
                curr = next;
            }
            int take = true;
            for(const auto x: path) {
                if(take) {
                    partial_solution.push_back(x);
                    k--;
                }
                take ^= true;
            }
            // remove all vertices on path and adjust degrees
            for(const auto x: path) {
                G.erase(x);
                node_deg.erase(x);
                deg_node[2].erase(x);
            }
        }
        else {
            break;
        }
    }

    return {G, k, partial_solution};
}

VC remove_leaves(VC vc) {
    Graph G;
    int k;
    std::vector<int> partial_solution;
    std::tie(G, k, partial_solution) = vc;

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

    while(true) {
        // if there is a leaf add it's neighbour to partial solution and continue
        if(deg_node[1].size()) {
            auto node = *deg_node.at(1).begin();
            auto neigh = *G[node].begin();
            // remove all the edges from the neighbour
            auto vertices = G.at(neigh);
            for(auto x: vertices) {
                G[neigh].erase(x);
                G[x].erase(neigh);

                auto x_deg = node_deg[x];
                deg_node[x_deg].erase(x);
                x_deg--;
                deg_node[x_deg].insert(x);
                node_deg[x] = x_deg;

                auto neigh_deg = node_deg[neigh];
                deg_node[neigh_deg].erase(neigh);
                neigh_deg--;
                deg_node[neigh_deg].insert(neigh);
                node_deg[neigh] = neigh_deg;
            }
            G.erase(node);
            G.erase(neigh);
            partial_solution.push_back(neigh);
            k--;
        }
        else {
            break;
        }
    }
    //std::cout << G.size() << "\n";
    std::vector<int> empty_nodes;
    for(const auto& x: G) {
        if(x.second.empty()) {
            empty_nodes.push_back(x.first);
        }
    }
    for(const auto x: empty_nodes) {
        G.erase(x);
    }
    //std::cout << G.size() << "\n";

    return {G, k, partial_solution};
}
