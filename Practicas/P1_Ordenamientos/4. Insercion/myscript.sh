#!/bin/bash
dir=''
gcc Insercion.c tiempo.c -o ord.exe
./ord.exe 500000 < $dir > salida1.txt
./ord.exe 1000 < $dir > salida2.txt
./ord.exe 2000 < $dir >> salida2.txt
./ord.exe 3000 < $dir >> salida2.txt
./ord.exe 4000 < $dir >> salida2.txt
./ord.exe 5000 < $dir >> salida2.txt
./ord.exe 8000 < $dir >> salida2.txt
./ord.exe 10000 < $dir >> salida2.txt
./ord.exe 50000 < $dir >> salida2.txt
./ord.exe 100000 < $dir >> salida2.txt
./ord.exe 150000 < $dir >> salida2.txt
./ord.exe 200000 < $dir >> salida2.txt
./ord.exe 300000 < $dir >> salida2.txt
./ord.exe 400000 < $dir >> salida2.txt
./ord.exe 500000 < $dir >> salida2.txt
./ord.exe 600000 < $dir >> salida2.txt
./ord.exe 700000 < $dir >> salida2.txt
./ord.exe 800000 < $dir >> salida2.txt
./ord.exe 900000 < $dir >> salida2.txt
./ord.exe 1000000 < $dir >> salida2.txt
./ord.exe 1500000 < $dir >> salida2.txt
./ord.exe 2000000 < $dir >> salida2.txt