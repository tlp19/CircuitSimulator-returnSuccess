#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <limits>
#include "network_header.hpp"

using namespace std;

struct Matrix
{
    int rows;
    int cols; 
    vector<double> values;

    void resize(int rows, int cols)
    {
        this->rows=rows;
        this->cols=cols;
    }
    void write(int r, int c, Component v)
    {
        values[r*cols+c] = v.num_value;
    }
    double read(int r, int c)
    {
        return values[r*cols+c];
    }

    vector<int> extract_node_number(vector<string> nodenames){
        for(int i=0; i < nodenames.size(); i++){
            //for every node name do this:
            string name = nodenames[i];
            int n = name.length();
            char x = name[n-1]; 
            //convert the char to an int
            char y = 'x'; 
            int a = y;
            vector<int> lastdigit;
            lastdigit.push_back(a);// for every resistor I store the 2 numbes which represent the terminal nodes
            }  
    }

    void write_resistor_conductance(vector<Component> resistor_list){
    
        for(int i=0; i < resistor_list.size(); i++)
        {
           vector<string> nodenames = resistor_list[i].nodes; //vector of strings cointaining list of nodes.
           //for a resistor it should only have 2 strings in it
           int value = resistor_list[i].num_value; //value of each resistor
           //extract the character at the end of the 2 node names (it corresponds to the node number)
           vector<int> lastdigit = extract_node_number(nodenames);
           int G =-1/value;
           //check if it's connected to ground       
           if (lastdigit[0]==0 || lastdigit[1] == 0 ){
                    //diagonal() 
                        for(int i=1; i<=size; i++){
                         if(lastdigit[0]==i || lastdigit[1]==i ){
                         int r=i-1; int c=i-1;
                         values[r*cols+c] = G;
                         }
                        }
                    
                    } else {
                    int a = lastdigit[0];
                    int b = lastdigit[1];
                    int r=a-1; int c=b-1;
                    values[r*cols+c] = G;
                    }
        
        }
     
    }
    
    
};


int main()
{
    
    Network x;
	cin >> x;

    vector<Component> input = x.components; //list of components
    vector<string> list_of_nodes = x.list_nodes(); //list of nodes in the circuit including ground
    int size = list_of_nodes.size() - 1; //number of nodes excluding ground

    vector<Component> resistor_list; //list of resistors
    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='R'){
        resistor_list.push_back(x);
        }
    }

    //square matrix of conductance (resistors only)
    Matrix conduct;
    conduct.resize(size,size);
    conduct.write_resistor_conductance(resistor_list);

      /*
    Matrix allvoltages; //vertical matrix v1,v2,v3,v4,v5 ecc... 
    allvoltages.resize(size,1);
    
    for(int i=0; i < size; i++){

        int rr=i;
        Component vv = //can't define this because uknown voltages aren't components
        allvoltages.write(rr, 1, vv);
    }
    */
   

    vector<Component> voltagesource_list; //list of voltagesources
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
    

    }

    
    




