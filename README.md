# returnSuccess // ELEC40006

This is the GitHub repository containing all our files for our Final Project of EEE/EIE Year 1 at Imperial College London (2019/2020).

Code written by :
	- Bertil de Germay de Cirfontaine
	- Daniel Romano
	- Tanguy Perron


# Prerequisites

Boost 1.71.0 was used to write the Matrix library that we use. Therefore, it is required in order to compile our simulator.
The rest of the files were written using standard C++ libraries on Ubuntu and compiled using GCC 7.5.0.


# Important notes

When using inductors and capacitors, make sure to use a timestep a lot smaller than the smaller period of the sources in the circuit (about 100 times smaller works fine).


# Project files

Libraries and other external files:
  - Matrix library [matrix_library/] - by hbtalha [https://github.com/hbtalha/Matrix-Library]
    - Matrix.h - merged header of our Matrix struct and the one from the library
    - Matrix.cpp - definitions for the methods of the library
  - Boost - required for the matrix library
    - Install using: ```sudo apt-get install libboost-all-dev```
    
  - plotsim.m [matlab/] - MatLab program given to plot the results of our simulation

List of program files:
  - network_header.hpp
  	- Contains all network structures and classes, as well as all important function declarations.
  - network_functions.cpp	
  	- Contains all definitions of the functions associated with the reading of a network.
  - analysis_header.hpp
    - Contains all structs, classes and function declarations regarding the analysis of a network.
  - analysis_functions.cpp
    - Contains all definitions of the functions associated with the analysis of a network.
  - simulator_dc.cpp
    - Simple DC simulator (one interation with t=0).
  - simulator_ac.cpp
    - AC simulator: our final program.

List of test files:
  - Test programs [test_programs/]:
    - test\_1\_network\_output.cpp
  	  - Test program that establishes a Network and then tests the output capability of the main code.
    - test\_2\_network\_io.cpp
  	  - Simple test program that reads a Networks and prints it directly.
  	- test\_3\_analysis\_listnodesandtimes.cpp
  	  - Test program that reads and prints a network, and then also prints the sorted list of its nodes.
  - Test circuits [test_circuits/]:
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
  	  - [AC] Similar to circuit 9, but with C and L instead of some resistors 
  	- test\_circuit\_11.txt
  	  - [AC] RCL test circuit
  	- test\_circuit\_12.txt
  	  - [AC] RC test circuit
  	- test\_circuit\_13.txt
  	  - [AC] RL test circuit
  	  
Debugging files [debugging/]:
  - debug.sh - Debugging script that compiles simulator_ac.cpp with debugging instruction for runtime
