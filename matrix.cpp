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
    

//CURRENT MATRIX

	//Create and initialize the column matrix of currents
	Matrix current;
	current.resize(size, 1);

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
}





/*
double time;
vector<double> time_intervals = x.time_intervals();

Matrix result;

for(int t_index = 0 ; t_index < time_intervals.size() ; t_index++) {
	time = time_intervals[t_index];
	x.update_instantaneous_values(x, t, result?);		//For V, I (Sine_function) and C, L (approximate to V or I)
	current.write_current_sources(x);
	current.write_voltage_sources(x);
	current.write_capacitors_as_voltages(x);
	current.write_inductors_as_currents(x);
	
	result =  current * conduct.inverse();
	result.print_in_CSV(time);
}

*/
