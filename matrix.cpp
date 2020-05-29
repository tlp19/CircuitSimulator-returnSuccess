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
    vector<Component> values;

    void resize(int rows, int cols)
    {
        this->rows=rows;
        this->cols=cols;
    }
    void write(int r, int c, Component v)
    {
        values[r*cols+c] = v;
    }
    Component read(int r, int c)
    {
        return values[r*cols+c];
    }
    void write_conductances(int r, int c, Component G){
        //for each resister we check its vector of string nodes to see to what it is connected
        int nofnodes = G.nodes.size();
        for(int i=0; i < nofnodes; i++){
             string name = G.nodes[i]; //name is th string corresponding to each node name
             int N = name.size();
             if (name[N-1] == "1"){
                 //it is connected to node 1 and should be included in the sum to obtain G11
             } else if(name[N-1] == "2"){
                 // 
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
    
    for(int i=0; i < resistor_list.size(); i++)
    {
        int row, collumn;
        Component G;
        conduct.write_conductances(row, collumn, G);
}
    }

    
    




