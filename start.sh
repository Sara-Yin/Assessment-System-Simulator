#!/bin/bash
git clone https://github.com/Sara-Yin/Assessment-System-Simulator.git
g++ -c main.cpp -o main.o
g++ -c Resource_Nodes.cpp -o Resource_Nodes.o
g++ -c Scheduler.cpp -o Scheduler.o
g++ -c User_Job.cpp -o User_Job.o
g++ main.o Resource_Nodes.o Scheduler.o User_Job.o -o run
./run