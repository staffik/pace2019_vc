#include <cassert>

#include "graph.h"
#include "io.h"
#include "solve.h"
#include "validate.h"

int main() {
	// Read the input
	int n;
	Graph G;
    std::tie(n, G) = read_input();

	// Solve the instance
	int solution = do_solve(G);
	std::cerr << "ANSWER:\t"<<solution<<std::endl;

	// Validate the solution
	//std::cerr << "Solution correctness validation\n";
	//assert(validate_correctness(G, solution));
	//std::cerr << "Solution minimality validation\nTHIS IS SLOW AND NEEDS TO BE TURNED OFF!!\n";
	//assert(validate_minimality(G, solution));

	// Write the output
    //write_output(n, solution);

    return 0;
}
