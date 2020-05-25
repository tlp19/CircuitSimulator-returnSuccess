#include "header.hpp"

using namespace std;


// Edits the component characteristics to fill in the nb_branches parameter
Component find_nb_branches(Component input){
	if(input.type == 'Q'){
		input.nb_branches = 3;
	} else {
		input.nb_branches = 2;
	};
	return input; 
}

	
// Overloading the >> operator to read a Network from input in the SPICE format
istream &operator>>(istream &input, Network &s) {
		
		
		
	return input;
}
	
// Overloading the << operator to print a Network (for debugging purposes)
ostream &operator<<(ostream &output, const Network &s) {
	//Output the components
	int network_size = Network.components.size();
	for(int i=0, 
	
	//Output the instruction
	output << ".tran 0 " << s.instruction.stop_time << " 0 " << s.instruction.timestep << endl << ".end" << endl;
	return output;
}
