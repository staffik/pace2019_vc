#ifndef VC_H
#define VC_H

#include <iostream>

#include "graph.h"

extern VC NO_instance;
extern VC YES_instance;

// typedef moved due to cyclical includes breaking everything

std::ostream& operator<<(std::ostream&, const VC&);
void remove_high_deg_nodes(Graph &G, int &k, VC &partSol);

bool valid(const VC &res);
bool invalid(const VC &res);

VC solve_deg2(Graph &G);
void remove_leaves(Graph&, VC&);

VC merge_VCs(const VC &vc1, const VC &vc2);
VC merge_VCs(const std::vector<VC> &vcs);

#endif
