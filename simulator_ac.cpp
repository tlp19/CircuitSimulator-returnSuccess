#include "analysis_functions.cpp"

using namespace std;


int main() {

// INPUT

    //Read a network from input
    Network x;
	cin >> x;
	x.add_resistance_to_capacitors();
	cerr << "The input netlist is:" << endl << x << endl << endl;
	
	//Save the list of names of components
	vector<string> list_of_components = x.list_components();
	
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
    
    cerr << "The complete conductance matrix is:" << endl << conduct << endl;
    cerr << "And its inverse is:" << endl << conduct.inverse() << endl;
  
  
// CURRENT MATRIX AND ANALYSIS

	//List all the time intervals that we need to do the analysis at
	double time;
	vector<double> time_intervals = x.time_intervals();
	
	//Create and initialize the column matrix of currents
	Matrix current;
	current.resize(size, 1);
	
	//Create a Matrix result and a vector for the currents through each components (init. at 0)
	Matrix result;
	result.resize(size, 1);
	cerr << result << endl; 
	vector<double> components_currents;
	components_currents.resize(list_of_components.size());
	
	//Output the first row of the output CSV file
	print_CSV_header(list_of_nodes, list_of_components);
	
	//Do the analysis at all the time intervals
	for(int t_index = 0 ; t_index < time_intervals.size() ; t_index++) {
		time = time_intervals[t_index];
		
		//Save the previous results, and reset the matrices for the new calculations
		Matrix prev_result = result;
		vector<double> prev_currents = components_currents;
		result.fill_with_zeros();
		current.fill_with_zeros();
		components_currents = {};
		
		//Update the instantaneous value of the independant sources
		x.update_sources_instantaneous_values(time);		//For V, I with a Sine_function
		current.write_current_sources(x);
		current.write_voltage_sources(x);

		//Approximate capacitors and inductors to sources
		current.write_capacitors_as_voltage_sources(x, prev_result, prev_currents);
		current.write_inductors_as_current_sources(x, prev_result, prev_currents);
		
		//cerr << current << endl;

		//Calculate the result matrix
		result =  conduct.inverse() * current;
		
		components_currents = find_current_through_components(time, x, result, current);
		
		//Output the result matrix in CSV format
		print_in_CSV(time, result, components_currents);
		cerr << time << endl << endl;
		//cerr << result << endl << endl;
	}
	
	cerr << "end of analysis" << endl;
}
