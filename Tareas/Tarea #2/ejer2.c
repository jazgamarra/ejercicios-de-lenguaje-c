/*
Jazmin Gamarra 
Desarrolle este ejercicio con el compañero Manuel Baez  
*/

#include <stdio.h> 
#define MAX_TAM 10
#define N 5 

typedef struct { 
		int prueba; 
		char a[MAX_TAM]; 
		char b[MAX_TAM]; 
		unsigned short c; 
		float d[2][4][6];    // cargaré la matriz automaticamente con valores aleatorios en la funcion cargaAutomatica 
		long e; 
		struct F { 
			char f1, f2, f3; 
			}f; 		
		} B; 
		
int main () {
	
	B A[N];  
	cargaManual (&A);  // el usuario introducira los valores de a,b,c,e,f 
	cargaAutomatica (&A); // carga con random de la matriz d 
	impresion(&A); // se imprimen los datos que inicializo el usuario

}

void cargaManual( B *A ){
	int i; 
	for (i=0; i<N; i++) { 
	
			// Escanea los valores de las cadenas a y b 
			printf("\nIngrese el valor de a (a es una cadena): ");
			scanf("%s", (A+i)->a); 
			printf("\nIngrese el valor de b (b es una cadena): ");
			scanf("%s", (A+i)->b); 
			
			//Escanea el valor del int c 
			printf("\nIngrese el valor de c (c es un entero corto): ");
			scanf("%hd", &(A+i)->c); 
			
			//Escanea el valor de int e
			printf("\nIngrese el valor de e (e es un entero largo): ");
			scanf("%ld", &(A+i)->e); 
			
			// Escanea los valores de f1, f2, f3 de struct f 
			printf("\nIngrese tres letras (equivalentes a f1,f2,f3) sin espacio en medio: ");
			scanf("%c%c%c", &(A+i)->f.f1, &(A+i)->f.f2, &(A+i)->f.f3);

	}
} 

void cargaAutomatica ( B *A ){
	
	// Carga con random de la matriz tridimensional d 
	int x, i, j, k; 
		for (x=0; x<N; x++) { 
			for (i=0; i<2; i++) { 
				for (j=0; j<4; j++) { 
					for (k=0; k<6; k++) { 
						 (A+x)->d[i][j][k] = (rand() % 100)/10; 
					}
				}
			}
		}

}

void impresion(B *A) {
	
	int i; 	
	printf("\n\nSe imprimiran los valores introducidos por el usuario:  \n\n"); 
		for (i=0; i<N; i++) { 
			printf("\n\nRegistro #%d ", i+1); 
			printf("\nCadena a: %s", (A+i)->a);
			printf("\nCadena b: %s", (A+i)->b);
			printf("\nEntero corto c: %hd", (A+i)->c);
			printf("\nEntero largo e: %ld", (A+i)->e);
		}
}
