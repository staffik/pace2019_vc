#include "hopcroft_carp.h"

#include "graph.h"

const int INF = 1e9;

std::pair<std::vector<int>, std::vector<int>> hopcroft_carp::getVertexCover() {
	return vc;
}

hopcroft_carp::hopcroft_carp(GraphAdj BG)
	n = m = BG.n;

	pairU.clear();
	pairU.resize(n+1, 0);

	pairV.clear();
	pairV.resize(m+1, 0);

	dist.clear();
	dist.resize(n+1, INF);

	vis[0].clear();
	vis[0].resize(n+1, false);
	vis[1].clear();
	vis[1].resize(m+1, false);

	calculateMaximumMatching();
	calculateVertexCover();
}

bool hopcroft_carp::bfs() {
	std::queue<int> Q;

	for(int u=1; u<=n; ++u) {
		if(pairU[u]==0) {
			dist[u]=0;
			Q.push(u);
		} else {
			dist[u]=INF;
		}
	}

	dist[0] = INF;

	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();

		if(u==0) continue;
		for(int i=0; i<BG.adj[u].size(); ++i) {
			int v = BG.adj[u][i];
			if(dist[pairV[v]] == INF) {
				dist[pairV[v]] = dist[u] + 1;
				Q.push(pairV[v]);
			}
		}
	}

	return dist[0] != INF;	
}

bool hopcroft_carp::dfs(int u) {
	if (u != 0) {
		for (int i=0; i<BG.adj[u].size(); ++i) {
			int v = BG.adj[u][i];
			if(dist[pairV[v]] == dist[u]+1) {
				if (dfs(pairV[v])) {
					pairV[v]=u;
					pairU[u]=v;
					return true;
				}
			}
		}

		return false;
	}
	return true;
}

void hopcroft_carp::alternate(int u) {
	if(vis[0][u])
		return;
	vis[0][u]=true;
	for(int i=0; i<BG.adj[u].size(); ++i) {
		int v = BG.adj[u][i];
		if(!vis[1][v]) {
			vis[1][v]=true;
			int w = pairV[v];
			assert(w>0);
			alternate(w);
		}
	}
}

void hopcroft_carp::calculateMaximumMatching() {
	result=0;
	while(bfs()) {
		for (int u=1; u<=n; ++u) {
			if (pairU[u]==0) {
					result+=dfs(u);
			}
		}
	}
}

void hopcroft_carp::calculateVertexCover() {
	for(int u=1; u<=n; ++u) {
		if(pairU[u]==0) alternate(u);
	}
	for(int i=1; i<=n; ++i) {
		if(!vis[0][i]) vc.first.push_back(i);
	}
	for(int i=1; i<=m; ++i) {
		if(vis[1][i]) vc.second.push_back(i);
	}
	assert(result == vc.first.size() + vc.second.size());
}
