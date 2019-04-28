
#ifndef KERNEL_2K_H
#define KERNEL_2K_H

#include <vector>

#include "graph.h"
#include "vc.h"

using vi = std::vector<int>;

// apply LPVC OneHalf reduction -> |G'(V)| <= 2k
VC kernel_2k_reduction(const VC &partSol);

#endif // KERNEL_2K_H
