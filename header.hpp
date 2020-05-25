#ifndef header_hpp
#define header_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

using namespace std;

struct Component {
	char type;
	string name;
	int nb_branches;
	vector<string> nodes;
	float value;
	string transistor_type;

}

struct

class Network {
	vector<Component> components;
	vector<Instruction> instructions;
}

int find_nb_branches(Component input);


#endif
