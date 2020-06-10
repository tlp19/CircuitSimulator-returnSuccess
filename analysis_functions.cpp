#include "analysis_header.hpp"

using namespace std;


vector<double> Network::time_intervals() const {
	vector<double> intervals;
	double counter = 0.0;
	double _stop_time = get_numerical(instruction.stop_time);
	double _timestep = get_numerical(instruction.timestep);
	intervals.reserve(_stop_time/_timestep+1);
	while(counter < (_stop_time-_timestep/2)) {
		intervals.push_back(counter);
		counter += _timestep;
	}
	intervals.push_back(_stop_time);
	return intervals;
}

//Lists all nodes inside a Network in a sorted order
vector<string> Network::list_nodes() const {
	vector<string> all_nodes;
	vector<string> node_list;
	
	for(int i=0 ; i<components.size() ; i++) {
		for(int j=0 ; j<components[i].nodes.size() ; j++) {
			all_nodes.push_back(components[i].nodes[j]);
		}
	}
	
	sort(all_nodes.begin(), all_nodes.end());
	
	string node_n = all_nodes[0];
	node_list.push_back(node_n);
	for(int k=1 ; k<all_nodes.size() ; k++) {
		string node_n_p1 = all_nodes[k];
		if(node_n_p1 != node_n) {
			node_list.push_back(node_n_p1);
		}
		node_n = all_nodes[k];
	}
	
	return node_list;
}

void Network::set_nodes_to_numbers(){
	vector<string> a = Network::list_nodes();
	for(int i=0; i< components.size(); i++){
		for(int j=0 ; j<components[i].nodes.size() ; j++){
			for(int k=0 ; k< a.size(); k++){
				if(components[i].nodes[j] == a[k]){
					components[i].nodes[j] = to_string(k);
				}
			}
		}		
	}
//	return listed_nodes_numbers;
}

// Resizes a matrix
void Matrix::resize(int rows, int cols) { 
	this->rows=rows;
	this->cols=cols;
	values.resize(rows*cols);
	cerr << "Rows: " << rows << endl;
	cerr << "Columns: " << cols << endl;
	cerr << "-> Size: " << values.size() << endl << endl;
}

// Writes the value of a component inside the matrix
void Matrix::write(int r, int c, Component v)
{
	values[r*cols+c] = v.num_value;
}

// Returns the value stored in the matrix at a specific location
double Matrix::read(int r, int c)
{
	return values[r*cols+c];
}

// Fills a matrix with zeros (of the type double)
void Matrix::fill_with_zeros() {
	for(int i = 0 ; i < rows ; i++) {
		for(int j = 0 ; j < cols ; j++) {
			double zero = 0;
			values[i*cols+j] = zero;
		}
	}
}

// Extracts the node number of a node
vector<int> extract_node_number(vector<string> nodenames){
	vector<int> node_nb = {};
	for(int i=0; i < nodenames.size(); i++){
		node_nb.push_back((int)get_numerical(nodenames[i]));
		}
		cerr << "Between the nodes: " << node_nb[0] << "-" << node_nb[1] << endl;
	return node_nb;
}
	
	// Prints a matrix to cout
void Matrix::print() const {
	cerr << endl << "We get the following conductance matrix:" << endl;
	for(int i = 0 ; i < rows ; i++) {
		for(int j = 0 ; j < cols ; j++) {
			cout << values[i*cols+j] << tab;
		}
		cout << endl;
	}
	cerr << endl;
}

	// Fills in the values in the conductance matrix for the resistors present in the circuit
void Matrix::write_resistor_conductance(Network input_network) {
	vector<Component> input_components = input_network.components;
	vector<string> list_of_nodes = input_network.list_nodes();
	vector<Component> resistor_list;
	for (int i=0; i < input_components.size(); i++) {  
		Component x = input_components[i]; 
		if( x.type=='R'){
		resistor_list.push_back(x);
		}
	}
	for(int i=0; i < resistor_list.size(); i++) {
	   	vector<string> nodenames = resistor_list[i].nodes;
	   	int value = resistor_list[i].num_value;
		//extract the character at the end of the 2 node names (it corresponds to the node number)
		vector<int> node_nb = extract_node_number(nodenames);
		double G = 1.0/value;
		cerr << "Conductance value: " << G << endl;
		//check if it's connected to ground   
	   	if (node_nb[0]==0 || node_nb[1]==0){
			//diagonal
			int index = node_nb[0] + node_nb[1] - 1;
			cerr << "In the matrix at the coordinates: (" << index << ";" << index << ") [diagonal]" << endl;
			values[index*cols+index] += G;   
		} else {
			//between two non-ground nodes
			int a = node_nb[0] - 1;
			int b = node_nb[1] - 1;
			cerr << "In the matrix at the coordinates: (" << a << ";" << b << ")" << endl;
			cerr << "In the matrix at the coordinates: (" << b << ";" << a << ")" << endl;
			values[a*cols+b] = -G;
			values[b*cols+a] = -G;
			values[a*cols+a] += G;
			values[b*cols+b] += G;
		}
		cerr << endl;
	}
}

// Overwrites values of the matrix to consider the cases of voltage sources
void Matrix::overwrite_w_voltage_sources(Network input_network) {
	vector<Component> voltagesource_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if( x.type=='V'){
			voltagesource_list.push_back(x);
		}
   	}
	for(int i=0; i < voltagesource_list.size(); i++) {
		vector<string> nodenames = voltagesource_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		if (node_nb[0]==0 || node_nb[1]==0){
			int index = node_nb[0] + node_nb[1] - 1;
			for(int other_idx = 0 ; other_idx < cols ; other_idx++) {
				values[index*cols+other_idx] = 0;
			}
			values[index*cols+index] = 1;
		} else {
			vector<double> row_p;
			int pos = node_nb[0] - 1;
			int neg = node_nb[1] - 1;
			for(int idx = 0 ; idx < cols ; idx++) {
				row_p.push_back(values[pos*cols+idx]);
				values[pos*cols+idx] = 0;
			}
			values[pos*cols+pos] = 1;
			values[pos*cols+neg] = -1;
			for(int idx = 0 ; idx < cols ; idx++) {
				if(idx!=pos && idx!=neg) {
					values[neg*cols+idx] += row_p[idx];
				}
			}
			values[neg*cols+neg] += row_p[pos];
			values[neg*cols+pos] = 0;
		}
	}
}
