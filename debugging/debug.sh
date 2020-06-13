#!/bin/bash

g++ simulator.cpp -fsanitize=address -g -o Simulator_debug

echo Compiled simulator.cpp to Simulator_debug using runtime debugging parameters
