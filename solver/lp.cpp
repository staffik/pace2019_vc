#include<iostream>
#include<vector>

#include "lp.h"

std::ostream& operator<<(std::ostream& ostream, std::vector<float> v) {
    // for(auto x: v) {
    //     ostream << x << " ";
    // }
    // ostream << "\n";
    return ostream;
}

LP LP_from_graph(Graph& G) {
    LP lp;
    std::vector<Constraint> constrs;
    int n = G.size();
    std::vector<float> coeffs;
    for(int i = 0; i < n; i++) {
        // x_0 + x_1 + ... + x_n
        lp.objective = std::vector<float>(n, 1);

        // 0 <= x_i
        coeffs = std::vector<float>(n, 0);
        coeffs[i] = 1;
        // std::cout << coeffs;
        constrs.push_back({0, coeffs});

        // x_i <= 1  <==>  -1 <= -x_i
        coeffs = std::vector<float>(n, 0);
        coeffs[i] = -1;
        // std::cout << coeffs;
        constrs.push_back({-1, coeffs});

        for(auto j: G[i]) {
            // std::cout << i << " " << j << "\n";
            // 1 <= x_i + x_j
            coeffs = std::vector<float>(n, 0);
            coeffs[i] = 1;
            coeffs[j] = 1;
            // std::cout << coeffs;
            constrs.push_back({1, coeffs});
        }
    }
    return lp;
}
