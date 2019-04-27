#include "graph.h"

#include <assert.h>

#define DBG(x) x

void Graph::init(int N) {
	n = N;
	adj.clear();
	adj.resize(n);
}

Graph::vi& Graph::operator[](int idx) {
	DBG(assert(idx>=0 && idx<n));
	return adj[idx];
}

unsigned Graph::size() {
	return n;
}

BipartiteGraph::BipartiteGraph(const Graph &G) {
	n = G.n;
	for(int i=0; i<2; ++i) {
		adj[i].clear();
		adj[i].resize(n);
	}
	for(int u=0; u<n; ++u) {
		for(auto v: G.adj[u]) {
			adj[0][u].push_back(v);
			adj[1][u].push_back(v);
		}
	}
}

