#ifndef VC_CPP
#define VC_CPP
#include<vector>
#include<unordered_set>

typedef std::vector<std::unordered_set<int>> Graph;

Graph preprocess(Graph G, int k);

#endif
