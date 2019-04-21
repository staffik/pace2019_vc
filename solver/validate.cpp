#include <vector>
#include "validate.h"

bool validate_correctness(Graph G, const VC& sol) {
    remove_vertices(G, sol);
    return G.empty();
}

bool validate_minimality(const Graph& G, const VC& sol) {
    for(auto x: sol) {
        auto subsol = sol;
        subsol.erase(x);
        if(validate_correctness(G, subsol)) {
            return false;
        }
    }
    return true;
}
