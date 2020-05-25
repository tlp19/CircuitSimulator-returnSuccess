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
	input >> _value_type;
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



// Overloading the >> operator to read an Instruction from input in the SPICE format
istream &operator>>(istream &input, Instruction &s) {
	string _name;
	cin >> _name;
	if(_name==".end") {
		s.is_end=true;
	} else {
		s.is_end=false;
		float arg0;
		cin >> arg0;
		string _stop_time;
		cin >> _stop_time;
		s.stop_time=_stop_time;
		cin >> arg0;
		string _timestep;
		cin >> _timestep;
		s.timestep = _timestep;
	}
	return input;
}



// Overloading the >> operator to read a Network from input in the SPICE format
istream &operator>>(istream &input, Network &s) {
	Component _x;
	Instruction _instruction;
	while(input.good()) {
		if(input.peek()=='*') {
			//Ignore a comment
//			cerr << "comment" << endl;
			input.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			if (input.peek()=='.') {
				//Read an instruction
//				cerr << "instruction" << endl;
				input >> _instruction;
				if(_instruction.is_end==false){
					s.instruction=_instruction;
					input.ignore(numeric_limits<streamsize>::max(), '\n');
				} else {
					return input;
				}
			} else {
				//Read a component
//				cerr << "component" << endl;
				input >> _x;
				s.components.push_back(_x);
				input.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
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


//Convert the litteral value from string to double
double get_numerical(string value){
	string num , letter;
	for (int i=0; i<value.length() ; i++){
		if ( isdigit(value[i])){
			num.push_back(value[i]);
			} else if((value[i]>='A' && value[i]<= 'Z') || (value[i]>= 'a' && value[i] <= 'z')){
				letter.push_back(value[i]);
				}
		} 
	double num_list = stod(num);
	double total;

	if (letter[0] == 'p'){
		total = num_list * pow(10, -12);
		return total;
		} else if (letter[0] == 'n'){
			total = num_list * pow(10,-9);
			return total;
		} else if (letter[0] == 'u'){
			total = num_list * pow(10,-6);
			return total;
		} else if (letter[0] == 'm'){
			total = num_list *  pow(10,-3);
			return total;
		} else if (letter[0] == 'k'){
			total = num_list * pow(10,3);
			return total;
		} else if (letter[0] == 'M'){
			total = num_list * pow(10,6);
			return total;
		} else if (letter[0] == 'G'){
			total = num_list * pow(10,9);
			return total;
		} else {
			return num_list;
		}
	}
