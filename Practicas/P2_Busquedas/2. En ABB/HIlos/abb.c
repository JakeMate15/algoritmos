//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Noviembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Búsqueda en ABB
//Compilación: "gcc abb.c tiempo.x  -o abb" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./abb n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tiempo.h"
#include "arbolBinario.h"

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
#define HILOS 2				//Número de threads y la división del arreglo
int B[20] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //Números a buscar
int posElemBuscado; 		//Variable con la posición del elemento buscado del arreglo B.
int pos=-1;					//Posicion del elemento buscado

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int * crearArreglo(int);
void * busquedaEnABB(void* arbol);

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int *A; 					//A es un puntero que guardará la dirección del arreglo a ordenar
	int i;						//Variables para loops
	int n; 						//Cantidad de datos
	double tiempoT = 0; 		//Variable que recibe la suma total del tiempo tardado
	Raiz ABB, busq, izq, der; 	//Declaración de los arboles que se usaran

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) {
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else{
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
	//Creación del árbol
	//******************************************************************
	ABB = nuevoNodo(A[0],0);
	for(i=1;i<n;i++){
		insertar(ABB, A[i], i); //Inserto datos en el árbol
	}

	
	//******************************************************************	
	//Creación de los hilos
	//******************************************************************
	pthread_t hilo1, hilo2;

	
	//For para buscar los números propuestos
	for(i=0; i < 20; i++){
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);
		posElemBuscado = i;
		
		//******************************************************************	
		//Algoritmo
		//******************************************************************	
		if(ABB->dato == B[i]){
			pos = ABB->posicion;
		}
		else{
			pthread_create(&hilo1,NULL,busquedaEnABB,ABB->izq);
			pthread_create(&hilo1,NULL,busquedaEnABB,ABB->der);
		}
		
		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);
		
		//Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Para x = %d\npos = %d\n", B[i], pos);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");

		//Limpiamos la posicion
		pos=-1;

		tiempoT = tiempoT + (wtime1 - wtime0);
	}
	
	//Impresión de resultados finales
	printf("\n");
	printf("n = %d\n", n);
	printf("Tiempo total de los 20 números a buscar = %.10f s\n", tiempoT);
	printf("Tiempo total de los 20 números a buscar = %.10e s\n", tiempoT);
	printf("Tiempo promedio para todas las búsquedas = %.10f s\n", tiempoT/(20*1.0));
	printf("Tiempo promedio para todas las búsquedas = %.10e s\n", tiempoT/(20*1.0));
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
	Busqueda en los hijos del arbol
	---------------------------
	Argumentos:
	void * arbol El hijo izquierdo o derecho del arbol completo
	Variables utilizadas:
	*return* int *array: arreglo con el tamaño asignado
*/
void * busquedaEnABB(void * arbol){
	Raiz arbolHijo = (Raiz)arbol;
	Raiz arbolBuscado;

	arbolBuscado = busqueda(arbolHijo,B[posElemBuscado]);

	if(arbolBuscado!=NULL){
		pos = arbolBuscado->posicion;
	}

}