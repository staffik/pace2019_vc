#include <assert.h>
#include <algorithm>
#include <queue>
#include "graph.h"
#include "vc.h"

ExtGraph::ExtGraph(const Graph &G) : G(G) {
	n = G.size();
	m = 0;
	for(auto &it : G) {
		int deg = it.second.size();
		m += deg;
		deg_2_nodes[deg].insert(it.first);
	}
	assert(m%2==0);
	m/=2;
};

int ExtGraph::max_deg() {
	if(G.empty()) return 0;
	return deg_2_nodes.rbegin()->first;
}

int ExtGraph::highest_degree_node() {
	assert(!G.empty());
	return *(deg_2_nodes.rbegin()->second.begin());
}

void ExtGraph::verify() {
	int a = G.size(), b=0;
	for(auto v : G) {
		assert(deg_2_nodes[v.second.size()].find(v.first) != deg_2_nodes[v.second.size()].end());
	}
	for(auto d : deg_2_nodes)
		b += d.second.size();
	assert(a == b);
}

void ExtGraph::remove_single_vertex(Graph::value_type &u) {
	int deg = G[u.first].size();
	deg_2_nodes[deg].erase(u.first);
	if(deg_2_nodes[deg].empty())
		deg_2_nodes.erase(deg);
	G.erase(u.first);

	for(auto v : u.second) {
		auto it = G.find(v);
		if(it==G.end())
			continue;

		int deg = it->second.size();
		deg_2_nodes[deg].erase(v);
		if(deg_2_nodes[deg].empty())
			deg_2_nodes.erase(deg);

		m -= it->second.erase(u.first);

		if(it->second.empty())
			G.erase(it);
		else
			deg_2_nodes[it->second.size()].insert(v);

	}
	n = G.size();
}

void ExtGraph::add_single_vertex(Graph::value_type &u) {
	auto ut = G.find(u.first);
	if(ut != G.end()) {
		deg_2_nodes[ut->second.size()].erase(ut->first);
	}
	for(auto v : u.second) {
		auto it = G.find(v);
		if(it != G.end()) {
			int deg = it->second.size();
			auto& jt = deg_2_nodes.at(deg);
			jt.erase(v);
			if(jt.empty())
				deg_2_nodes.erase(deg);
		}

		bool inserted = false;
		inserted |= G[v].insert(u.first).second;
		deg_2_nodes[G[v].size()].insert(v);

		inserted |= G[u.first].insert(v).second;
		m += inserted;
	}
	deg_2_nodes[G[u.first].size()].insert(u.first);
	n = G.size();
	int x = highest_degree_node();
}

void ExtGraph::remove_vertices(Graph::value_type &u,
					std::vector<Graph::value_type> &neighbors) {
	for(auto v : u.second) {
		auto it = G.find(v);
		if(it==G.end())
			continue;

		neighbors.emplace_back(*it);
		remove_single_vertex(neighbors.back());
	}
}

void ExtGraph::add_vertices(std::vector<Graph::value_type> &neighbors) {
	for(auto &v : neighbors) {
		add_single_vertex(v);
	}
}

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

void remove_single_vertex(Graph &G, Graph::value_type &u) {
	for(auto v : u.second) {
		G[v].erase(u.first);
		if(G[v].empty())
			G.erase(v);
	}
	G.erase(u.first);
}

void add_single_vertex(Graph &G, Graph::value_type &u) {
	for(auto v : u.second) {
		G[v].insert(u.first);
		G[u.first].insert(v);
	}
}

void remove_vertices(Graph &G, Graph::value_type &u,
					std::vector<Graph::value_type> &neighbors) {
	for(auto v : u.second) {
		auto it = G.find(v);
		if(it==G.end())
			continue;

		neighbors.emplace_back(*it);
		remove_single_vertex(G, neighbors.back());
	}
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

void add_vertices(Graph &G,	std::vector<Graph::value_type> &neighbors) {
	for(auto &v : neighbors) {
		add_single_vertex(G,  v);
	}
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

int remove_loops(Graph &G) {
	std::vector<Graph::value_type> loops;
	for(auto &u : G) {
		if(u.second.find(u.first) != u.second.end()) {
			loops.emplace_back(u);
		}
	}
	int g = G.size();
	for(auto &u : loops) {
		remove_single_vertex(G, u);
	}
	return g - G.size();
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

