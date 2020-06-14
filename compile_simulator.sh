#!/bin/bash
set -e

g++ matrix_library/Matrix.cpp network_functions.cpp analysis_functions.cpp simulator.cpp -o Simulator

echo "The simulator was compiled to ./Simulator"
