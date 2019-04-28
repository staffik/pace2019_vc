#include "graph.h"
#include<algorithm>

size_t max_deg(const Graph& G) {
	size_t res = 0;
	for(auto x: G) {
		res = std::max(res, x.second.size());
	}
	return res;
}

Graph induced_subgraph(const Graph& G, const std::unordered_set<int>& vertices) {
	Graph induced;
	for(const auto& x: G) {
		if(vertices.find(x.first) != vertices.end()) {
			for(const auto y: x.second) {
				if(vertices.find(y) != vertices.end()) {
					induced[x.first].insert(y);
				}
			}
		}
	}
	return induced;
}

// assume G is 0 based, constructed graph is 1-based
GraphAdj::GraphAdj(const Graph &G) {
	for(const auto& x: G) {
		n = std::max(n, x.first+1);
	}
	adj.resize(n+1);
	for(int u=0; u<n; ++u) {
		for(auto v: G.at(u)) {
			adj[u+1].push_back(v+1);
		}
	}
}

