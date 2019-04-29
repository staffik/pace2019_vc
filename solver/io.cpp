#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <set>

#include "vc.h"

std::pair<int, Graph> read_input() {
    std::string line;
    int phase = 0;
    int n, m, x, y;

    Graph G;
    // phase 0: p td n m (n - no. vertices, m - no. edges)
    // phase 1: x y (endpoints)
    while(true) {
        if(!std::cin) {
            break;
        }
        std::getline(std::cin, line);
        if(line[0] == 'c') {
            std::cout << line << std::endl;
            continue;
        }
        if(phase == 1) {
            std::sscanf(line.c_str(), "%d %d", &x, &y);
            x--;
            y--;
            G[x].insert(y);
            G[y].insert(x);
        } else { // phase = 0
            assert(line[0] == 'p');
            std::sscanf(line.c_str(), "%*s %*s %d %d", &n, &m);
            // G.init(n);
            phase++;
        }
    }
    return {n, G};
}

void write_output(int n, std::vector<int> sol) {
    std::printf("s vc %d %zu\n", n, sol.size());
    std::sort(sol.begin(), sol.end());
    for(const int x: sol) {
        std::printf("%d\n", x+1);
    }
}
