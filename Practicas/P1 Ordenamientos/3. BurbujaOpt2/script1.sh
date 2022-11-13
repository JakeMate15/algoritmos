#!/bin/bash
dir=''
gcc Burbuja_Optimizada_2.c tiempo.c -o ord.exe
./ord.exe 500000 < $dir > salida1.txt