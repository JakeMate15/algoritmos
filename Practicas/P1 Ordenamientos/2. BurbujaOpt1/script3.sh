#!/bin/bash
dir=''
gcc Burbuja_Optimizada_1.c tiempo.c -o ord.exe
./ord.exe 3000000 < $dir > salida3.txt
./ord.exe 4000000 < $dir >> salida3.txt
./ord.exe 5000000 < $dir >> salida3.txt
./ord.exe 6000000 < $dir >> salida3.txt
./ord.exe 10000000 < $dir >> salida3.txt