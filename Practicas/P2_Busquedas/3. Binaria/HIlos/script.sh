#!/bin/bash
gcc hilos.c tiempo.c -lpthread -o busqueda.exe
./busqueda.exe 1000000 100 < numOrd.txt > salida1.txt
./busqueda.exe 2000000 100 < numOrd.txt > salida2.txt
./busqueda.exe 3000000 100 < numOrd.txt > salida3.txt
./busqueda.exe 4000000 100 < numOrd.txt > salida4.txt
./busqueda.exe 5000000 100 < numOrd.txt > salida5.txt
./busqueda.exe 6000000 100 < numOrd.txt > salida6.txt
./busqueda.exe 7000000 100 < numOrd.txt > salida7.txt
./busqueda.exe 8000000 100 < numOrd.txt > salida8.txt
./busqueda.exe 9000000 100 < numOrd.txt > salida9.txt
./busqueda.exe 10000000 100 < numOrd.txt > salida10.txt