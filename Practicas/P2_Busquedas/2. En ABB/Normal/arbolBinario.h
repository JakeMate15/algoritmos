//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Septiembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Definición de la estructura de dato Árbol Binario
//Estructura: Árbol Binario
//*****************************************************************

//*****************************************************************
//DEFINICIÓN DE ÁRBOL BINARIO
//*****************************************************************
#ifndef _arbol_
#define _arbol_

//********************************************************************************
//DEFINICIÓN DE ESTRUCTURAS
//********************************************************************************
struct Nodo{
	int dato;
	int posicion;
	struct Nodo *izq;
	struct Nodo *der;
};

typedef struct Nodo * Raiz;

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
Raiz nuevoNodo(int, int);
Raiz insertar(Raiz, int, int);
void postorden(Raiz);
Raiz busqueda(Raiz , int);

#endif
