#include "network_functions.cpp"
#include <ctype.h>
#include <stdio.h>


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

cout<< get_numerical("10m") <<endl;


/*int p = pow(10,-12);
int n = pow(10,-9);
int u = pow(10,-6);
int m = pow(10,-3);
int k = pow(10,3);
int Meg = pow(10,6);
int G = pow(10,9);
*/

}
