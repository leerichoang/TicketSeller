#!/bin/bash
rm *.exe
g++ ticket.cpp -pthread -o main.exe
./main.exe
