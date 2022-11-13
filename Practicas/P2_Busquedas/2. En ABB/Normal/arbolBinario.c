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
	int pos: Posicion del valor dentro del arreglo
	Variables utilizadas:
	*return* ABB nvo: estructura árbol que se le asignará un nuevo nodo
*/
ABB nuevoNodo(int info, int pos){
	ABB nvo;
	nvo = (ABB) malloc(sizeof(Arbol));
	if(nvo == NULL){
		printf("No se ha creado el nodo");
		exit(1);
	}
	nvo ->dato = info;
	nvo ->posicion = pos;
	nvo ->izq = nvo ->der = NULL;
	return nvo;
}

/*
	Proceso para insertar información en un nodo del árbol binario 
	--------------------------------------------------------------
	Argumentos:
	ABB: estructura árbol que se le realizaran las modificaciones
	int info: información que se guardará en un nodo
	int pos: Posicion del valor dentro del arreglo
	Variables
	ABB nodo devuelve el nodo del arreglo en el que se encuentra sin cambio alguno
*/
void insertar(ABB nodo, int info, int pos){
	if(info > nodo->dato){
		if(nodo->der == NULL){
			nodo->der = nuevoNodo(info, pos);
		}else{
			insertar(nodo->der, info,pos);
		}
	}else{
		if(nodo->izq == NULL){
			nodo->izq = nuevoNodo(info, pos);
		}else{
			insertar(nodo->izq, info, pos);
		}
	}	
}


/*
	Proceso recursivo para recorrer el árbol en inorden 
	---------------------------------------------------
	Argumentos:
	ABB nodo: estructura árbol al que recorrerán
*/
void inorden(ABB nodo){
	if(nodo!=NULL){
		inorden(nodo->izq);
		//printf("%d ", nodo->dato); //Ver los elementos del arbol
		inorden(nodo->der);
	}
}

/*
	Algoritmo: Busqueda en ABB
	--------------------------
	Argumentos:
	ABB nodo: estructura árbol al que aplicarán procedimiento
	int x: número a encontrar
	Variables:
	return nodo->dato si se encontró
	return -1 si no se encontró
*/
ABB busqueda(ABB nodo, int x){
	if(nodo == NULL) return NULL; //Se manda cuando no se encontró en número y ya recorrió el árbol
	
	if(nodo->dato == x) return nodo; //Se manda cuando se encontró el número
	
	if(nodo->dato < x) return busqueda(nodo->der, x); //Recorre en la rama derecha la búsqueda
	
	if(nodo->dato > x) return busqueda(nodo->izq, x); //Recorre en la rama izquierda la búsqueda
}