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
	struct Nodo *izq;
	struct Nodo *der;
};

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
struct Nodo * nuevoNodo(int);
void insertar(struct Nodo *, int);
void preorden(struct Nodo *);
void inorden(struct Nodo *);
void postorden(struct Nodo *);
void guardaInOrden(struct Nodo *, int *, int *);

#endif
