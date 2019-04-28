
#ifndef KERNEL_2K_H
#define KERNEL_2K_H

#include "graph.h"
#include <vector>

using vi = std::vector<int>;

// returns pair of lists <do_not_get_to_solution, get_to_solution>
std::pair<vi,vi> kernel_2k_reduction(const Graph &G);

#endif // KERNEL_2K_H
