#include "graph.h"
#include <algorithm>
#include <queue>

std::ostream& operator<<(std::ostream& ostr, const Graph& G) {
	for(auto x: G) {
		ostr << x.first << ": ";
		for(auto y: x.second) {
			ostr << y << " ";
		}
		ostr << "\n";
	}
	return ostr;
}

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

void remove_single_vertex(Graph &G, int u) {
	for(auto v : G[u]) {
		G[v].erase(u);
		if(G[v].empty())
			G.erase(v);
	}
	G.erase(u);
}

void remove_vertices(Graph& G, std::unordered_set<int> vertices) {
	std::vector<int> keys;
	for(const auto& x: G) {
		keys.push_back(x.first);
	}
	for(const auto& node: keys) {
		if(vertices.find(node) != vertices.end()) {
			G.erase(node);
			continue;
		}
		std::vector<int> to_delete;
		for(const auto neigh: G[node]) {
			if(vertices.find(neigh) != vertices.end()) {
				to_delete.push_back(neigh);
			}
		}
		for(auto x: to_delete) {
			G[node].erase(x);
		}
		if(G[node].empty()) {
			G.erase(node);
		}
	}
}

std::unordered_set<int> get_connected_component(const Graph& G, int node) {
	std::unordered_set<int> cc = {};
	std::queue<int> q;
	q.push(node);
	while(q.size()) {
		node = q.front();
		q.pop();
		// if node is already visited
		if(cc.find(node) != cc.end()) {
			continue;
		}
		cc.insert(node);
		for(const auto neigh: G.at(node)) {
			q.push(neigh);
		}
	}
	return cc;
}

std::vector<std::unordered_set<int> > get_connected_components(const Graph& G) {
	std::unordered_set<int> visited;
	std::vector<std::unordered_set<int> > connected_components;
	for(const auto x: G) {
		// if x is visited
		auto node = x.first;
		if(visited.find(node) != visited.end()) {
			continue;
		}
		auto component = get_connected_component(G, node);
		for(const auto node: component) {
			visited.insert(node);
		}
		connected_components.push_back(component);
	}
	return connected_components;
}

Graph difference(Graph G, std::unordered_set<int> to_remove) {
	for(auto u : to_remove)
		remove_single_vertex(G, u);
	return G;
}

// assume G is 0 based, constructed graph is 1-based
GraphAdj::GraphAdj(const Graph &G) {
	n = -1;
	for(const auto& x: G) {
		n = std::max(n, x.first+1);
	}
	adj.resize(n+1);
	for(int u=0; u<n; ++u) {
		if(G.find(u) != G.end()) {
			for(auto v: G.at(u)) {
				adj[u+1].push_back(v+1);
			}
		}
	}
}

