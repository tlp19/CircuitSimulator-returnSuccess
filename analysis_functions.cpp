#include "analysis_header.hpp"

using namespace std;

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
