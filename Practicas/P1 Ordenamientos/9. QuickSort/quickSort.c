//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: QuickSort
//Compilación: "gcc quickSort.c tiempo.x  -o quickSort" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./quickSort n" (Linux y MAC OS)
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
void quickSort(int *, int, int);
int pivot(int *, int, int);
void intercambiar(int *, int, int);

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
	int p, r;

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
	quickSort(A, 0, n-1);
 
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
	Algoritmo de ordenamiento "quickSort" (Función recursiva que se encarga de dividir el arreglo con ayuda del pivotes para ir ordenando)
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	int j, posición del pivote asignado
*/
void quickSort(int *A, int p, int r){
	int j; //La variable será la parte intermediaria del arreglo
	if(p < r){
		//Asigna el pivote con tal de que los elementos más pequeños están a la izquierda y los mayores a la derecha
		j = pivot(A, p, r);
		quickSort(A, p, j-1);
		quickSort(A, j+1, r);
	}
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que asigna el pivote e intercambia la posición de manera que en el lado izquierdo esten los números menores y en el lado derecho esten los número mayores al pivote)
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	int piv, valor del pivote asignado en la posición incial
	int i, variable auxiliar asignada en la posición inicial
	*return* int j, variable auxiliar asignada en la posición final y será retornada como la posición que retoma el pivote
*/
int pivot(int *A, int p, int r){
	//Declaramos el pivote desde el inicio
	int piv = A[p], i = p, j = r;
	//Mientras no se crucen los indices
	while(i < j){
		//Va recorriendo la posición inicial hacia la derecha cuando el pivote siga siendo mayor o igual al número a comparar, así mismo también verifica que los indices no colisionen
		while(A[i] <= piv && i < j){
			i++;
		}
		//Va recorriendo el numero de final a la izquierda cuando el pivote es menor al número a comparar
		while(A[j] > piv){
			j--;
		}
		//Verificamos si todavía no se cruzan los indices y se intercambian las posiciones en donde se hayan quedado los dos anteriores loops
		if(i < j){
			intercambiar(A, i, j);	
		}
	}
	//En cuyo caso de que se hayan cruzado, ponemos el pivote en el lugar que le corresponde
	intercambiar(A, p, j);
	//Regresamos la posición en donde quedo, que será el pivote
	return j;
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que sólo realiza el intercambio de números)
	------------------------------------------
	Argumentos:
	int *A, arreglo con los números a ordenar
	int i, posición 1 a intercambiar
	int j, posición 2 a intercambiar
	Variables utilizadas:
	int temp, variable auxiliar para poder intercambir el valor sin que se pierda
*/
void intercambiar(int *A, int i, int j){
	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}