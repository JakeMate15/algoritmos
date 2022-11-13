//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Funciones/Operaciones de la estructura de dato Heap
//Estructura: Heap
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*
	Se genera el heap con una longitud determinada
	----------------------------------------------
	Argumentos:
	Heap *h: estructura heap que se le asignará un tamaño de memoria
	int tam: longitud para el heap
*/
void construir(Heap *h, int tam){
    h->tam = tam;
    h->ultimo = 0;
    h->heap = (int*)malloc(sizeof(int) * tam);
}

/*
	Libera espacio en memoria
	-------------------------
	Argumentos:
	Heap h: estructura a limpiar o a liberar
*/
void deshacer(Heap *h) {
    free(h->heap);
}

/*
	Insertamos elementos al monticulo
	---------------------------------
	Argumentos:
	Heap *h: estructura heap al que se le va insertar el dato
	int dato: variable para otorgar el su contenido a la estructura
*/

void insertar(Heap *h, int dato) {
	//Esto es en e caso de que el ultimo supere a la longitud construida desde un inicio
    if(h->ultimo >= h->tam) reubicar(h, h->tam*2);

	//En caso de que no se ubica el dato hasta el último del monticulo y escala
    h->heap[h->ultimo++] = dato;
    subir(*h, h->ultimo-1);
}

/*
	Es para ir quitando la raíz del árbol
	-------------------------------------
	Argumentos:
	Heap *h: estructura heap al que se le va hacer las modificaciones
	int i: posición del heap
*/
void borrar(Heap *h, int i) {
		//El último elemento pasa a la raíz y empieza a bajar dependiendo de las comparaciones
        h->heap[i] = h->heap[--h->ultimo];
        bajar(*h, i);
}

/*
	Extrae el nodo raíz
	-------------------
	Argumentos:
	Heap *h: estructura heap al que se le va hacer las modificaciones
	Variables utilizadas:
	*return* int raiz: contenido que se obtiene del nodo raíz
*/
int extraerMaximo(Heap *h) {
    int raiz = h->heap[0];

    borrar(h, 0);

    return raiz;
}

/*
	Construyo un heap más grande si es necesario
	--------------------------------------------
	Argumentos:
	Heap *h: estructura heap al que se le va hacer las modificaciones
	int cap: tamaño al que se va asignar al nuevo heap
	Variables utilizadas:
	int *heap2: variable que hace referencia al monticulo/puede ser visto como arreglo de números enteros y se le asigna al heap
	int i: utilizada para los loops
*/
void reubicar(Heap *h, int ncap) {
    int *heap2;
    int i;

    heap2 = (int*)malloc(sizeof(int) * ncap);
    for(i = 0; i < h->ultimo; i++) heap2[i] = h->heap[i];
    if(h->heap) free(h->heap);
    h->heap = heap2;
    h->tam = ncap;
}

/*
	Intercambio las posiciones segun sea el caso
	--------------------------------------------
	Argumentos:
	Heap h: estructura heap al que se le va hacer las modificaciones
	int i: posición 1 de intercambio
	int j: posición 2 de intercambio
	Variables utilizadas:
	int temp: variable auxiliar para mantener el dato
*/
void intercambiar(Heap h, int i, int j) {
    int temp;

    temp = h.heap[i];
    h.heap[i] = h.heap[j];
    h.heap[j] = temp;
}

/*
	Algoritmo para subir del nivel del arbol
    Hacemos intercambio entre el hijo que pasa a ser padre y viceversa, el padre pasa a ser hijo
	--------------------------------------------------------------------------------------------
	Argumentos:
	Heap h: estructura heap al que se le va hacer las modificaciones
	int i: posición de intercambio
	Variables utilizadas:
	int iPadre: hace referencia a la posición del padre de la posición i
*/
void subir(Heap h, int i) {
    int iPadre;
	
    while(i > 0 && h.heap[i] > h.heap[iPadre=padre(h, i)]) {
        intercambiar(h, i, iPadre);
        i = iPadre;
    }
}

/*
	Se manda hasta la última posición el elemento
	---------------------------------------------
	Argumentos:
	Heap h: estructura heap al que se le va hacer las modificaciones
	int i: posición de intercambio
	Variables utilizadas:
	int iIzq: hace referencia a la posición del hijo izquierdo
	int iDer: hace referencia a la posición del hijo derecho
	int maximo: se refiere al número que sea mayor para mandar hasta abajo
*/
void bajar(Heap h, int i){
    int iIzq, iDer, maximo;

    maximo = i;
    do{
        i = maximo;
        iIzq=izquierdo(h, i);
        iDer=derecho(h, i);
        if(iDer < h.ultimo && h.heap[iDer] > h.heap[maximo]) maximo = iDer;
        if(iIzq < h.ultimo && h.heap[iIzq] > h.heap[maximo]) maximo = iIzq;
        if(i != maximo) intercambiar(h, i, maximo);
    } while (i != maximo && maximo < h.ultimo/2);
}

/*
	Obtenemos el nodo padre
	-----------------------
	Argumentos:
	Heap h: estructura
	int i: posición a ver la información
	Variables utilizadas:
	*return* se devuelve el valor de la pocisión del nodo padre
*/
int padre(Heap h, int i) {
    return (i-1)/2;
}

/*
	Obtenemos el nodo izquierdo del nodo padre
	------------------------------------------
	Argumentos:
	Heap h: estructura
	int i: posición a ver la información
	Variables utilizadas:
	*return* se devuelve el valor de la pocisión del nodo hijo izquierdo
*/
int izquierdo(Heap h, int i) {
    return 2*i+1;
}

/*
	Obtenemos el nodo derecho del nodo padre
	----------------------------------------
	Argumentos:
	Heap h: estructura
	int i: posición a ver la información
	Variables utilizadas:
	*return* se devuelve el valor de la pocisión del nodo hijo derecho
*/
//Obtenemos hijo derecho del nodo padre
int derecho(Heap h, int i) {
    return 2*i+2;
}
