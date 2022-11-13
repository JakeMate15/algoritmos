//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Definición de la estructura de dato Heap
//Estructura: Heap
//*****************************************************************

//*****************************************************************
//DEFINICIÓN DE HEAP
//*****************************************************************
#ifndef _heap_
#define _heap_

//********************************************************************************
//DEFINICIÓN DE ESTRUCTURAS
//********************************************************************************
typedef struct {
    int *heap;
    int tam;
    int ultimo;
} Heap;

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void construir(Heap *, int);
void deshacer(Heap *);
void insertar(Heap *, int);
void borrar(Heap *, int);
int extraerMaximo(Heap *);

/* Funciones auxiliares */
void reubicar(Heap *, int);
void intercambiar(Heap, int, int);
void subir(Heap, int);
void bajar(Heap, int);
int padre(Heap, int);
int izquierdo(Heap, int);
int derecho(Heap, int);
#endif
