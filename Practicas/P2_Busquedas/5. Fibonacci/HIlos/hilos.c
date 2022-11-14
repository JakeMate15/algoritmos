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
int fibn;                   //Variable para encontrar la potencia menor más cercana al número buscado
pthread_t *arrHilos; 		//Arreglo para los hilos generados

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
int * crearArreglo(int);
void* particion(void *id);
int fibo(int *, int , int , int );

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
    int fib2=0,fib1=1;
    
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

            if(pthread_create (&arrHilos[j], NULL, particion, &j) != 0){
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

void* particion(void *id){
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


	posElem = fibo(A,B[posElemBuscado],inicio,fin);
    
}


/*
	Algoritmo de búsqueda fibonacci
	---------------------------------
	Argumentos:
	int *A: arreglo a recorrer para encontrar el número a buscar
	int inicio: Limite izq del arreglo
	int fin: limite der del arreglo
	int x: número a buscar 
	int
	Variables utilizada:
	int n: tamaño del problema
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
    int n = fin-inicio+1;
	
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