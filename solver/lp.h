#ifndef LP_H
#define LP_H
#include<vector>
#include "vc.h"

struct Constraint {
    float limit;
    std::vector<float> coefficients;
    // (limit, coefficients)
    // limit <= x_0 * coeff[0] + x_1 * coeff[1] + ... + x_n * coeff[n]
};

struct LP {
    std::vector<float> objective;
    std::vector<Constraint> constraints;
};

// typedef std::vector<std::pair<float, std::vector<float>>> LP;
// // (limit, coefficients)
// // limit <= x_0 * coeff[0] + x_1 * coeff[1] + ... + x_n * coeff[n]

LP LP_from_graph(Graph&);

#endif
