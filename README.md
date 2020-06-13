# returnSuccess // ELEC40006

This is the GitHub repository containing all our files for our Final Project of EEE/EIE Year 1 at Imperial College London (2019/2020).

Code written by :
  - Bertil de Germay de Cirfontaine
  - Daniel Romano
  - Tanguy Perron


# Prerequisites

Boost 1.71.0 was used to write the Matrix library that we use. Therefore, it is required in order to compile our simulator (see below in "Project files" for installation command).
The rest of the files were written using standard C++ libraries on Ubuntu and compiled using GCC 7.5.0.


# Guidelines to use the simulator

  - There is already a compiled version of our simulator called "Simulator".
  - To compile the simulator again, use `$ g++ simulator.cpp -o Simulator` in the main directory of the project folder.
  - To run the simulator, use the command `$ ./Simulator < input_circuit.txt`
  - The output is automatically recorded in a file simdata.txt (if it previously exists, it will be overwritten).

#### Note
  - When using inductors and capacitors, make sure to use a timestep a lot smaller than the smaller period of the sources in the circuit (around at least 100 times smaller works best).


# Project files

## Libraries and other external files:
  - Matrix library \[matrix_library/\] - by hbtalha \[[Library GitHub Repository](https://github.com/hbtalha/Matrix-Library)\]
    - Matrix.h - merged header of our Matrix struct and the one from the library
    - Matrix.cpp - definitions for the methods of the library
  - Boost - required by the matrix library to compile the program
    - Install using: `$ sudo apt-get install libboost-all-dev`
    
  - plotsim.m [matlab/] - MatLab program given to plot the results of our simulation

## List of program files:
  - network_header.hpp
  	- Contains all network structures and classes, as well as all important function declarations.
  - network_functions.cpp	
  	- Contains all definitions of the functions associated with the reading of a network.
  - analysis_header.hpp
    - Contains all structs, classes and function declarations regarding the analysis of a network.
  - analysis_functions.cpp
    - Contains all definitions of the functions associated with the analysis of a network.
  - simulator.cpp
    - AC simulator: our final program.

## List of test files:
Test programs [test_programs/] :
  - test\_1\_network\_output.cpp
    - Test program that establishes a Network and then tests the output capability of the main code.
  - test\_2\_network\_io.cpp
    - Simple test program that reads a Networks and prints it directly.
  - test\_3\_analysis\_listnodesandtimes.cpp
    - Test program that reads and prints a network, and then also prints the sorted list of its nodes.
  - simulator_dc.cpp
    - Simple DC simulator (one interation with t=0).
    
Test circuits [test_circuits/] :
  - test\_circuit\_1.txt
    - [I/O] A simple input file to test the i/o capabilities. [not a tested working circuit]
  - test\_circuit\_2.txt
    - [I/O] A more complex input circuit. [not a tested working circuit]
  - test\_circuit\_3.txt
    - [General] A simple test circuit.
  - test\_circuit\_4.txt
  	- [Analysis] Full circuit with voltage sources and resistors to test the conductance matrix.
  - test\_circuit\_5.txt
    - [Analysis] Same as test\_circuit\_3 but using unusual node names.
  - test\_circuit\_6.txt
    - [Debug DC] Circuit for debugging purpuses: similar to circuit 4.
  - test\_circuit\_7.txt
    - [DC] Same as circuit 6, but using an ungrounded current source.
  - test\_circuit\_8.txt
    - [DC] Similar to circuit 4, but with a current source and testing edge cases.
  - test\_circuit\_9.txt
  	- [AC (only R)] Similar to circuit 4, but with a sine voltage source, a current source and more sensible .tran instructions.
  - test\_circuit\_10.txt
    - [AC] Similar to circuit 9, but with C and L instead of some resistors.
  - test\_circuit\_11.txt
    - [AC] RCL test circuit
  - test\_circuit\_12.txt
    - [AC] RC test circuit
  - test\_circuit\_13.txt
    - [AC] RL test circuit
  - test\_circuit\_14.txt
    - [DC] RC test circuit
  - test\_circuit\_15.txt
    - [DC] Two capacitors in parallel : doesn't work (conductance matrix not invertible).
  - test\_circuit\_16.txt
    - [DC] RCC circuit - A resistor and two capacitors in parallel.
  - test\_circuit\_17.txt
    - [AC] RCC circuit - A resistor and two capacitors in parallel.
  - test\_circuit\_complex.txt
    - [AC] Complex circuit to test the capabilities of our simulator.
  	  
## Debugging files [debugging/]:
  - debug.sh - Debugging script that compiles simulator_ac.cpp with debugging instruction for runtime
