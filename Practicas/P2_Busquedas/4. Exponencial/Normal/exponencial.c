//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Noviembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Búsqueda exponencial
//Compilación: "gcc exponencial.c tiempo.x  -o exponencial" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./exponencial n" (Linux y MAC OS)
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
int binaria(int *, int, int, int);
int exponencial(int *, int, int);

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
	int B[20] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //Números a buscar
	int i;	//Variables para loops
	double tiempoT = 0; //Variable que recibe la suma total del tiempo tardado
	int pos; //Variable para verificar la posición en la que encontró el número

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
	
	//For para buscar los números propuestos
	for(i=0; i < 20; i++){
		//******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);
		
		//******************************************************************	
		//Algoritmo
		//******************************************************************	
		pos = exponencial(A, n, B[i]);
	
		//******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);
		
		//Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Para x = %d\n pos = %d\n", B[i], pos);
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
	Algoritmo de búsqueda exponencial
	---------------------------------
	Argumentos:
	int *A: arreglo a recorrer para encontrar el número a buscar
	int n: tamaño del problema
	int x: número a buscar 
	Variables utilizada:
	int i: auxiliar en los loops
	-- return binaria después de hacer el primer proceso, se llama a la función para terminar de encontrar el número
	-- return 0 si se encuentra en la primera posición
*/
int exponencial(int *A, int n, int x){
	int i = 1;
	if(A[0] == x){
		return 0;
	}
	
	while(i < n && A[i] <= x) i = i * 2;
	
	if(i <= n-1) return binaria(A, i/2, i, x);
	else return binaria(A, i/2, n-1, x);
}

/*
	Algoritmo de búsqueda binaria (recursivo)
	----------------------------
	Argumentos:
	int *A: arreglo a recorrer para encontrar el número a buscar
	int posIni: partición inicial que se encuentra el arreglo
	int posFin: partición final que se encuentra el arreglo
	int x: número a buscar 
	Variables utilizada:
	int mid: utilizada para marcar la mitad de la variable
	-- return mid si se encuentra el número a buscar
	-- return -1 si no se encuentra
*/
int binaria(int *A, int posIni, int posFin, int x){
	int mid;
	if(posFin >= posIni){
		mid = posIni  + (posFin-posIni)/2;
		
		if(A[mid] == x) return mid;
		
		if(A[mid] > x) return binaria(A, posIni, mid - 1, x);
		
		if(A[mid] < x) return binaria(A, mid + 1, posFin, x);
	}
	
	return -1;
}