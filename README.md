# returnSuccess // ELEC40006 Project
Libraries:
  - Matrix library - by hbtalha [https://github.com/hbtalha/Matrix-Library]
    - Matrix.h - merged header of our Matrix struct and the one from the library
    - Matrix.cpp - definitions for the methods of the library
  - Boost - required for the matrix library
    - Install using: ```sudo apt-get install libboost-all-dev```

List of program files:
  - network_header.hpp
  	- Contains all network structures and classes, as well as all important function declarations.
  - network_functions.cpp	
  	- Contains all definitions of the functions associated with the reading of a network.
  - analysis_header.hpp
    - Contains all structs, classes and function declarations regarding the analysis of a network.
  - analysis_functions.cpp
    - Contains all definitions of the functions associated with the analysis of a network.
  - matrix.cpp
    - Core file of our program.

List of test files:
  - Test programs:
    - test\_1\_network\_output.cpp
  	  - Test program that establishes a Network and then tests the output capability of the main code.
    - test\_2\_network\_io.cpp
  	  - Simple test program that reads a Networks and prints it directly.
  	- test\_3\_analysis\_listnodesandtimes.cpp
  	  - Test program that reads and prints a network, and then also prints the sorted list of its nodes.
  - Test circuits:
	- test\_circuit\_1.txt
  	  - A simple input file to test the i/o capabilities. [not a tested working circuit]
    - test\_circuit\_2.txt
  	  - A more complex input circuit. [not a tested working circuit]
  	- test\_circuit\_3.txt
  	  - A simple test circuit.
  	- test\_circuit\_4.txt
  	  - Full circuit with voltage sources and resistors to test the conductance matrix.
  	- test\_circuit\_5.txt
  	  - Same as test\_circuit\_3 but using unusual node names.
