#include "analysis_functions.cpp"

using namespace std;


int main() {

// INPUT

    //Read a network from input
    Network x;
	cin >> x;

	//Save the list of node names
    vector<string> list_of_nodes = x.list_nodes(); //list of nodes in the circuit (including ground)
    int size = list_of_nodes.size() - 1; //number of nodes (excluding ground)
    
    //Replace all user-selected node names with numbers
    x.set_nodes_to_numbers();
    

// CONDUCTANCE MATRIX

    //Create and initialize the square matrix of conductance
    Matrix conduct;
    conduct.resize(size,size);
    
    //Fill the conductance matrix with the conductance of the resistors
    conduct.write_resistor_conductance(x);
    cerr << "The conductance matrix with only resistors is:" << endl << conduct << endl;
    
    //Overwrite the previous matrix to support voltage sources
    conduct.overwrite_w_voltage_sources(x);
    
    cerr << "The conductance matrix is:" << endl << conduct << endl;
    cerr << "And its inverse is:" << endl << conduct.inverse() << endl;
  
  
// CURRENT MATRIX AND ANALYSIS

	//List all the time intervals that we need to do the analysis at
	double time;
	vector<double> time_intervals = x.time_intervals();
	
	//Create a Matrix result, and output the first row of the output CSV file
	Matrix result;
	print_CSV_header(list_of_nodes);
	
	//Do the analysis at all the time intervals
	for(int t_index = 0 ; t_index < time_intervals.size() ; t_index++) {
		time = time_intervals[t_index];
		x.update_instantaneous_values(x, t, result?);		//For V, I (Sine_function) and C, L (approximate to V or I)
		current.write_current_sources(x);
		current.write_voltage_sources(x);
		//current.write_capacitors_as_voltages(x);
		//current.write_inductors_as_currents(x);
		
		//Calculate the result matrix
		result =  current * conduct.inverse();
		
		//Output the result matrix in CSV format
		result.print_in_CSV(time);
	}
}
