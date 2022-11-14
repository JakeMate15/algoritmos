#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//*****************************************************************
//VARIABLES GLOBALES
//*****************************************************************
int numeroHilos;			//Número de threads
int *A;
int B[20] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0}; //Números a buscar
int n;                      //Tamano del arreglo
int posElemBuscado;
int posElem = -1;

int * crearArreglo(int);
void* lineal(void *);


int main(int argc, char* argv[]){
    int i,j;
    
    if (argc!=3) {
		printf("\nIndique el tamño del problema y la cantidad de hilos - Ejemplo: %s 1000 10\n",argv[0]);
		exit(1);
	}
    else{
        n = atoi(argv[1]);
        numeroHilos = atoi(argv[2]);
    }

    pthread_t arrHilos[numeroHilos];
    A = crearArreglo(n);

	for(i=0;i<n;i++){
		scanf("%d",&A[i]); //rellena el arreglo A
	}

    for(j = 0; j<1; j++){
        posElemBuscado = j;

        for(j=0;j<numeroHilos; j++){

            if(pthread_create (&arrHilos[j], NULL, lineal, &j) != 0){
                printf("No se han creado los hilos");
                exit(1);
            }

        }


        for(i=0; i<numeroHilos; i++){
            pthread_join(arrHilos[i],NULL);
        }

        printf("El elemento %d esta en la pos %d\n", B[posElemBuscado],posElem);
    }

    

    exit(0);
}

void* lineal(void *id){
    int inicio,fin;
    int numeroHilo = *((int *) id);
    int i;

    posElem = -1;


    inicio=(numeroHilo*n)/numeroHilos;
	if(numeroHilo==numeroHilos)	
		fin=n;
	else
		fin=((numeroHilo+1)*n)/numeroHilos-1;


    printf("\nEstamos en el hilo %d\nInicia en %d y termina en %d\n",numeroHilo,inicio,fin);
    

    if(inicio==fin){
        if(A[inicio] == B[posElemBuscado]){
            posElem = inicio;
        }
    }
    else{
        for(i = inicio; i < fin; i++){
            if(A[i] == B[posElemBuscado]){
                posElem = i;
            }
        }
        
    }
    
}

int * crearArreglo(int n){
	int *array;
	
	array = (int *) malloc(sizeof(int) * n);
	
	if(array == NULL){
		printf("No hay memoria disponible para el arreglo");
		exit(1);
	}
	
	return array;
}