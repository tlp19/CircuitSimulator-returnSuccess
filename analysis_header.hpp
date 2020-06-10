#ifndef analysis_header_hpp
#define analysis_header_hpp

#include <algorithm>

#include "network_header.hpp"
#include "network_functions.cpp"
#include "matrix_library/Matrix.h"
#include "matrix_library/Matrix.cpp"

using namespace std;


/* --- CONSTANTS --- */
const char tab = 9;
const double pi = 3.141592653589793238463;



/* -- CLASSES AND STRUCTURES -- */

//Matrix struct is in matrix_library/Matrix.h
//with all of it's methods' declarations



/* -- ANALYSIS FUNCTIONS (not linked to either Matrix or Network) -- */

//Extracts the node number of a node
vector<int> extract_node_number(vector<string> nodenames);

//Prints the first row of a CSV file
void print_CSV_header(const vector<string> nodenames);

//Prints a row of the CSV file for a specific time
void print_in_CSV(const double time, const Matrix mat, const vector<double> vec);

//Find the voltage at a given node
double find_voltage_at(const string nodename, const vector<string> nodelist, const Matrix voltages);

//Find the current through each component of a network at instant omega
vector<double> find_current_through_components(const double time, const Network net, const Matrix mat);


#endif
