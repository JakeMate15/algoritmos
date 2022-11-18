#!/bin/bash
gcc linealConHIlos.c tiempo.c -lpthread -o busqueda.exe
./busqueda.exe 1000000 100 < numDes.txt > salida.txt
./busqueda.exe 2000000 100 < numDes.txt >> salida.txt
./busqueda.exe 3000000 100 < numDes.txt >> salida.txt
./busqueda.exe 4000000 100 < numDes.txt >> salida.txt
./busqueda.exe 5000000 100 < numDes.txt >> salida.txt
./busqueda.exe 6000000 100 < numDes.txt >> salida.txt
./busqueda.exe 7000000 100 < numDes.txt >> salida.txt
./busqueda.exe 8000000 100 < numDes.txt >> salida.txt
./busqueda.exe 9000000 100 < numDes.txt >> salida.txt
./busqueda.exe 10000000 100 < numDes.txt >> salida.txt