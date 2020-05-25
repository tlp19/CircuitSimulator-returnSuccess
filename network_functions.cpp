#include "header.hpp"

using namespace std;


// Returns either the value or the transistor type depending on the component
string Component::value_type() const {
	if(type=='Q') {
		return transistor_type;
	} else {
		return value;
	}
}


// Edits the component characteristics to fill in the nb_branches parameter
void Component::set_nb_branches() {
	if(type == 'Q'){
		nb_branches = 3;
	} else {
		nb_branches = 2;
	};
}



// Overloading the >> operator to read a Component from input
istream &operator>>(istream &input, Component &s) {
	char _type;
	input >> _type;
	s.type=_type;
	
	string _name;
	input >> _name;
	s.name = _name;
	
	s.set_nb_branches();
	
	string _node;
	for(int i=0 ; i<s.nb_branches ; i++) {
		input >> _node;
		s.nodes.push_back(_node);
	}
	
	string _value_type;
	if(s.type=='Q'){
		s.transistor_type=_value_type;
	} else {
		s.value=_value_type;
	}
	
	return input;
}

// Overloading the << operator to print a Component
ostream &operator<<(ostream &output, const Component &s) {
	output << s.type << s.name << " ";
	for(int i=0 ; i < s.nb_branches ; i++) {
		output << s.nodes[i] << " ";
	}
	output << s.value_type();
	return output;
}



// Overloading the >> operator to read a Network from input in the SPICE format
istream &operator>>(istream &input, Network &s) {
	//Read the components
	Component _x;
	while(input.peek() != ('.' | '*')) {
		input >> _x;
		s.components.push_back(_x);
	}
	//Ignore the 
	//Read the instruction
	assert(input.peek() == ('.' | '*'));
	string _instruction;
	input >> _instruction;
	
		
	return input;
}
	
// Overloading the << operator to print a Network (for debugging purposes)
ostream &operator<<(ostream &output, const Network &s) {
	//Output the components
	for(int i=0 ; i < s.components.size() ; i++) {
		output << s.components[i] << endl;
	}
	
	//Output the instruction
	output << ".tran 0 " << s.instruction.stop_time << " 0 " << s.instruction.timestep << endl << ".end";
	return output;
}
