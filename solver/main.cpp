#include "graph.h"
#include "io.h"
#include "solve.h"

int main() {
	// Read the input
	int n;
	Graph G;
    std::tie(n, G) = read_input();

	// Solve the instance
	VC solution = do_solve(G);

	// Write the output
    write_output(n, solution);

    return 0;
}
