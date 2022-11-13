//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Enero 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Burbuja Simple
//Compilación: "gcc Burbuja_Simple.c tiempo.x  -o Burbuja_Simple" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./Burbuja_Simple n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int * crearArreglo(int);
void BurbujaSImple(int*,int);

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
	int *A; //A es un puntero que guardara la direccion del arreglo al ordenar
	int i;	//Variable para loops

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
	BurbujaSImple(A,n);
	
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
	Algoritmo de ordenamiento "Burbuja Simple"
	------------------------------------------
	Argumentos:
	int A[], arreglo con los números a ordenar
	int n, tamaño del arreglo/problema
	Variables utilizadas:
	int i, j: usadas para los loops
	int aux: auxiliar para poder realizar el intercambio de números
*/
void BurbujaSImple(int A[],int n){	//Nota: int*A == int A[];
	int i,j,aux;
	
	//loop para aplicar la misma ejecución de comparación en todas las posiciones y verificar ordenamiento correcto
	for(i=0;i<=n-2;i++){
		//loop para recorrer el arreglo e ir comparando
		for(j=0;j<=n-2;j++){
			//En caso de que el número sea mayor al siguiente, intercambian posiciones
			if(A[j]>A[j+1]){
				aux=A[j];
				A[j]=A[j+1];
				A[j+1]=aux;
			}
		}
	}
	
}