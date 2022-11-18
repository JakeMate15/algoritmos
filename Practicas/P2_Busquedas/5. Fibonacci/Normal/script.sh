#!/bin/bash
dir="/mnt/c/Users/erikm/Desktop/algoritmos/Practicas/P2_Busquedas/10millones.txt"
gcc fibo.c tiempo.c -o busqueda.exe
./busqueda.exe 1000000 < numOrd.txt > salida.txt
./busqueda.exe 2000000 < numOrd.txt >> salida.txt
./busqueda.exe 3000000 < numOrd.txt >> salida.txt
./busqueda.exe 4000000 < numOrd.txt >> salida.txt
./busqueda.exe 5000000 < numOrd.txt >> salida.txt
./busqueda.exe 6000000 < numOrd.txt >> salida.txt
./busqueda.exe 7000000 < numOrd.txt >> salida.txt
./busqueda.exe 8000000 < numOrd.txt >> salida.txt
./busqueda.exe 9000000 < numOrd.txt >> salida.txt
./busqueda.exe 10000000 < numOrd.txt >> salida.txt