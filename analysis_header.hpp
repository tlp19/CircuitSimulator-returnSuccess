#ifndef analysis_header_hpp
#define analysis_header_hpp

#include <algorithm>

#include "network_header.hpp"
#include "network_functions.cpp"
#include "matrix_library/Matrix.h"
#include "matrix_library/Matrix.cpp"

using namespace std;

char tab = 9;



/* -- CLASSES AND STRUCTURES -- */




/* --- ANALYSIS FUNCTIONS --- */


//Extracts the node number of a node
vector<int> extract_node_number(vector<string> nodenames);


#endif
