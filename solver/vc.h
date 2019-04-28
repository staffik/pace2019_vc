#ifndef VC_CPP
#define VC_CPP

#include<vector>

#include "graph.h"

typedef std::tuple<Graph, int, std::vector<int>> VC;

VC remove_high_deg_nodes(VC vc);

bool successfull(const VC &res);

#endif
