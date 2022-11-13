//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Shell
//Compilación: "gcc Shell.c tiempo.x  -o Shell" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./Shell n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tiempo.h"
 
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void shell(int *,int);
int * crearArreglo(int);

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; 	//n determina el tamaño del algoritmo dado por argumento al ejecutar
	int *A; //A es un puntero que guardará la dirección del arreglo a ordenar
	int i;	//Variables para loops

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n=atoi(argv[1]);
	}

	//******************************************************************	
	//Creación del arreglo
	//******************************************************************	
	A = crearArreglo(n);
	
	for(i=0;i<n;i++){
		scanf("%d",&A[i]); //rellena el arreglo A
	}
	
	//******************************************************************	
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************	
	uswtime(&utime0, &stime0, &wtime0);
	
	//******************************************************************	
	//Algoritmo
	//******************************************************************	
	shell(A,n);

	//******************************************************************	
	//Evaluar los tiempos de ejecución 
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);
	
	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("n = %d\n",n);
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponencial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

	//Terminar programa normalmente	
	exit (0);	
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*
	Creamos el arreglo dinámico
	---------------------------
	Argumentos:
	int n: tamaño del problema
	Variables utilizadas:
	*return* int *array: arreglo con el tamaño asignado
*/
int * crearArreglo(int n){
	int *array;
	
	array = (int *) malloc(sizeof(int) * n);
	
	if(array == NULL){
		printf("No hay memoria disponible para el arreglo");
		exit(1);
	}
	
	return array;
}

/*
	Algoritmo de ordenamiento "Shell"
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int n, tamaño del arreglo/problema
	Variables utilizadas:
	int i: usada para loop
	int k: identifica la mitad del sub-arreglo y es el gap o salto a comparar
	int b: sirve para verificar e numero de intercambios que se realizaron
	int temp: auxiliar para poder realizar el intercambio de números
*/
void shell(int *A, int n){
	int k, i,temp,b;
	//Devuelve la parte entera de la mitad del arreglo
	k=trunc(n/2);
	
	//Se reduce hasta el salto más pequeño para poder comparar en las posiciones que es 1
	while(k>=1){
		b=1;
			//loop que se detiene cuando no hay algún intercambio realizado
			while(b!=0){
  	 			b=0;
  	 			//loop que realiza comparaciones e intercambios
  	 			for(i=k;i<n;i++){
  	 				//si se cumplen intercambian posiciones (i-k va desde la posición inicial hasta k-1 y i va desde k hasta n-1)
  	 				if(A[i-k]>A[i]){
						temp=A[i];
						A[i]=A[i-k];
						A[i-k]=temp;
						b++;
  	 				}
  	 			}
  	 		}
  	 	//Devuelve la parte de la mitad de los sub-arreglos
  	 	k=trunc(k/2);
  	}
}