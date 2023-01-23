/* Primer pacial Virtual 2021 
Jazmin Gamarra 
28/03/2022 
*/
#include <stdio.h>
#define N 10

// PROTOTIPOS
	void ordenar (int V[N]) ;
	void impresion (int V[N]) ;
	void impresion2 (char V[N]) ;  
	void secuencia (int V[N]) ;
	

int main () {
	
	int A[N] = {2,5,2,4,4,9,7,2,4,7}; // 2 2 2   4 4 4   5     7 7      9 
	
	printf("\n\n1. Vector numerico A = { 2,5,2,4,4,9,7,2,4,7 } \n");
		ordenar(A); 
		impresion(A); 
		secuencia(A); 
	
	char B[N] = { 'A','C','D','T','E','T','J','E','A','D' };
	
	printf("\n\n2. Vector cadena B = { 'A','C','D','T','E','T','J','E','A','D' } \n");
			// convierto los valores de CADENA A INT para poder usar la misma subrutina para ordenar
			int aux[N], i; 
			for (i=0; i<N; i++){ 	
				aux[i]=(int)B[i]; 
			} 
	 		
	ordenar(aux); 
	 		
			// convierto los valores de INT A CADENA para tener el vector B ordenado 
			for (i=0; i<N; i++){ 	
				B[i]=(char)aux[i]; 
			} 
			 
	impresion2(B); 
	secuencia(aux); 
	
}

/*La subrutina ordenar recibe un vector numerico y lo ordena segun el metodo burbuja */
	void ordenar (int V[N]) {
		int i, j, aux; 
			for (i=0; i<N; i++){
				for (j=0; j<N; j++){
					if (V[j]>V[j+1]) {
						aux = V[j]; 
						V[j] = V[j+1]; 
						V[j+1]=aux;
						
	}		}	}	}

/*Hay dos subrutinas de impresion, la primera imprime vectores numericos y la segunda vectores de tipo caracter */
	void impresion (int V[N]) {
		
		printf("\n\tVector ordenado: ");
	
		int i; 
		for (i=0; i<N; i++){
			printf("%4d", V[i]);
		}
		
	}
	void impresion2 (char V[N]) {  // es la misma subrutina q arriba pero cambie el parametro a char 
		
		printf("\n\tVector ordenado:  ");
	
		int i; 
		for (i=0; i<N; i++){
			printf("%4c", V[i]);
		}
		
	}

/*La subrutina secuencia imprime en pantalla la cantidad de secuencias 
Una vez ordenado el vector, todos los elementos que son iguales quedan uno al lado del otro 
Queda entonces comparar cada elemento con el que tiene alado, y si son diferentes significa que existe una secuencia nueva */

	void secuencia (int V[N]) {
			int contador = 0, i; 
			for (i=0; i<N; i++){
				if (V[i] != V[i+1]) {
					contador ++; 	
				}
			}
		printf("\n\tCantidad de secuencias = %d", contador);
	}


   	