#!/bin/bash
gcc lineal.c tiempo.c -o busqueda.exe
./busqueda.exe 1000000 < numDes.txt > salida.txt
./busqueda.exe 2000000 < numDes.txt >> salida.txt
./busqueda.exe 3000000 < numDes.txt >> salida.txt
./busqueda.exe 4000000 < numDes.txt >> salida.txt
./busqueda.exe 5000000 < numDes.txt >> salida.txt
./busqueda.exe 6000000 < numDes.txt >> salida.txt
./busqueda.exe 7000000 < numDes.txt >> salida.txt
./busqueda.exe 8000000 < numDes.txt >> salida.txt
./busqueda.exe 9000000 < numDes.txt >> salida.txt
./busqueda.exe 10000000 < numDes.txt >> salida.txt
