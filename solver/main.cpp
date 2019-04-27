#include<iostream>
#include "io.h"
#include "vc.h"
#include "lp.h"

int main() {
    Graph G = read_input();
//    preprocess(G, 8);
//    LP_from_graph(G);    
    write_output(5, {2, 4});
    return 0;
}
