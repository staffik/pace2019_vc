
#ifndef KERNEL_2K_H
#define KERNEL_2K_H

#include <vector>

#include "graph.h"
#include "vc.h"


void all_half_reduction(Graph &G, VC &partSol);
void kernel_2k_reduction(Graph &G, VC &partSol);

#endif // KERNEL_2K_H
