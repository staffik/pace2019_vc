#include<iostream>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>

typedef std::vector<std::unordered_set<int>> Graph;

Graph preprocess(Graph G, int k) {
    std::unordered_map<int, int> node_deg;
    std::map<int, std::set<int>> deg_node;

    int deg;
    for(size_t i = 0; i < G.size(); i++) {
        deg = G[i].size();
        node_deg[i] = deg;
        deg_node[deg].insert(i);

        if(deg > k) {
            std::cout << i << " " << deg << std::endl;
        }
    }
    return G;
}
