#ifndef analysis_header_hpp
#define analysis_header_hpp

#include <algorithm>

#include "network_header.hpp"
#include "network_functions.cpp"
//#include "libraries/matrix/Matrix.h"
//#include "libraries/matrix/Matrix.cpp"

using namespace std;

char tab = 9;



/* -- CLASSES AND STRUCTURES -- */


// Struct to define a Matrix and its methods
struct Matrix
{
    int rows;
    int cols; 
    vector<double> values;
    
    void resize(int rows, int cols);
    void write(int r, int c, Component v);
    double read(int r, int c);
    void fill_with_zeros();
    void print() const;
    void write_resistor_conductance(Network input_network);
    void overwrite_w_voltage_sources(Network input_network);
};



/* --- ANALYSIS FUNCTIONS --- */


//Extracts the node number of a node
vector<int> extract_node_number(vector<string> nodenames);


#endif
