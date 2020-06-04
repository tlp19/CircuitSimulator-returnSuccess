#include "analysis_functions.cpp"

using namespace std;

char tab = 9;


struct Matrix
{
    int rows;
    int cols; 
    vector<double> values;

	// Resizes a matrix
    void resize(int rows, int cols)
    { 
        this->rows=rows;
        this->cols=cols;
        values.resize(rows*cols);
        cerr << "Rows: " << rows << endl;
        cerr << "Columns: " << cols << endl;
        cerr << "-> Size: " << values.size() << endl;
    }
    
    // Writes the value of a component inside the matrix
    void write(int r, int c, Component v)
    {
        values[r*cols+c] = v.num_value;
    }

	// Returns the value stored in the matrix at a specific location
    double read(int r, int c)
    {
        return values[r*cols+c];
    }
    
    // Fills a matrix with zeros (of the type double)
    void fill_with_zeros() {
		for(int i = 0 ; i < rows ; i++) {
			for(int j = 0 ; j < cols ; j++) {
				double zero = 0;
				values[i*cols+j] = zero;
			}
		}
    }

	// Returns the last digit of the node name
	vector<int> extract_node_number(vector<string> nodenames){
    	vector<int> node_nb = {};
        for(int i=0; i < nodenames.size(); i++){
            /*string name = nodenames[i];
            int n = name.length();
            char x = name[n-1];
            char y = name[n-2]; 
            //convert the char to an int (with ascii shift)
            int a = int(x) - 48;
            int b = int(y) - 48;
            node_nb.push_back(b*10+a); */
            node_nb.push_back((int)get_numerical(nodenames[i]));
		}
			cerr << "Between the nodes: " << node_nb[0] << "-" << node_nb[1] << endl;
    return node_nb;
	}
	
	// Prints a matrix to cout
	void print() const {
    	cerr << endl << "We get the following conductance matrix:" << endl;
		for(int i = 0 ; i < rows ; i++) {
			for(int j = 0 ; j < cols ; j++) {
				cout << values[i*cols+j] << tab;
			}
			cout << endl;
		}
		cerr << endl;
	}

	// Fills in the values in the conductance matrix for the resistors present in the circuit
	void write_resistor_conductance(Network input_network) {
    	vector<Component> input_components = input_network.components;
		vector<string> list_of_nodes = input_network.list_nodes();
		vector<Component> resistor_list;
		for (int i=0; i < input_components.size(); i++) {  
		    Component x = input_components[i]; 
		    if( x.type=='R'){
		    resistor_list.push_back(x);
		    }
		}
        for(int i=0; i < resistor_list.size(); i++) {
           	vector<string> nodenames = resistor_list[i].nodes;
           	int value = resistor_list[i].num_value;
           	//extract the character at the end of the 2 node names (it corresponds to the node number)
           	vector<int> node_nb = extract_node_number(nodenames);
           	double G = 1.0/value;
           	cerr << "Conductance value: " << G << endl;
          	//check if it's connected to ground       
         	if (node_nb[0]==0 || node_nb[1]==0){
                //diagonal
            	int index = node_nb[0] + node_nb[1] - 1;
              	cerr << "In the matrix at the coordinates: (" << index << ";" << index << ") [diagonal]" << endl;
            	values[index*cols+index] += G;   
			} else {
				//between two non-ground nodes
				int a = node_nb[0] - 1;
				int b = node_nb[1] - 1;
				cerr << "In the matrix at the coordinates: (" << a << ";" << b << ")" << endl;
				cerr << "In the matrix at the coordinates: (" << b << ";" << a << ")" << endl;
				values[a*cols+b] = -G;
				values[b*cols+a] = -G;
				values[a*cols+a] += G;
				values[b*cols+b] += G;
			}
			cerr << endl;
        }
    }
    
    // Overwrites values of the matrix to consider the cases of voltage sources
    void overwrite_w_voltage_sources(Network input_network) {
    	vector<Component> voltagesource_list;
		for (int i=0; i < input_network.components.size(); i++) {  
			Component x = input_network.components[i]; 
	    	if( x.type=='V'){
			voltagesource_list.push_back(x);
			}
   		}
   		for(int i=0; i < voltagesource_list.size(); i++) {
   			vector<string> nodenames = voltagesource_list[i].nodes;
   			vector<int> node_nb = extract_node_number(nodenames);
   			if (node_nb[0]==0 || node_nb[1]==0){
   				int index = node_nb[0] + node_nb[1] - 1;
   				for(int other_idx = 0 ; other_idx < cols ; other_idx++) {
   					values[index*cols+other_idx] = 0;
   				}
   				values[index*cols+index] = 1;
   			} else {
   				
   			}
        }
   	}
};




/* ---- MAIN ---- */


int main() {
    
    Network x;
	cin >> x;

    vector<Component> input = x.components; //list of components

    vector<string> list_of_nodes = x.list_nodes(); //list of nodes in the circuit including ground
    int size = list_of_nodes.size() - 1; //number of nodes excluding ground

    //square matrix of conductance (resistors only)
    Matrix conduct;
    conduct.resize(size,size);
    conduct.fill_with_zeros();
    conduct.write_resistor_conductance(x);
	
   
//TODO
    /*vector<Component> voltagesource_list; //list of voltagesources
    int n_vsources = voltagesource_list.size(); //number of voltagesources

    for (int i=0; i < input.size(); i++) 
    {  
        Component x = input[i]; 
        if( x.type=='V'){
        voltagesource_list.push_back(x);
        }
    }
    
    Matrix vol; //vertical matrix of voltagesources
    vol.resize(n_vsources,1);

    for(int i=0; i < voltagesource_list.size(); i++)
    {
        int rr=i;
        Component vv = voltagesource_list[i];
        vol.write(rr, 1, vv);
    } */
    conduct.overwrite_w_voltage_sources(x);

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

	conduct.print();
}
