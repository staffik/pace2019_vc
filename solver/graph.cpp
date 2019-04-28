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

// assume G is 0 based, constructed graph is 1-based
GraphAdj::GraphAdj(const Graph &G) {
	n = G.n;
	adj.resize(n+1);
	for(int u=0; u<n; ++u) {
		for(auto v: G.adj[u]) {
			adj[u+1].push_back(v+1);
		}
	}
}

