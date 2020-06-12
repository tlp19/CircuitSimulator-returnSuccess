#include "analysis_header.hpp"

using namespace std;


// Fills a matrix with zeros (of the type double)
void Matrix::fill_with_zeros() {
	for(int i = 0 ; i < rows ; i++) {
		for(int j = 0 ; j < cols ; j++) {
			double zero = 0;
			values[i*cols+j] = zero;
		}
	}
}


//List all the times at which we need to analyze the circuit
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
	
	//Store all the nodes of the network in a vector
	for(int i=0 ; i<components.size() ; i++) {
		for(int j=0 ; j<components[i].nodes.size() ; j++) {
			all_nodes.push_back(components[i].nodes[j]);
		}
	}
	
	//Sort the vector
	sort(all_nodes.begin(), all_nodes.end());
	
	//Delete duplicates
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


//Lists all components inside a Network in a sorted order
vector<string> Network::list_components() const {
	vector<string> name_list;
	for(int i=0 ; i<components.size() ; i++) {
		string component_name = "";
		component_name += components[i].type;
		component_name += components[i].name;
		name_list.push_back(component_name);
	}
	return name_list;
}


//Changes all the nodenames in a circuit to numbers (string)
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
}


//Adds a small resistance in series with all C and V to find the current through them
void Network::add_resistance_to_C_and_V(){

	for(int i = 0 ; i < components.size() ; i++) {
	
		if(components[i].type == 'C') {
			string node0 = components[i].nodes[0];
			string node1 = components[i].nodes[1];
			
			//Add a resistor in series with the first terminal of the capacitor
			string new_node = "ZZ_" + node0 + "_" + node1;
			Component new_resistor;
			new_resistor.type = 'T';
			new_resistor.name = components[i].name;
			new_resistor.set_nb_branches();
			new_resistor.nodes.resize(2);
			new_resistor.nodes[0] = node0;
			new_resistor.nodes[1] = new_node;
			new_resistor.num_value = 1;
			new_resistor.has_function = 0;
			components[i].nodes[0] = new_node;
			components.push_back(new_resistor);
			
			//Add a resistor in series with the first terminal of the capacitor to cancel it out
			string new_node2 = "ZZ__" + node0 + "_" + node1;
			Component new_resistor2;
			new_resistor2.type = 'T';
			new_resistor2.name = components[i].name + "_";
			new_resistor2.set_nb_branches();
			new_resistor2.nodes.resize(2);
			new_resistor2.nodes[0] = new_node2;
			new_resistor2.nodes[1] = node1;
			new_resistor2.num_value = -1;
			new_resistor2.has_function = 0;
			components[i].nodes[1] = new_node2;
			components.push_back(new_resistor2); 
			
		} else if(components[i].type == 'V') {
			string node0 = components[i].nodes[0];
			string node1 = components[i].nodes[1];
			
			//Add a resistor in series with the first terminal of the voltage source
			string new_node = "XX_" + node0 + "_" + node1;
			Component new_resistor;
			new_resistor.type = 'S';
			new_resistor.name = components[i].name;
			new_resistor.set_nb_branches();
			new_resistor.nodes.resize(2);
			new_resistor.nodes[0] = node0;
			new_resistor.nodes[1] = new_node;
			new_resistor.num_value = 1;
			new_resistor.has_function = 0;
			components[i].nodes[0] = new_node;
			components.push_back(new_resistor);
			
			//Add a resistor in series with the second terminal of the voltage source to cancel it out
			string new_node2 = "XX__" + node0 + "_" + node1;
			Component new_resistor2;
			new_resistor2.type = 'S';
			new_resistor2.name = components[i].name + "_";
			new_resistor2.set_nb_branches();
			new_resistor2.nodes.resize(2);
			new_resistor2.nodes[0] = new_node2;
			new_resistor2.nodes[1] = node1;
			new_resistor2.num_value = -1;
			new_resistor2.has_function = 0;
			components[i].nodes[1] = new_node2;
			components.push_back(new_resistor2); 
		}
	}
}


