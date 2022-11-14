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
int NumThreads = 100;			//Número de threads y la división del arreglo
int *A; //A es un puntero que guardará la dirección del arreglo a ordenar
int B[20] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //Números a buscar
int n; 	//n determina el tamaño del algoritmo dado por argumento al ejecutar 
int pos; //Variable para saber la posición del número del que va 
 
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
	int i, j;	//Variables para loops
	double tiempoT = 0; //Variable que recibe la suma total del tiempo tardado
	pthread_t *thread; //Variable de hilos
	
	thread = malloc(NumThreads * sizeof(pthread_t));

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
	//Creación del arreglo e hilos
	//******************************************************************	
	A = crearArreglo(n);
	for(i=2;i<n;i++){
		scanf("%d",&A[i]); //rellena el arreglo A
	}
	
	void *no;
	for(j = 1; i < NumThreads; i++){
		//void *no = (void*)j;
		if(pthread_create (&thread[i], NULL, lineal, &j) != 0){
			perror("El hilo no pudo crearse");
			exit(-1);
		}
	}
	
	//For para buscar los números propuestos
	for(i=0; i < 20; i++){
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************
		pos = i;	
		uswtime(&utime0, &stime0, &wtime0);
		
		//******************************************************************	
		//Algoritmo
		//******************************************************************
		//El main ejecuta el thread 0
		lineal(0);
		
		//Esperar a que terminen los demas
		for(j = 1; j < NumThreads; j++) {
			pthread_join (thread[j], NULL);
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
	int n_threa: auxiliar del número de hilo que va
	int inicio: posición en la que se va a iniciar la búsqueda
	int fin: posición en la que va a terminar la búsqueda
	int i: auxiliar para el loop
*/
void * lineal(void *id){
	//int n_thread = id;
	int n_thread = *((int*)(&id));
	int inicio, fin, i;
	//Tramo a revisar
	inicio = (n_thread*n)/NumThreads;
	if(n_thread == NumThreads-1) fin = n;
	else fin = ((n_thread+1)*n)/NumThreads-1;
	
	
	//loop para recorrer uno por uno el arreglo
	for(i = inicio; i < fin; i++){
		if(A[i] == B[pos]){
			printf("Se encontro numero en posicion %d", i) ;
			break;
		} 
	}
}