#include "analysis_header.hpp"

using namespace std;


bool get_value_capacitor(Component C, /*current */ int i){
	C.num_value = i;
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

vector<double> Network::set_nodes_to_numbers() const {
	vector<string> a = Network::list_nodes();
	vector<double> listed_nodes_numbers;
	int n= a.size();
	for(int i=0; i<n; i++){
		listed_nodes_numbers[i] = i;
		}
	return listed_nodes_numbers;
}
