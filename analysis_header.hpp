#ifndef analysis_header_hpp
#define analysis_header_hpp

#include <algorithm>

#include "network_header.hpp"
#include "network_functions.cpp"
#include "matrix_library/Matrix.h"
#include "matrix_library/Matrix.cpp"

using namespace std;


/* ----- CONSTANTS ----- */

const char tab = '\t';
const double pi = 3.141592653589793238463;



/* ---- CLASSES AND STRUCTURES ---- */

//Matrix struct is declared in "matrix_library/Matrix.h" with all of it's methods' declarations



/* -- GENERAL ANALYSIS FUNCTIONS -- */

//Extracts the node number of a node
vector<int> extract_node_number(const vector<string> &nodenames);

//Prints the first row of a CSV file
void print_CSV_header(const vector<string> &nodenames, const vector<string> &compnames);

//Prints a row of the CSV file for a specific time
void print_in_CSV(const double &time, const Matrix &mat, const vector<double> &vec, const Network &net, const vector<string> &nodenames, const vector<string> &compnames);

//Find the voltage at a given node (from previous results)
double find_voltage_at(const string &nodename, const vector<string> &nodelist, const Matrix &voltages);

//Find the current through each component of a network in one instant
vector<double> find_current_through_components(const double &time, const Network &net, const Matrix &voltage_mat, const Matrix &current_mat);

//Find current through a given component (from previous results)
double find_current_through(const string &name, const Network &x, const vector<double> &currents);


#endif
