#include "analysis_functions.cpp"

using namespace std;


struct Matrix
{
    int rows;
    int cols; 
    vector<double> values;


    void resize(int rows, int cols)
    {
    	cerr << "In: resize()" << endl; 
        this->rows=rows;
        this->cols=cols;
//NEW: previously wasn't resizing the vector values
        values.resize(rows*cols);
        cerr << "Rows: " << rows << endl;
        cerr << "Columns: " << cols << endl;
        cerr << "-> Size: " << values.size() << endl;
    }
    
    void write(int r, int c, Component v)
    {
    	cerr << "In: write(Component)" << endl;
        values[r*cols+c] = v.num_value;
    }

    double read(int r, int c)
    {
    	cerr << "In: read()" << endl;
        return values[r*cols+c];
    }
    
    void fill_with_zeros() {
    	cerr << "In: fill_with_zeros()" << endl;
		for(int i = 0 ; i < rows ; i++) {
			for(int j = 0 ; j < cols ; j++) {
				double zero = 0;
				values[i*cols+j] = zero;
			}
		}
    }

	vector<int> extract_node_number(vector<string> nodenames){
    	cerr << "In: extract_node_number()" << endl;
    	vector<int> lastdigit = {};
        for(int i=0; i < nodenames.size(); i++){
            //for every node name do this:
            string name = nodenames[i];
            int n = name.length();
            char x = name[n-1]; 
            //convert the char to an int (with ascii shift)
            int a = int(x) - 48;
            lastdigit.push_back(a);// for every resistor I store the 2 numbers which represent the terminal nodes
		}
			cerr << "Between the nodes: " << lastdigit[0] << "-" << lastdigit[1] << endl;
//NEW: previously wasn't returning anything, hence the weird values
    return lastdigit;
	}
	
	void print() const {
    	cerr << "In: print()" << endl;
		for(int i = 0 ; i < rows ; i++) {
			for(int j = 0 ; j < cols ; j++) {
				cout << values[i*cols+j] << " ";
			}
			cout << endl;
		}
	}

	void write_resistor_conductance(Network input_network) {
    	cerr << "In: write_resistor_conductance()" << endl;
    	vector<Component> input_components = input_network.components; //list of components
		vector<string> list_of_nodes = input_network.list_nodes(); //list of nodes in the circuit including ground
		int size = list_of_nodes.size() - 1; //number of nodes excluding ground
		vector<Component> resistor_list; //list of resistors
		for (int i=0; i < input_components.size(); i++)
		{  
		    Component x = input_components[i]; 
		    if( x.type=='R'){
		    resistor_list.push_back(x);
		    }
		}
    	
        for(int i=0; i < resistor_list.size(); i++)
        {
           	vector<string> nodenames = resistor_list[i].nodes; //vector of strings containing list of nodes.
           	//for a resistor it should only have 2 strings in it
           	int value = resistor_list[i].num_value; //value of each resistor
           	//extract the character at the end of the 2 node names (it corresponds to the node number)
           	vector<int> lastdigit = extract_node_number(nodenames);
//NEW: was initially an int, and then we needed 1.0 otherwise it converted itself again to an int.
           	double G = 1.0/value;
           	cerr << "Conductance value: " << G << endl;
          	//check if it's connected to ground       
         	if (lastdigit[0]==0 || lastdigit[1] == 0 ){
                    //diagonal
//NEW: wrong way to think about it
           	/*	for(int i=1; i<=size; i++){
                	if(lastdigit[0]==i || lastdigit[1]==i ){ */
                	int i = lastdigit[0] + lastdigit[1] - 1;
                	cerr << "In the matrix at the coordinates: (" << i << ";" << i << ") [diagonal]" << endl;
                    values[i*cols+i] += G;
             //		}
             //	}     
			} else {
				int a = lastdigit[0] - 1;
				int b = lastdigit[1] - 1;
				cerr << "In the matrix at the coordinates: (" << a << ";" << b << ")" << endl;
				cerr << "In the matrix at the coordinates: (" << b << ";" << a << ")" << endl;
				values[a*cols+b] = -G;
				values[b*cols+a] = -G;
				values[a*cols+a] += G;
				values[b*cols+b] += G;
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
/* USELESS NOW
    vector<Component> resistor_list; //list of resistors
    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='R'){
        resistor_list.push_back(x);
        }
    }
*/
    //square matrix of conductance (resistors only)
    Matrix conduct;
    conduct.resize(size,size);
    conduct.fill_with_zeros();
	conduct.print();
    conduct.write_resistor_conductance(/*input*/ x);
	
	
      /*
    Matrix allvoltages; //vertical matrix v1,v2,v3,v4,v5 ecc... 
    allvoltages.resize(size,1);
    
    for(int i=0; i < size; i++){

        int rr=i;
        Component vv = //can't define this because uknown voltages aren't components
        allvoltages.write(rr, 1, vv);
    }
    */
   
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
    }

    vector<Component> currentsource_list; //list of currentsources
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
