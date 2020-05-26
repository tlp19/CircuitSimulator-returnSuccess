#include "network_header.hpp"

using namespace std;



/* --- DEBUGGING FUNCTIONS --- */


// Overloading to print a vector<string> to cout
ostream &operator<<(ostream &output, const vector<string> &s) {
	for(int i=0 ; i < s.size() ; i++) {
		output << s[i] << " ";
	}
	return output;
}



/* --- PRACTICAL FUNCTIONS --- */


//Writes a Sine_function as a string
string Component::function_to_string() const {
	string function_to_string;
	function_to_string.push_back("SINE(")
	function_to_string.push_back(function.dc_offset)
	function_to_string.push_back(" ")
	function_to_string.push_back(function.amplitude)
	function_to_string.push_back(" ")
	function_to_string.push_back(function.frequency)
	function_to_string.push_back(")")
	return function_to_string;
}

// Returns either the value or the transistor type depending on the component
string Component::value_or_type() const {
	if(type=='Q') {
		return transistor_type;
	} else if() {
		return s.function_to_string();
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


// Overloading the >> operator to read a Sine_function from input
istream &operator>>(istream &input, Sine_function &s) {
	string _dc_offset;
	cin >> _dc_offset;
	s.dc_offset = get_numerical(_dc_offset);
		
	string _amplitude;
	cin >> _amplitude;
	s.amplitude = get_numerical(_amplitude);
	
	string _frequency;
	cin >> _frequency;
	s.frequency = get_numerical(_frequency);
			
	return input;
}

// Overloading the >> operator to read a Component from input
istream &operator>>(istream &input, Component &s) {
	char _type;
	input >> _type;
	s.type=_type;
	
	string _name;
	input >> _name;
	s.name = _name;
	
	s.nodes = {};
	s.set_nb_branches();
	
	string _node;
	for(int i=0 ; i<s.nb_branches ; i++) {
		input >> _node;
		s.nodes.push_back(_node);
	}
	assert(s.nodes.size()==s.nb_branches);
	
	if((s.type=='V')||(s.type=='I')) {
		//if peek 'S' -> Sine_function
		//else -> value
		if(input.peek()=='S') {
			s.has_function = true;
			Sine_function _function;
			input >> _function;
			s.function = _function;
		} else {
			s.has_function = false;
			string _value;
			input >> _value;
			s.value = _value;
		}
	} else if(s.type=='Q'){
		string _transistor_type;
		input >> _transistor_type;
		s.transistor_type=_transistor_type;
	} else {
		string _value;
		input >> _value;
		s.value=_value;
	}
	
	return input;
}

// Overloading the << operator to print a Component
ostream &operator<<(ostream &output, const Component &s) {
	output << s.type << s.name << " ";
	for(int i=0 ; i < s.nb_branches ; i++) {
		output << s.nodes[i] << " ";
	}
	output << s.value_or_type();
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
			input.ignore(numeric_limits<streamsize>::max(), '\n');
		} else if (input.peek()=='.') {
			//Read an instruction
			input >> _instruction;
			if(_instruction.is_end==false){
				s.instruction=_instruction;
				input.ignore(numeric_limits<streamsize>::max(), '\n');
			} else {
				return input;
			}
		} else {
			//Read a component
			input >> _x;
			s.components.push_back(_x);
			input.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return input;
}
	
// Overloading the << operator to print a Network (for debugging purposes)
ostream &operator<<(ostream &output, const Network &s) {
	for(int i=0 ; i < s.components.size() ; i++) {
		output << s.components[i] << endl;
	}
	output << ".tran 0 " << s.instruction.stop_time << " 0 " << s.instruction.timestep << endl << ".end";
	return output;
}


/*Convert a litteral value from string to double by taking the last letter of the string and analysing it.
It is used in the sine function operator to isolate the member variables, digits from letter
and to detect the multipliers following a number.
Allows you to split a string into different respective categories: number letter and symbol */
double get_numerical(string value){
	string num , letter , symbol;
	for (int i=0; i<value.length() ; i++){
		if ( isdigit(value[i])){
			num.push_back(value[i]);
			} else if((value[i]>='A' && value[i]<= 'Z') || (value[i]>= 'a' && value[i] <= 'z')){
				letter.push_back(value[i]);
				} else {
					symbol.push_back(value[i]);
					}
		} 
	double num_list = stod(num);
	double total;
	int n = letter.length();
	
	if (letter[n-1] == 'p'){
		total = num_list * pow(10, -12);
		return total;
		} else if (letter[n-1] == 'n'){
			total = num_list * pow(10,-9);
			return total;
		} else if (letter[n-1] == 'u'){
			total = num_list * pow(10,-6);
			return total;
		} else if (letter[n-1] == 'm'){
			total = num_list *  pow(10,-3);
			return total;
		} else if (letter[n-1] == 'k'){
			total = num_list * pow(10,3);
			return total;
		} else if (letter[n-1] == 'g'){
			total = num_list * pow(10,6);
			return total;
		} else if (letter[n-1] == 'G'){
			total = num_list * pow(10,9);
			return total;
		} else {
			return num_list;
		}
}
