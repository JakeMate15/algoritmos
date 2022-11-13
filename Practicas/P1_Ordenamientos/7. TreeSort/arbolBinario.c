//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Funciones/Operaciones de la estructura de dato Árbol Binario
//Estructura: Árbol Binario
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBinario.h"

//************************************************************************
//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*
	Se genera un nodo del árbol binario con el dato
	-----------------------------------------------
	Argumentos:
	int info: información que se guardará en el nodo
	Variables utilizadas:
	*return* struct Nodo *nvo: estructura árbol que se le asignará un nuevo nodo
*/
struct Nodo * nuevoNodo(int info){
	struct Nodo* nvo;
	nvo = (struct Nodo *) malloc(sizeof(struct Nodo));
	if(nvo == NULL){
		printf("No se ha creado el nodo");
		exit(1);
	}
	nvo ->dato = info;
	nvo ->izq = nvo ->der = NULL;
	return nvo;
}

/*
	Proceso para insertar información en un nodo del árbol binario 
	--------------------------------------------------------------
	Argumentos:
	struct Nodo *nvo: estructura árbol que se le realizaran las modificaciones
	int info: información que se guardará en un nodo
*/
void insertar(struct Nodo * nodo, int info){
	if(info > nodo->dato){
		if(nodo->der == NULL){
			nodo->der = nuevoNodo(info);
		}else{
			insertar(nodo->der, info);
		}
	}else{
		if(nodo->izq == NULL){
			nodo->izq = nuevoNodo(info);
		}else{
			insertar(nodo->izq, info);
		}
	}
}

/*
	Proceso recursivo para recorrer el árbol en preorden 
	----------------------------------------------------
	Argumentos:
	struct Nodo *nvo: estructura árbol al que recorrerán
*/
void preorden(struct Nodo * nodo){
	if(nodo != NULL){
		printf("%d ", nodo->dato);
		preorden(nodo->izq);
		preorden(nodo->der);
	}
}

/*
	Proceso recursivo para recorrer el árbol en inorden 
	---------------------------------------------------
	Argumentos:
	struct Nodo *nvo: estructura árbol al que recorrerán
*/
void inorden(struct Nodo * nodo){
	if(nodo!=NULL){
		inorden(nodo->izq);
		printf("%d ", nodo->dato);
		inorden(nodo->der);
	}
}

/*
	Proceso recursivo para recorrer el árbol en postorden 
	-----------------------------------------------------
	Argumentos:
	struct Nodo *nvo: estructura árbol al que recorrerán
*/
void postorden(struct Nodo * nodo){
	if(nodo != NULL){
		postorden(nodo->izq);
		postorden(nodo->der);
		printf("%d ", nodo->dato);
	}
}

/*
	Función que pasa cada nodo de forma inorden a un arreglo 
	--------------------------------------------------------
	Argumentos:
	struct Nodo *nvo: estructura árbol al que recorrerán y se extraen los datos
	int *A: arreglo que se le irá insertando los elementos del árbol
	int *i: posición del arreglo
*/
void guardaInOrden(struct Nodo * nodo, int *A, int *i){
	if(nodo!=NULL){
		guardaInOrden(nodo->izq, A, i);
		A[*i] = nodo->dato;//En vez de imprimir, guardamos el elemento
		*i = *i + 1; //Esto para poder guardar el siguiente elemento al arreglo
		guardaInOrden(nodo->der, A, i);
	}
}