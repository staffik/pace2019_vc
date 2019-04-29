#ifndef VC_CPP
#define VC_CPP

#include <iostream>
#include <vector>

#include "graph.h"

typedef std::tuple<Graph, int, std::vector<int>> VC;

std::ostream& operator<<(std::ostream&, const VC&);
VC remove_high_deg_nodes(VC vc);

bool successfull(const VC &res);
VC solve_deg2(VC vc);

#endif
