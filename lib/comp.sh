#!/bin/bash
mpicc  -std=c99 -fPIC -rdynamic -shared  -o  ./T1.so ./T1.c  ../src/obj/qmpi.c  
mpicc  -std=c99 -fPIC -rdynamic -shared  -o  ./T3.so ./T3.c  ../src/obj/qmpi.c 
mpicc  -std=c99 -fPIC -rdynamic -shared  -o  ./T2.so ./T2.c  ../src/obj/qmpi.c
cd mpiP && make clean && make shared --include=../../src/obj/qmpi.h && cd ../ 
