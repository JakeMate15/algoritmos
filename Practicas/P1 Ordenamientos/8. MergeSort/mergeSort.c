//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: MergeSort
//Compilación: "gcc mergeSort.c tiempo.x  -o mergeSort" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./mergeSort n" (Linux y MAC OS)
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
void mergeSort(int *, int, int);
void merge(int *, int, int, int);
 
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
	//Creacion del arreglo
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
	mergeSort(A, 0, n-1);

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
	
	//Mostrar los tiempos en formato exponecial
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
	Algoritmo de ordenamiento "mergeSort" (Función recursiva que se encarga de dividir el arreglo en sub-arreglos de uno para después ir juntando de manera ordenada)
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	int q, posición mitad del arreglo o sub-arreglo
*/
void mergeSort(int *A, int p, int r){
	int q;
	
	//compara para verificar si las posiciones todavía no colisionan o que la final no sea menor que la inicial
	if(p < r){
		
		q = (p+r)/2; //Automáticamente agarra la parte entera del resultado
		//Divide en 2 subArreglos y realiza recursividad
		mergeSort(A, p, q);
		mergeSort(A, q+1, r);
		//Junta los resultados de manera ordenada
		merge(A, p, q, r);
	}
}

/*
	Algoritmo de ordenamiento "mergeSort" (Función encargada de ir reuniendo de manera ordenada los elementos)
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	int q, posición mitad del arreglo
	Variables utilizadas:
	int k: usada para el loop
	int *C: arreglo que es auxiliar para i
	int l: define el tamaño del arreglo auxiliar
	int i: variable auxiliar para referenciar a la posición inicial del arreglo
	int j: posición auxiliar para referenciar a la posición mitad del arreglo
*/
void merge(int *A, int p, int q, int r){
	int k, *C;
	int l = r-p+1, i = p, j = q+1;
	C = crearArreglo(l);//se crea de forma dinámica el arreglo auxiliar conforme al tamaño calculado
	
	//recorre todo el arreglo auxiliar
	for(k = 0; k < l; k++){
		//La posición i no debe de alcanzar la mitad y j no debe de alcanzar el final del arreglo
		if(i <= q && j <= r){
			//Compara que parte del sub-arreglo es menor y se le asigna al arreglo auxiliar
			if(A[i] < A[j]){
				C[k] = A[i];
				i++;
			}else{
				C[k] = A[j];
				j++;
			}
		//Aqui identifica cada condición anterior para asignar el movimiento
		}else if(i <= q){
			C[k] = A[i];
			i++;
		}else{
			C[k] = A[j];
			j++;
		}
	}
	
	//Acomoda desde la posición inicial hasta la última por parte del arreglo auxiliar
	for(k = p, i = 0; k <= r; k++, i++){
		A[k] = C[i];
	}
}