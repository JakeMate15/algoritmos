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
#ifndef _Arbol_
#define _Arbol_

//********************************************************************************
//DEFINICIÓN DE ESTRUCTURAS
//********************************************************************************
typedef struct Nodo{
	int dato;
	int posicion;
	struct Nodo *izq;
	struct Nodo *der;
}Arbol;

typedef Arbol *ABB;

//*****************************************************************
//Operaciones de un ABB
//*****************************************************************
ABB nuevoNodo(int valor, int pos);
void insertar(ABB raiz, int valor, int pos);
void inorden(ABB raiz);
ABB busqueda(ABB raiz, int valor);


#endif