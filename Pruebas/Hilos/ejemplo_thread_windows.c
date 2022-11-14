//*****************************************************************
//EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis de algoritmos
//ESCUELA SUPERIOR DE CÓMPUTO - IPN
//(C) Marzo 2013
//Ejemplo del empleo de Threads
//Compilación: ""gcc tiempo.c ejemplo_thread.c -lpthread -o ejemplo_thread"
//Ejecución: "./ejemplo_thread 4"
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int NumThreads;			//Número de threads
int N;

//********************************************************************************
//COMPORTAMIENTO DE LOS THREADS
//********************************************************************************

//********************************************************************************
//1 Saludar 
//********************************************************************************
void* saludar(void* id)
{
	printf("\nHola desde Saludar\tSoy el thread %d",(int)id);
}

//********************************************************************************
//2 Realizar un procesamiento
//********************************************************************************
void* procesar(void* id)
{	
	int n_thread=(int)id;
	int inicio,fin,i,a;

	//Revisar la parte de los datos a procesar	
	inicio=(n_thread*N)/NumThreads;
	if(n_thread==NumThreads-1)	
		fin=N;
	else
		fin=((n_thread+1)*N)/NumThreads-1;

	printf("\nHola desde procesar\tSoy el thread %d\tInicio %d\tTermino %d",n_thread,inicio,fin);
	for(i=inicio;i<=fin;i++)
		a=i*i;		
		//printf("\nProcesando dato %d",i);

	printf("\nBye desde procesar\tSoy el thread %d\tHe terminado",n_thread);

}

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main (int argc, char *argv[])
{	
	int i,j,k; 	//Variables auxiliares para loops
	
	
	//********************************************************************************
	//Obtener el número de threads a usar y el arreglo para la identificacion de los mismos
	//********************************************************************************
	pthread_t *thread;
	if (argc<2) 
	{
		printf("Indique el número de threads - \tEjemplo: [user@equipo]$ %s 4\n\n",argv[0]);
		exit(-1);
	}  
	NumThreads=atoi(argv[1]);
	thread = malloc(NumThreads*sizeof(pthread_t));

	//***************************************************************************************************************************
	//Saber cuál es el tamaño del problema N
	//***************************************************************************************************************************	
	//Si no se introduce correctamente N
	if (argc!=3) 
	{
		printf("\nIndique el tamaño de N - \nEjemplo: [user@equipo]$ %s %s 1000\n",argv[0],argv[1]);
		exit(-1);
	}
	N=atoi(argv[2]);


	//***************************************************************************************************************************
	//1 Saludar desde cada hilo "saludar"
	//***************************************************************************************************************************
	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, saludar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	
	//El main ejecuta el thread 0
	saludar(0);
	
	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);
				
	//***************************************************************************************************************************
	//2 Procesar desde cada hilo "procesar"
	//***************************************************************************************************************************
	//Crear los threads con el comportamiento "segmentar"
	for (i=1; i<NumThreads; i++) 
	{
		if (pthread_create (&thread[i], NULL, procesar,(void*)i) != 0 ) 
		{
			perror("El thread no  pudo crearse");
			exit(-1);
		}
	}
	
	//El main ejecuta el thread 0
	procesar(0);
	
	//Esperar a que terminen los threads (Saludar)
	for (i=1; i<NumThreads; i++) pthread_join (thread[i], NULL);

	
	//Terminar programa normalmente	
	exit (0);	
}
