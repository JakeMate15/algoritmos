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
	*return* Raiz nvo: estructura árbol que se le asignará un nuevo nodo
*/
Raiz nuevoNodo(int info, int pos){
	struct Nodo* nvo;
	nvo = (Raiz) malloc(sizeof(struct Nodo));
	if(nvo == NULL){
		printf("No hay espacio en memoria");
		exit(1);
	}
	nvo->dato = info;
	nvo->posicion = pos;
	nvo ->izq = nvo ->der = NULL;
	return nvo;
}

/*
	Proceso para insertar información en un nodo del árbol binario 
	--------------------------------------------------------------
	Argumentos:
	Raiznodo: estructura árbol que se le realizaran las modificaciones
	int info: información que se guardará en un nodo
	Variables
	Raiz nodo devuelve el nodo del arreglo en el que se encuentra sin cambio alguno
*/
Raiz insertar(Raiz nodo, int info, int pos){
	if(nodo == NULL) return nuevoNodo(info,pos);
	
	if(info < nodo->dato) nodo->izq = insertar(nodo->izq, info, pos);
	if(info > nodo->dato) nodo->der = insertar(nodo->der, info, pos);
	
	return nodo;
}

/*
	Proceso recursivo para recorrer el árbol en postorden 
	-----------------------------------------------------
	Argumentos:
	Raiznodo: estructura árbol al que recorrerán
*/
void postorden(Raiz nodo){
	if(nodo != NULL){
		postorden(nodo->izq);
		postorden(nodo->der);
		printf("%d %d\n", nodo->dato,nodo->posicion);
	}
}


/*
	Algoritmo: Busqueda en ABB
	--------------------------
	Argumentos:
	Raiz nodo: estructura árbol al que aplicarán procedimiento
	int x: número a encontrar
	Variables:
	return nodo->dato si se encontró
	return -1 si no se encontró
*/
Raiz busqueda(Raiz nodo, int x){
	if(nodo == NULL) return NULL; //Se manda cuando no se encontró en número y ya recorrió el árbol
	
	if(nodo->dato == x) return nodo; //Se manda cuando se encontró el número
	
	if(nodo->dato < x) return busqueda(nodo->der, x); //Recorre en la rama derecha la búsqueda
	
	if(nodo->dato > x) return busqueda(nodo->izq, x); //Recorre en la rama izquierda la búsqueda
}