// Extracts the node number of a node
vector<int> extract_node_number(const vector<string> &nodenames){
	vector<int> node_nb = {};
	for(int i=0; i < nodenames.size(); i++){
		node_nb.push_back((int)get_numerical(nodenames[i]));
		}
	return node_nb;
}


// Prints a matrix to cout
ostream &operator<<(ostream &output, const Matrix &mat) {
	for(int i = 0 ; i < mat.rows ; i++) {
		for(int j = 0 ; j < mat.cols ; j++) {
			output << mat.values[i*mat.cols+j] << tab;
		}
		output << endl;
	}
	return output;
}


// CONDUCTANCE: Fills in the values in the conductance matrix for the resistors present in the circuit
void Matrix::write_resistor_conductance(const Network &input_network) {

	//List all the resistors present in a circuit
	vector<Component> input_components = input_network.components;
	vector<string> list_of_nodes = input_network.list_nodes();
	vector<Component> resistor_list;
	for (int i=0; i < input_components.size(); i++) {  
		Component x = input_components[i]; 
		if(x.type=='R' || x.type=='T' || x.type=='t' || x.type=='S'){
		resistor_list.push_back(x);
		}
	}
	
	//For each resistor, complete the current matrix with the appropriate values
	for(int i=0; i < resistor_list.size(); i++) {
	   	vector<string> nodenames = resistor_list[i].nodes;
	   	vector<int> node_nb = extract_node_number(nodenames);
	   	double value = resistor_list[i].num_value;
		double G = 1.0/value;
		//Check if it's connected to ground   
	   	if (node_nb[0]==0 || node_nb[1]==0){
			//connected to groud: add values only in diagonal
			int index = node_nb[0] + node_nb[1] - 1;
			values[index*cols+index] += G;   
		} else {
			//between two un-grounded nodes
			int a = node_nb[0] - 1;
			int b = node_nb[1] - 1;
			values[a*cols+b] += -G;
			values[b*cols+a] += -G;
			values[a*cols+a] += G;
			values[b*cols+b] += G;
		}
	}
}


// CONDUCTANCE: Overwrites values of the matrix to consider the cases of voltage sources
void Matrix::overwrite_w_voltage_sources(const Network &input_network) {

	//List all the voltage sources (and capacitors) present in the circuit
	vector<Component> voltagesource_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if(x.type=='V' || x.type=='C'){
			voltagesource_list.push_back(x);
		}
   	}
   	
   	//For each voltage source, complete the conductance matrix with the appropriate values
	for(int i=0; i < voltagesource_list.size(); i++) {
		vector<string> nodenames = voltagesource_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		if (node_nb[0]==0 || node_nb[1]==0){
			//connected to ground
			int index = node_nb[0] + node_nb[1] - 1;
			for(int other_idx = 0 ; other_idx < cols ; other_idx++) {
				values[index*cols+other_idx] = 0;
			}
			values[index*cols+index] = 1;
		} else {
			//between two un-grounded nodes
			int pos = node_nb[0] - 1;
			int neg = node_nb[1] - 1;
			//First, save the row p
			vector<double> row_p;
			for(int idx = 0 ; idx < cols ; idx++) {
				row_p.push_back(values[pos*cols+idx]);
				values[pos*cols+idx] = 0;
			}
			//Then, set the right values at the row p
			values[pos*cols+pos] = 1;
			values[pos*cols+neg] = -1;
			//Then sum the two old rows to do the supernode analysis
			for(int idx = 0 ; idx < cols ; idx++) {
					values[neg*cols+idx] += row_p[idx];
			}
		}
	}
}


// CURRENT: Writes the value of the current sources in the current matrix
void Matrix::write_current_sources(const Network &input_network) {
	assert(cols==1);
	
	//List all the current sources present in the circuit
	vector<Component> currentsource_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if(x.type=='I'){
			currentsource_list.push_back(x);
		}
   	}
   	
   	//For each current source, complete the current matrix with the appropriate values
	for(int i=0; i < currentsource_list.size(); i++) {
		vector<string> nodenames = currentsource_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		int in = node_nb[0] - 1;
		int out = node_nb[1] - 1;
		if(out>=0){values[out] += currentsource_list[i].num_value;}
		if(in>=0){values[in] += -currentsource_list[i].num_value;}
	}
}


