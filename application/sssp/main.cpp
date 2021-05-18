#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "host_graph_api.h"
#include "host_graph_verification.h"

#include <algorithm>
#include <cassert>
#include <string>
#include <limits>

#include "l2.h"

graphInfo graphDataInfo;

void show_graph(const prop_t* const property, const unsigned long n) {
	static const unsigned int lim = 5;
	assert(n >= lim);
	
	const unsigned int low_lim = std::min((unsigned long) lim, n);
	const unsigned int up_lim = n - lim;
	
	unsigned long n_zero = 0;
	unsigned long i_zero = 0;
	
	bool show_frontier = true;
	
	
	for (unsigned i = 0; i < n; ++i) {
		if ( i < low_lim || i > up_lim) std::cerr << "Vertex " << i << ": " << property[i] << "\n";
		if ( property[i] == 0 ) {
			n_zero++;
			i_zero = i;
		}
		
		if ( property[i] >= MAX_PROP ) {
			if ( show_frontier ) {
				std::cerr << "------- Vertex " << i << " is an unvisited vertex frontier (" << property[i] << ") -------" << "\n";
				show_frontier = false;
			}
		}
		else show_frontier = true;
	}
	
	std::cerr << "Number of vertices with null property: " << n_zero << "\n";
	if ( n_zero > 0 ) std::cerr << "Last null property at: " << i_zero << "\n";
	
}

int main(int argc, char **argv) {
	
    char * xcl_file = NULL;
    unsigned long source = 0;
    unsigned long max_steps = std::numeric_limits<unsigned long>::max();
    
    if (argc > 1)
    {
        xcl_file = argv[1];
    }

    std::string gName;
    if (argc > 2)
    {
        gName = argv[2];
    }
    else
    {
        std::cout << "No dataset given." << "\n";
        return -1;
    }
	
	if (argc > 3) {
		max_steps = std::stoul(argv[3]);
	}
	
	if (argc > 4) {
		source = std::stoul(argv[4]);
	}
	std::cout << "Source vertex: " << source << "\n";
	graphDataInfo.userData = source;
	
	
    std::string mode = "normal";

    DEBUG_PRINTF("start main\n");

    acceleratorInit("graph_fpga", xcl_file);

    acceleratorDataLoad(gName, mode, &graphDataInfo);

    acceleratorDataPreprocess(&graphDataInfo);
    
    
    int *reg;
    prop_t *prop;
    int active_vertices = 1;
    unsigned int run_counter = 0;    
    do {
		acceleratorSuperStep(run_counter, &graphDataInfo);
		reg = (int *) acceleratorQueryRegister();
		active_vertices = reg[0];
		std::cerr << "\nRun " << run_counter << ": " << active_vertices << " active vertices\n";
		
		prop = acceleratorQueryProperty(run_counter % 2);
		show_graph(prop, graphDataInfo.vertexNum);
		run_counter++;
		
	} while (active_vertices != 0 && run_counter < max_steps);
    acceleratorDeinit();

    return 0;
}

