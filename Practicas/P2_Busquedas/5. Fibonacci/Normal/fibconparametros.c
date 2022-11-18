#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibo(int *A, int x, int inicio, int fin){
	int tern2 = 0, tern1 = 1, tern = tern2 + tern1, offset = -1, i;
    int n = fin-inicio+1;
	
	while(tern < n){
		tern2 = tern1;
		tern1 = tern;
		tern = tern2 + tern1;
	}
	
	while(tern > 1){
		if(offset + tern2 <= n-1) i = offset + tern2;
		else i = n-1;
		
		if(A[i] < x){
			tern = tern1;
			tern1 = tern2;
			tern2 = tern - tern1;
			offset = i;
		}else if(A[i] > x){
			tern = tern2;
			tern1 = tern1 - tern2;
			tern2 = tern - tern1;
		}else{
			return i;
		}
	}
	
	if(tern1 && A[offset +1] == x) return offset + 1;
	
	return -1;
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

int main(int argc, char* argv[]){
	int n; 	//n determina el tamaño del algoritmo dado por argumento al ejecutar
	int *A; //A es un puntero que guardará la dirección del arreglo a ordenar
	int i;	//Variables para loops
	int pos; //Variable para verificar la posición en la que encontró el número
    int busq = 236;

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n=atoi(argv[1]);
	}

	//******************************************************************	
	//Creación del arreglo
	//******************************************************************	
	A = crearArreglo(n);
	
	for(i=0;i<n;i++){
		scanf("%d",&A[i]); //rellena el arreglo A
	}
		
		pos = fibo(A, busq, 1,3);
	
		printf("\n");
		printf("Para x = %d\n pos = %d\n", busq, pos);
		printf("\n");
		

	//Terminar programa normalmente	
	exit (0);	
}
