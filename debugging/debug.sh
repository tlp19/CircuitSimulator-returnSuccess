#!/bin/bash

g++ simulator.cpp -fsanitize=address -g -o Simulator_debug
