#ifndef header_hpp
#define header_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

using namespace std;


// CLASSES AND STRUCTURES

struct Component {
	char type;
	string name;
	int nb_branches;
	vector<string> nodes;
	float value;
	string transistor_type;
};

struct Instruction{
	string stop_time;
	string timestep;
};

class Network {
	vector<Component> components;
	Instruction instruction;
};


//FUNCTIONS

Component find_nb_branches(Component input){
	if(input.type == 'Q'){
		input.nb_branches = 3;
	} else {
		input.nb_branches = 2;
	};
	return input; 
}


#endif