// CURRENT: Writes the value of the voltage sources in the current matrix
void Matrix::write_voltage_sources(const Network &input_network) {
	assert(cols==1);
	
	//List all the voltage sources present in the circuit
	vector<Component> voltagesource_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if(x.type=='V'){
			voltagesource_list.push_back(x);
		}
   	}
   	
   	//For each voltage source, complete the current matrix with the appropriate values
	for(int i=0; i < voltagesource_list.size(); i++) {
		vector<string> nodenames = voltagesource_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		int pos = node_nb[0] - 1;
		int neg = node_nb[1] - 1;
		//if the positive terminal is connected to ground, set it as a negative voltage source the other way around
		if(pos<=0) {
			values[neg] = -voltagesource_list[i].num_value;
		} else {
			values[pos] = voltagesource_list[i].num_value;
		}
	}
}



// DEBUGGING ONLY: set to false for normal output, set to true to output all the values for all nodes and components (including the ones created by the program for the analysis
//--------------------------------------------
bool debug = false;
//--------------------------------------------


// OUTPUT: Prints out the first row of the CSV file
void print_CSV_header(const vector<string> &nodenames, const vector<string> &compnames) {
	
	//The first column of the CSV file constains the time
	cout << "Time" << tab;
	
	for(int i = 1 ; i < nodenames.size() ; i++) {
		//If not a node created only for analysis, output the name of the node
		if(debug==false) {
			if((nodenames[i].at(0)!='Z' && nodenames[i].at(1)!='Z') && (nodenames[i].at(0)!='Y' && nodenames[i].at(1)!='Y') && (nodenames[i].at(0)!='X' && nodenames[i].at(1)!='X')) {
				cout << "V(" << nodenames[i] << ")" << tab;
			}
		} else {
			cout << "V(" << nodenames[i] << ")" << tab;
		}
	}
	
	for(int i = 0 ; i < compnames.size() ; i++) {
		//If not a resistor created only for analysis, output the name of the component
		if(debug==false) {
			if((compnames[i].at(0) != 'T')&&(compnames[i].at(0)!='t')&&(compnames[i].at(0)!='S')) {
				cout << "I(" <<compnames[i] << ")" << tab;
			}
		} else {
			cout << "I(" <<compnames[i] << ")" << tab;
		}
	}
	
	cout << "\n";
}


// OUTPUT: Prints out one result row of the CSV file
void print_in_CSV(const double &time, const Matrix &mat, const vector<double> &vec, const Network &net, const vector<string> &nodenames, const vector<string> &compnames) {
	
	assert(mat.cols==1);
	cout << time << tab;
	
	//Output the voltages of the nodes
	for(int i = 1 ; i < nodenames.size() ; i++) {
		if(debug==false){
			if((nodenames[i].at(0)!='Z' && nodenames[i].at(1)!='Z') && (nodenames[i].at(0)!='Y' && nodenames[i].at(1)!='Y') && (nodenames[i].at(0)!='X' && nodenames[i].at(1)!='X')) {
				cout << find_voltage_at(nodenames[i], nodenames, mat) << tab;
			}
		} else {
			cout << find_voltage_at(nodenames[i], nodenames, mat) << tab;
		}
	}
	
	//Output the currents through the components
	for(int i = 0 ; i < compnames.size() ; i++) {
		if(debug==false) {
			if((compnames[i].at(0)!='T')&&(compnames[i].at(0)!='t')&&(compnames[i].at(0)!='S')) {
				cout << find_current_through(compnames[i], net, vec) << tab;
			}
		} else {
			cout << find_current_through(compnames[i], net, vec) << tab;
		}
	}
	cout << "\n";
}


