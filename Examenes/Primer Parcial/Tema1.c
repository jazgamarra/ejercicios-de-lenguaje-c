/*
Jazmin Gamarra 31/03/2022

NOTA: ESTE ES EL ORDEN DE MI PROGRAMA 
- subrutina cargaElementos
- subrutina imprimirVector (la llamo desde cargaElementos)
- subrutina ordenarVector (la llamo desde mediana)

- subrutina mediaAritmetica 
- subrutina mediana 
- subrutina moda 

- subrutina estatisticas (llama a las subrutinas media, moda y mediana )
- int main 

*/

#include <stdio.h>
#include <stdlib.h>
int N; 


/*cargaElementos se encarga de leer los elementos por teclado. 
el ingreso de datos funciona a traves de un centinela, terminara cuando el usuario introduzca cero
mientras el numero ingresado sea distinto de cero se seguira redimensionando el vector */

	void cargaElementos (int *vector) {
		
		printf("\nEl programa le permitira introducir numeros hasta que introduzca 0 \nINTRODUZCA 0 PARA VER LAS ESTADISTICAS");
		int i = -1; 
			while (*(vector+i) > 0 ){
				i++;
				vector=realloc(vector, (i+1)*sizeof(int));
				
				printf("\n ="); 
				scanf("%d", (vector+i));
				
				while (*(vector+i)>10) {
					printf("\nPor favor ingrese un numero entre 1 y 10: "); 
					scanf("%d", (vector+i));
				}	
			} 
		N = i+1; // guardo el numero de elementos q se ingreso en mi variable global para usar despues en otras funciones 
		
		printf("\n\nEl vector ingresado es = \n");
		imprimirVector(vector);  // llamo a la subrutina de impresion 
	}

/* subrutina para la impresion del vector */
	void imprimirVector (int *vector) {
		int i; 
			
			for (i=0; i<N; i++) {
				printf("  %d  |", *(vector+i)); 
			}
	}

/* la funcion ordenarVector ordena el vector a traves del metodo burbuja
se necesita para hayar la mediana  */
	void ordenarVector (int *vector) {
			int i, j, aux; 
				for (i=0; i<N; i++){
					for (j=0; j<N; j++){
						if (*(vector+j)>*(vector+j+1)) {
							aux = *(vector+j); 
							*(vector+j) = *(vector+j+1); 
							*(vector+j+1) = aux;
							
						}		
					}	
				}
			printf("\n\nEl vector ordenado es = \n");
			imprimirVector(vector);  // llamo a la subrutina de impresion 	
	}
/*las tres subrutinas siguientes hacen los calculos de moda, mediana y media aritmetica. */

			void mediaAritmetica (int *vector) {
				int i; 
				float mediaArit = 0; 
				
					for (i=0; i<N; i++) {
						mediaArit = mediaArit + *(vector+i); 
					}
					
				mediaArit = mediaArit/N; 
				printf("\n\nLa media es: %.2f", mediaArit);
			}

			void mediana (int *vector) {
				
				ordenarVector(vector);  // se llama a la subrutina de ordenacion
				
				int mediana ; 
				float posicion = N/2; 
				mediana = *(vector+(int)posicion); 
				 
				printf("\n\nLa mediana es: %d", mediana);
			}

			void moda (int *vector) {
						
				int contadores[10] = {0,0,0,0,0 ,0,0,0,0,0}; int i, j; 
						
				for (i=0; i<N; i++) {
					for (j=0; j<10; j++) {
						if (j==*(vector+i)) {
							contadores[j]=contadores[j] + 1; 
						}
					}
				}
				int moda = 0; 
				for (i=0; i<N; i++) {
					for (j=0; j<10; j++) {
						if (contadores[j] > moda) {
							 moda = j; 
						}
					}
				}
				printf("\n\nLa moda es: %d", moda);
			}
/*---------------------------------------------------------------------------------------*/

/*la subrutina estadisticas llama a las subrutinas mediaAritmetica, mediana y moda para que realicen los calculos */
void estadisticas (int *vector) {
	
	mediaAritmetica(vector); 
	moda(vector);
	mediana(vector);

	 
}

/* en el main solo se llama a las funciones de carga y estadistica */
int main () {
	 
		int *vector;
		vector =  malloc(1 * sizeof(int));
		 	
			cargaElementos(vector);  
			estadisticas(vector); 
			
		free (vector); 
}

