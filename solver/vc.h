#ifndef VC_CPP
#define VC_CPP

#include <iostream>
#include <vector>

#include "graph.h"

typedef std::vector<int> VC;

extern VC NO_instance;
extern VC YES_instance;

std::ostream& operator<<(std::ostream&, const VC&);
void remove_high_deg_nodes(Graph &G, int &k, VC &partSol);

bool valid(const VC &res);
bool invalid(const VC &res);

VC solve_deg2(Graph &G);
void remove_leaves(Graph&, VC&);

VC merge_VCs(const VC &vc1, const VC &vc2);
VC merge_VCs(const std::vector<VC> &vcs);

#endif
