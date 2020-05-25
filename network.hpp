#ifndef network_hpp
#define network_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

using namespace std;



/* CLASSES AND STRUCTURES */


//Struct to define a specific component inside the circuit
struct Component {
	char type;						//Type of the component; either R, C, L, D or Q
	string name;					//Arbitrary name of the component
	int nb_branches;				//Number of nodes that the component is connected to
	vector<string> nodes;			//List of the nodes that the component is connected to (2 or 3)
	float value;					//Value of the component (in Ohms, Farads, etc.)
	string transistor_type;			//In case the component is a transistor, this is either NPN or PNP
};


//Struct to store the analysis instruction of the .tran line in the input
struct Instruction{
	string stop_time;				//Second argument of the .tran instruction
	string timestep;				//Fourth argument of the .tran instruction
};


//Struct to store the whole Network as defined in the input SPICE file, as well as the .tran instruction
struct Network {
	vector<Component> components;	//List of the components in the network
	Instruction instruction;		//Specification of the .tran instruction to analyse the circuit
	
	// Overloading the >> operator to read a network from input in the SPICE format
	istream &operator>>(istream &input, Network &s) {
		
		
		
		return input;
	}
	
	// Overloading the << operator to print a Network (for debugging purposes)
	ostream &operator<<(ostream &output, const Network &s) {
	
	
	
		return output;
	}
};



/* FUNCTIONS */


Component find_nb_branches(Component input){
	if(input.type == 'Q'){
		input.nb_branches = 3;
	} else {
		input.nb_branches = 2;
	};
	return input; 
}


#endif
