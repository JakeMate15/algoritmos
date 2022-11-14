//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Noviembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Medición de tiempo en C y recepción de parametros en C bajo UNIX
//Algoritmo: Búsqueda exponencial
//Compilación: "gcc fibo.c tiempo.x  -o fibo" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./fibo n" (Linux y MAC OS)
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
int fibo(int *, int, int);

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
		pos = fibo(A, n, B[i]);
	
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
	Algoritmo de búsqueda fibonacci
	---------------------------------
	Argumentos:
	int *A: arreglo a recorrer para encontrar el número a buscar
	int n: tamaño del problema
	int x: número a buscar 
	Variables utilizada:
	int tern2: término n-2 de la sucesión
	int tern1: término n-1 de la suceisión
	int tern: término n de la sucesión
	int offset: variable para marcar el final si hay partición
	int i: variable auxiliar para asignar la partición del subarreglo
	-- return offset+1 posición del arreglo en el que se ubica el número a buscar
	-- return -1 si no se encuentra
*/
int fibo(int *A, int x, int inicio, int fin){
	int tern2 = 0, tern1 = 1, tern = tern2 + tern1, offset = -1, i;
	
	while(tern < n){
		tern2 = tern1;
		tern1 = tern;
		tern = tern2 + tern1;
	}
	
	while(tern > 1){
		if(offset + tern2 <= n-1) i = offset + tern2;
		else i = n-1;
		
		if(A[i] < x){
			tern = tern1;
			tern1 = tern2;
			tern2 = tern - tern1;
			offset = i;
		}else if(A[i] > x){
			tern = tern2;
			tern1 = tern1 - tern2;
			tern2 = tern - tern1;
		}else{
			return i;
		}
	}
	
	if(tern1 && A[offset +1] == x) return offset + 1;
	
	return -1;
}
