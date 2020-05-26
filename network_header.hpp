#ifndef network_hpp
#define network_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <limits>

using namespace std;



/* -- CLASSES AND STRUCTURES -- */


// Struct to define a sine function (for components V and I)
struct Sine_function {
	bool is_sine;
	double dc_offset;
	double amplitude;
	double frequency;
};

// Struct to define a specific component inside the circuit
class Component {
  public:
	char type;						//Type of the component; either V, I, R, C, L, D or Q
	string name;					//Arbitrary name of the component
	int nb_branches;				//Number of nodes that the component is connected to
	vector<string> nodes;			//List of the nodes that the component is connected to (2 or 3)
	string value;					//Litteral value of the component (in Ohms, Farads, etc.)
	double num_value;				//Numerical value extracted from the value variable
//	Sine_function function;			//Sine function for V and I components
//	string transistor_type;			//In case the component is a transistor, this is either NPN or PNP


	string value_or_type() const;	//Returns the transis. type if Q, returns the value otherwise
	void set_nb_branches();			//Fills in the nb_branches member variable
};

// Derived class of Component
class VIsource: public Component {
  public:
	bool is_v;						//1 if V, 0 if I
	double dc_value;				//Contains the DC value (if there is one)
	Sine_function function;			//Contains the Sine function (if there is one)
	bool is_dc;						//1 if DC, 0 if using a function
};


// Struct to store the analysis instruction of the .tran line in the input
struct Instruction{
	bool is_end;					//1 if it's the .end instruction, 0 otherwise
	string stop_time;				//Second argument of the .tran instruction
	string timestep;				//Fourth argument of the .tran instruction
};


// Struct to store the whole Network as defined in the input SPICE file, as well as the .tran instruction
struct Network {
	vector<Component> components;	//List of the components in the network
	Instruction instruction;		//Specification of the .tran instruction to analyse the circuit
};



/* --- NETWORK FUNCTIONS --- */


// Overloading the >> operator to read a Sine_function from input
istream &operator>>(istream &input, Sine_function &s);

// Overloading the >> operator to read a Component from input
istream &operator>>(istream &input, Component &s);

// Overloading the << operator to print a Component
ostream &operator<<(ostream &output, const Component &s);

// Overloading the >> operator to read an Instruction from input in the SPICE format
istream &operator>>(istream &input, Instruction &s);

// Overloading the >> operator to read a Network from input in the SPICE format
istream &operator>>(istream &input, Network &s);

// Overloading the << operator to print a Network (for debugging purposes)
ostream &operator<<(ostream &output, const Network &s);

//Convert the litteral value from string to double
double get_numerical(string value);

#endif
