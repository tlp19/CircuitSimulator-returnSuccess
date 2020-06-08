#include "analysis_functions.cpp"

using namespace std;


int main() {
    
    Network x;
	cin >> x;

    vector<string> list_of_nodes = x.list_nodes(); //list of nodes in the circuit including ground
    int size = list_of_nodes.size() - 1; //number of nodes excluding ground

    //square matrix of conductance
    Matrix conduct;
    conduct.resize(size,size);
    
    //fill the conductance matrix with the conductance of the resistors
    conduct.write_resistor_conductance(x);
    cout << conduct << endl;
    
    //overwrite the previous matrix to support voltage sources
    conduct.overwrite_w_voltage_sources(x);
    cout << conduct << endl;
    cout << "-" << endl;
    cout << conduct.inverse() << endl;
    cout << "-" << endl;

//TODO
   /* vector<Component> currentsource_list; //list of currentsources
    int n_csources = currentsource_list.size(); //number of currentsurces

    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='I'){
        currentsource_list.push_back(x);
        }
    }
    
    Matrix current; //vertical matrix of currentsources
    current.resize(n_csources,1);
    
    for(int i=0; i < currentsource_list.size(); i++)
    {
        int rr=i;
        Component vv = currentsource_list[i];
        current.write(rr, 1, vv);
    }

*/
}