// Updates the instantaneous value of voltage and current sources
void Network::update_sources_instantaneous_values(const double &time) {
	for(int i = 0 ; i < components.size() ; i++) {
		double omega =  components[i].function.frequency;
		if(components[i].has_function==true) {
			components[i].num_value = components[i].function.amplitude * sin(omega * time) + components[i].function.dc_offset;
		}
	}
}


//Returns the voltage at a given node, by finding the value of the node in the result matrix
double find_voltage_at(const string &nodename, const vector<string> &nodelist, const Matrix &voltages) {
	
	//If asked for ground, just return 0
	if(nodename=="0") {return 0;}
	assert(voltages.cols==1);
	double voltage;
	
	//Go through the list of nodes until we find our node
	int i = 1;
	while(i<nodelist.size() && nodename != nodelist[i]) {
		i++;
	}
	
	//Debugging for memory management
	assert(voltages.size()==nodelist.size()-1);
	if(i>=nodelist.size()) {assert(false);}
	
	//Return the corresponding value at the same index from the result matrix
	voltage = voltages.values[i-1];
	return voltage;
};


//Finds all the current through the components
vector<double> find_current_through_components(const double &time, const Network &net, const Matrix &voltage_mat, const Matrix &current_mat) {
	vector<string> nodelist = net.list_nodes();
	vector<double> currents;
	for(int i = 0 ; i < net.components.size() ; i++) {
		if(net.components[i].type == 'V') {
		
			//List the components of the circuit
			vector<string> comp_list;
			for(int k = 0 ; k < net.components.size() ; k++) {
					comp_list.push_back(net.components[k].type + net.components[k].name);
			}
			
			//Find the resistor that we want the current of
			string comp_name = 'S' + net.components[i].name;
			int j = 0;
			while(comp_name != comp_list[j]) {
				j++;
			}
			Component resistor_s = net.components[j];
			
			//Calculate its current
			double vol_0 = find_voltage_at(resistor_s.nodes[0], nodelist, voltage_mat);
			double vol_1 = find_voltage_at(resistor_s.nodes[1], nodelist, voltage_mat);
			double current_s = (vol_0 - vol_1) / resistor_s.num_value ;
			
			//This is the same current as the one through the voltage source
			currents.push_back(current_s);
			
		} else if(net.components[i].type == 'I') {
			//Simply take the value of the current source
			currents.push_back(net.components[i].num_value);
			
		} else if(net.components[i].type == 'R' || net.components[i].type == 'T' || net.components[i].type == 't' || net.components[i].type == 'S') {
			double vol_0 = find_voltage_at(net.components[i].nodes[0], nodelist, voltage_mat);
			double vol_1 = find_voltage_at(net.components[i].nodes[1], nodelist, voltage_mat);
			double current_r = (vol_0 - vol_1) / net.components[i].num_value ;
			currents.push_back(current_r);
			
		} else if(net.components[i].type == 'C') {
			//List the components of the circuit
			vector<string> comp_list;
			for(int k = 0 ; k < net.components.size() ; k++) {
					comp_list.push_back(net.components[k].type + net.components[k].name);
			}
			
			//Find the resistor that we want the current of
			string comp_name = 'T' + net.components[i].name;
			int j = 0;
			while(comp_name != comp_list[j]) {
				j++;
			}
			Component resistor_t = net.components[j];
			
			//Calculate its current
			double vol_0 = find_voltage_at(resistor_t.nodes[0], nodelist, voltage_mat);
			double vol_1 = find_voltage_at(resistor_t.nodes[1], nodelist, voltage_mat);
			double current_t = (vol_0 - vol_1) / resistor_t.num_value ;
			
			//This is the same current as the one through the capacitor
			currents.push_back(current_t);
			
		} else if(net.components[i].type == 'L') {
			//The value is stored in the buffer of the inductor
			double current_l = net.components[i].buffer;
			currents.push_back(current_l);
		}
	}
	return currents;
}


