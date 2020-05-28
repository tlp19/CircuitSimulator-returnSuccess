#ifndef analysis_header_hpp
#define analysis_header_hpp

#include "network_header.hpp"
#include "network_functions.cpp"

using namespace std;



/* -- CLASSES AND STRUCTURES -- */


// Struct to define a Matrix ans its methods
struct Matrix {
	int rows;
	int columns;
	vector<double> values;
	
	void set_nb_rows();
	void set_nb_columns();
	void set_value();
};



/* --- ANALYSIS FUNCTIONS --- */


#endif
