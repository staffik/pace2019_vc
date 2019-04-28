#include<iostream>

#include "graph.h"
#include "io.h"
#include "lp.h"
#include "vc.h"

int main() {
    Graph G = read_input();
    std::cout << max_deg(G) << "\n";
    auto subG = induced_subgraph(G, {1, 3, 5, 7, 8});
    std::cout << max_deg(subG) << "\n";

    auto res = remove_high_deg_nodes({G, 5, {}});
    auto partial_solution = std::get<2>(res);
    std::cout << partial_solution.size() << "\n";
    if(partial_solution.size()) {
        for(const auto node: partial_solution) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    // write_output(5, {2, 4});
    return 0;
}
