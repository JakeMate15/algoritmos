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
int potencia = 1;             //Variable para encontrar la potencia menor más cercana al número buscado
pthread_t *arrHilos; 		//Arreglo para los hilos generados

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int * crearArreglo(int);
void* exponencial(void *id);
int binaria(int *, int, int, int);

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
        //Encontramos la potencia más cercana
        potencia = 1;
        if(A[0] == B[i]){
		    posElem = 0;
	    }
        else{
            while(potencia < n && A[potencia] <= B[i]) 
                potencia *= 2;
        }

        //Creamos y procesamos los respectivos hilos
        for(j=0;j<numeroHilos; j++){

            if(pthread_create (&arrHilos[j], NULL, exponencial, NULL) != 0){
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
		printf("Para x = %d\nPos = %d\n", B[i],posElem);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");
		
		tiempoT = tiempoT + (wtime1 - wtime0);
		posElem = -1;
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
	--------------------------------------------
	Argumentos:
	void *id el número de hilo que está por ejecutar
	Variables utilizadas:
	int inicio: posición en la que se va a iniciar la búsqueda dentro del arreglo
	int fin: posición en la que va a terminar la búsqueda
    int posEncontrada: bandera que indica si se encontro el elemento
*/

void* exponencial(void *id){
    int inicio,fin;
    int posEncontrada;

	//Intervalo en donde se buscara el elemento
    inicio=potencia/2;
	if(potencia <= n-1)	
		fin = potencia;
	else
		fin=n-1;

	posEncontrada = binaria(A,inicio,fin,B[posElemBuscado]);
	if(posEncontrada!=-1){
		posElem = posEncontrada;
	}
    
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