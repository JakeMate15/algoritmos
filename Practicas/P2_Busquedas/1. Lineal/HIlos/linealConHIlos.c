//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Noviembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Búsqueda con ayuda de hilos
//Compilación: "gcc hilos.c tiempo.x -lpthread -o hilos" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./hilos n" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tiempo.h"

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int numeroHilos;			//Número de threads y la división del arreglo
int *A; 					//A es un puntero que guardará la dirección del arreglo a ordenar
int B[20] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //Números a buscar
int n; 						//Cantidad de datos
int posElemBuscado; 		//Variable con la posición del elemento buscado del arreglo B.
int posElem = -1;			//Posición del elemento dentro del arreglo, el -1 indica que no se encontró

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int * crearArreglo(int);
void* lineal(void *);

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char* argv[])
{	
	//******************************************************************	
	//Variables del main
	//******************************************************************	
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int i, j;					//Variables para loops
	double tiempoT = 0; 		//Variable que recibe la suma total del tiempo tardado
	pthread_t *arrHilos; 		//Arreglo para los hilos generados

	//******************************************************************	
	//Recepción y decodificación de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 3 argumentos (Cadena de ejecución, cantidad de elementos y número de hilos requeridos)
	if (argc!=3) {
		printf("\nIndique el tamño del problema y la cantidad de hilos - Ejemplo: %s 1000 10\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo y el tercero como la cantidad de hilos
	else{
		n=atoi(argv[1]);
		numeroHilos = atoi(argv[2]);
	}

	//******************************************************************	
	//Creación del arreglo e hilos
	//******************************************************************	
	A = crearArreglo(n);
	arrHilos = malloc(numeroHilos * sizeof(pthread_t));

	for(i=0;i<n;i++){
		scanf("%d",&A[i]); //rellena el arreglo A
	}
	
	//For para buscar los números propuestos
	for(i=0; i < 20 ; i++){
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************
		posElemBuscado = i;	
		uswtime(&utime0, &stime0, &wtime0);
		
		//******************************************************************	
		//Algoritmo
		//******************************************************************
		//Creamos y procesamos los respectivos hilos
		for(j=0;j<numeroHilos; j++){

            if(pthread_create (&arrHilos[j], NULL, lineal, &j) != 0){
                printf("No se han creado los hilos");
                exit(1);
            }

        }
		
		//Unión de todos los hilos
        for(j=0; j<numeroHilos; j++){
            pthread_join(arrHilos[i],NULL);
        }
	
		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);
		
		//Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Para x = %d\n", B[i]);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");
		
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
	Algoritmo de búsqueda lineal
	----------------------------
	Argumentos:
	void *id el número de hilo que está por ejecutar
	Variables utilizadas:
	int numeroHilo: número del hilo procesado
	int inicio: posición en la que se va a iniciar la búsqueda dentro del arreglo
	int fin: posición en la que va a terminar la búsqueda
	int i: auxiliar para el loop
*/

void* lineal(void *id){
    int inicio,fin;
    int numeroHilo = *((int *) id);
    int i;

    posElem = -1;

	//Intervalo en donde se buscara el elemento
    inicio=(numeroHilo*n)/numeroHilos;
	if(numeroHilo==numeroHilos)	
		fin=n;
	else
		fin=((numeroHilo+1)*n)/numeroHilos-1;

	
	//printf("\nEstamos en el hilo %d\nInicia en %d y termina en %d\n",numeroHilo,inicio,fin);


	//loop para recorrer uno por uno el arreglo
	for(i = inicio; i <= fin; i++){
		if(A[i] == B[posElemBuscado]){
			printf("Se encontro numero en la posicion %d", i) ;
			break;
		} 
	}
    
}