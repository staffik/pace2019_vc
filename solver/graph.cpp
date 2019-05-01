#include "graph.h"
#include <assert.h>
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

int number_of_edges(const Graph &G) {
	int m = 0;
	for(const auto &it : G)
		m += it.second.size();
	assert(m%2 == 0);
	return m/2;
}

int highest_degree_vertex(const Graph &G) {
	assert(!G.empty());
	auto it = G.cbegin();
	int res=it->first, deg = it->second.size();
	for(auto &it : G) {
		if(it.second.size()>deg) {
			deg = it.second.size();
			res = it.first;
		}
	}
	return res;
}

size_t max_deg(const Graph& G) {
	size_t res = 0;
	for(auto x: G) {
		res = std::max(res, x.second.size());
	}
	return res;
}

Graph operator-(Graph G, int u) {
	remove_single_vertex(G, u);
	return G;
}

Graph operator-(Graph G, const std::unordered_set<int> &vertices) {
	remove_vertices(G, vertices);
	return G;
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

void remove_vertices(Graph& G, const std::unordered_set<int> &vertices) {
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

void remove_loops(Graph &G, std::vector<int> &partSol) {
	std::vector<int> loops;
	for(auto &u : G) {
		if(u.second.find(u.first) != u.second.end()) {
			loops.push_back(u.first);
		}
	}
	for(auto u : loops) {
		partSol.push_back(u);
		remove_single_vertex(G, u);
	}
}

Graph get_connected_component(const Graph& G, int node) {
	Graph cc;
	std::queue<int> q;
	q.push(node);
	while(q.size()) {
		node = q.front();
		q.pop();
		// if node is already visited
		if(cc.find(node) != cc.end()) {
			continue;
		}
		cc[node] = G.at(node);
		for(auto neigh: G.at(node)) {
			q.push(neigh);
		}
	}
	return cc;
}

int connected_components(const Graph& G, std::vector<Graph> &CCs) {
	std::unordered_set<int> visited;
	for(const auto x: G) {
		// if x is visited
		auto node = x.first;
		if(visited.find(node) != visited.end()) {
			continue;
		}
		auto component = get_connected_component(G, node);
		for(const auto &node: component) {
			visited.insert(node.first);
		}
		CCs.push_back(component);
	}
	return CCs.size();
}

Graph difference(Graph G, std::unordered_set<int> to_remove) {
	for(auto u : to_remove)
		remove_single_vertex(G, u);
	return G;
}

// assume G is 0 based, constructed graph is 1-based
GraphAdj::GraphAdj(const Graph &G) {
	n = 0;
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

