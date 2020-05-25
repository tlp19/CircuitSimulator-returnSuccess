#include "network_functions.cpp"

int main(){


vector<Component> c;
Instruction instruction;

Network x;

x.instruction.stop_time = "2";
x.instruction.timestep = "0.2";

Component resistor;
resistor.type = 'R';
resistor.name = "1";
resistor.nb_branches = 2;
resistor.nodes.push_back("0");
resistor.nodes.push_back("N1");
resistor.value = "12k";

c.push_back(resistor);

Component cap;
cap.type = 'C';
cap.name = "1";
cap.nb_branches = 2;
cap.nodes.push_back("N1");
cap.nodes.push_back("N2");
cap.value = "0.1";

c.push_back(cap);

x.components = c;

cout<< x<< endl;

}
