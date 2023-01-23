/*
Jazmin Gamarra 31/03/2022
NOTA: No pude hacer el mecanismo de restauracion 
*/

#include <stdio.h>
#include <stdlib.h>
#define N 7 

/* use cargarMatriz para poder usar la matriz del ejemplo porque si cargo con random es dificil que me 
salga una matriz que cumpla la condicion de tener varios sectores en los que la suma da cero 
*/

	int matriz[N][N] = {1,2,3,6,8,-1,-2,7,0,-5,0,-7,-1,9,0,1,5,-3,-1,7,16,8,-2,1,3,-9,1,8,6,-5,-3,-1,5,1,-5,5,1,-2,-5,4,8,-2,0,0,-5,-2,3,1,9  }; 
	
	void cargarMatriz (int *p) {
		int *m, i, j; 
		
		m=&matriz[0][0]; 
		
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){ 
				*(p+i*N+j) = *(m+i*N+j); 
			
			}
				
		}	
	}

/* Subrutina para la impresion de la matriz*/
	void imprimirMatriz (int *p) {
	
		int i, j; 
		for (i=0; i<N; i++){
			for (j=0; j<N; j++){ 
				printf("%d\t", *(p+i*N+j)  ); 
			
			}
			printf("\n"); 
		}	
	}

/*Compara si la suma de la submatriz cuadrada de 2x2 es igual a cero y suma al contador si ocurre. 
Se carga la direccion de memoria de los campos en el puntero auxiliar para vaciarse */

	void vaciar (int *p) {
		
		int i,j,cont=0, *aux; // son contadores 
		for (i=0;i<N;i++) {
			for (j=0;j<N;j++) {
						if (( *(p+i*N+j) + *(p+i*N+(j+1)) + *(p+(i+1)*N+j) + *(p+(i+1)*N+(j+1)) )  == 0) {
							cont ++;
							*aux = p+i*N+j;			free(aux); 
							*aux = p+i*N+(j+1); 	free(aux); 
							*aux = p+(i+1)*N+j; 	free(aux);	
							*aux = p+(i+1)*N+(j+1); free(aux); 
						}
			} 
		}
		printf("\nSe vacio la memoria en %d sectores\n", cont);
	
	}			
							
int main () {
	
	int *puntero;
	puntero = malloc(N*N*sizeof(int)); 
	 
	cargarMatriz(puntero); 
 	imprimirMatriz(puntero); 
 	vaciar(puntero); 
}