//Returns the current through a given component, by finding the value in the current result vector
double find_current_through(const string &comp_name, const Network &x, const vector<double> &currents) {
	double current;
	vector<string> comp_list;
	for(int i = 0 ; i < x.components.size() ; i++) {
		comp_list.push_back(x.components[i].type + x.components[i].name);
	}
	int j = 0;
	while(comp_name != comp_list[j]) {
		j++;
	}
	current = currents[j];
	return current;
};


//Writes capacitors in the current matrix as voltage sources
void Matrix::write_capacitors_as_voltage_sources(const Network &input_network, const Matrix &prev_v, const vector<double> &prev_c) {

	assert(prev_v.cols==1);
	vector<string> nodelist = input_network.list_nodes();
	double _timestep = get_numerical(input_network.instruction.timestep);
	
	//List all the capacitors present in the circuit
	vector<Component> capacitors_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if(x.type=='C'){
			capacitors_list.push_back(x);
		}
   	}
   	
   	//For each capacitor, complete the current matrix with the appropriate value
	for(int i=0; i < capacitors_list.size(); i++) {
	
		double capacitance = capacitors_list[i].num_value;
		
		//Previous values are:
		double prev_vol_0 = find_voltage_at(capacitors_list[i].nodes[0], nodelist, prev_v);
		double prev_vol_1 = find_voltage_at(capacitors_list[i].nodes[1], nodelist, prev_v);
		
		string name = capacitors_list[i].type + capacitors_list[i].name;
		double prev_c_through_C = find_current_through(name, input_network, prev_c);
		
		//Find the value of the equivalent voltage source
   		double C_as_voltage_value = (prev_vol_0 - prev_vol_1) + ((prev_c_through_C/capacitance) * _timestep);
   		
   		//Add this value in the current matrix
		vector<string> nodenames = capacitors_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		int pos = node_nb[0] - 1;
		int neg = node_nb[1] - 1;
		if(pos<0) {
			values[neg] = -C_as_voltage_value;
		} else {
			values[pos] = C_as_voltage_value;
		}
	}
}


//Writes inductors in the current matrix as current sources
void Matrix::write_inductors_as_current_sources(Network &input_network, const Matrix &prev_v, const vector<double> &prev_c) {

	assert(prev_v.cols==1);
	vector<string> nodelist = input_network.list_nodes();
	double _timestep = get_numerical(input_network.instruction.timestep);
	
	//List all the inductors present in the circuit, and also store all the components
	vector<Component> inductors_list;
	for (int i=0; i < input_network.components.size(); i++) {  
		Component x = input_network.components[i]; 
		if(x.type=='L'){
			inductors_list.push_back(x);
		}
   	}
   	
   	//For each inductor, complete the current matrix with the appropriate value
	for(int i=0; i < inductors_list.size(); i++) {
	
		double inductance = inductors_list[i].num_value;
		
		//Previous values are:
		double prev_vol_0 = find_voltage_at(inductors_list[i].nodes[0], nodelist, prev_v);
		double prev_vol_1 = find_voltage_at(inductors_list[i].nodes[1], nodelist, prev_v);
		string name = inductors_list[i].type + inductors_list[i].name;
		double prev_c_through_L = find_current_through(name, input_network, prev_c);
	
		//Find the value of the equivalent current source
		double L_as_current_value = prev_c_through_L + (((prev_vol_0 - prev_vol_1)/inductance) * _timestep);
		
		//Add this value in the current matrix
		vector<string> nodenames = inductors_list[i].nodes;
		vector<int> node_nb = extract_node_number(nodenames);
		int in = node_nb[0] - 1;
		int out = node_nb[1] - 1;
		if(out>=0){values[out] += L_as_current_value;}
		if(in>=0){values[in] += - L_as_current_value;}
		
		//Not optimized - Store the value calculated back into the buffer of the inductor
		string comp_name = 'L' + inductors_list[i].name;
		int j = 0;
		while(comp_name != (input_network.components[j].type+input_network.components[j].name)) {
			j++;
		}
		input_network.components[j].buffer = L_as_current_value;
	}
}
