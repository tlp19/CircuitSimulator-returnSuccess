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

    void write_conductance(vector<Component> resistor_list){
    
        for(int i=0; i < resistor_list.size(); i++)
        {
           vector<string> nodenames = resistor_list[i].nodes; //vector of strings cointaining list of nodes.
           //should only have 2 strings in it
           int value = resistor_list[i].num_value; //value of each resistor
           //extract the character at the end of the 2 node names (it corresponds to the node number)
           vector<int> lastdigit = extract_node_number(nodenames);
           int G =-1/value;
           //check if it's connected to ground       
           if (lastdigit[0]==0 || lastdigit[1] == 0 ){
                    //diagonal() 
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
    //input vector
    vector<Component> input;

    //vector that will fill the voltage matrix
    vector<Component> voltage_list;
    //number of voltages = number of nodes(exluding ground) = size of our matrices;
    int size = voltage_list.size(); 

    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='V'){
        voltage_list.push_back(x);
        }
    }
    
    //vertical matrix of voltages
    Matrix vol;
    vol.resize(size,1);
    
    for(int i=0; i < voltage_list.size(); i++)
    {
        int rr=i;
        Component vv = voltage_list[i];
        vol.write(rr, 1, vv);
    }

    //vector that will fill the current matrix
    vector<Component> current_list;

    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='I'){
        current_list.push_back(x);
        }
    }
    
    //vertical matrix of currents
    Matrix current;
    int size = current_list.size();
    current.resize(size,1);
    
    for(int i=0; i < current_list.size(); i++)
    {
        int rr=i;
        Component vv = current_list[i];
        current.write(rr, 1, vv);
    }
    
    //vector that will fill the conductance matrix
    vector<Component> resistor_list;

    for (int i=0; i < input.size(); i++)
    {  
        Component x = input[i]; 
        if( x.type=='R'){
        resistor_list.push_back(x);
        }
    }

    //square matrix of conductance
    Matrix conduct;
    conduct.resize(size,size);
    conduct.write_conductance(resistor_list);
   
    }

    
    




