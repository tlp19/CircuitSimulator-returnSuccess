#include "analysis_functions.cpp"

using namespace std;


int main() {

// INPUT

    //Read a network from input
    Network x;
	cin >> x;
	cerr << "The input netlist is:" << endl << x << endl << endl;

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
    
    //Overwrite the previous matrix to support voltage sources
    conduct.overwrite_w_voltage_sources(x);
    
    cerr << "The complete conductance matrix is:" << endl << conduct << endl;
    

//CURRENT MATRIX

	//Create and initialize the column matrix of currents
	Matrix current;
	current.resize(size, 1);
	
	//If not already DC, find a DC offset for the independant sources
	x.update_sources_instantaneous_values(0.0);	
	
	//Fill in the current matrix with the values of the independant current sources
	current.write_current_sources(x);
	
	//Fill in the current matrix with the values of the independant current sources
	current.write_voltage_sources(x);
	
	cerr << "The current matrix is:" << endl << current << endl;
	
	
//SOLVE THE CIRCUIT TO FIND THE NODE VOLTAGES
	
	//Create and calculate the matrix containing the results
	Matrix result;
	result = conduct.inverse() * current;
	
	//Print the result matrix to output using CSV format
	cerr << "And the voltages at each node are:" << endl << result << endl;
	print_CSV_header(list_of_nodes);
	result.print_in_CSV(0.0);
}
