#ifndef HOPCROFT_CARP_H
#define HOPCROFT_CARP_H

#include <vector>

#include "graph.h"

// returns minimum vertex cover of bipartite graph BG
std::pair<std::vector<int>, std::vector<int>> hopcroft_carp(BipartiteGraph &BG);

#endif // HOPCROFT_CARP_H
