#include<stdio.h>
#include <stdlib.h>
#include"arbolBinario.h"


int main(){
    
    ABB abb = nuevoNodo(50,5);

    insertar(abb,30,2);
    insertar(abb,20,1);
    insertar(abb,40,4);
    insertar(abb,70,7);
    insertar(abb,60,6);
    insertar(abb,80,8);

    ABB abb2 = busqueda(abb,80);

    if(abb2 == NULL){
        printf("-1");
    }
    else{
        printf("%d", abb2->posicion);
    }

    free(abb);
    
    return 0;
}