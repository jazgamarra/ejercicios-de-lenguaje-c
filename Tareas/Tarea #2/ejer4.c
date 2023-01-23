/*Jazmin Gamarra */
#include <stdio.h> 
#define N 5

typedef struct {
	int x, y; 
}PUNTO; 

int main () {
	
	char A[N][N];  
	cargarMatriz(A); 		// se carga el abecedario en la matriz 

	
	PUNTO p1, p2; 
	leerPuntos (&p1, &p2); // se leen los puntos p1 y p2 a traves de una subrutina 
	
	printf("\n\nMatriz original: \n"); 	
	impresion(A);   		// se usa solo una funcion para imprimir 

	marcarMatriz (A, &p1, &p2);  // se marcan las casillas que no corresponden 
	printf("\n\nMatriz marcada: \n"); 
	impresion(A); 
	
	
}

void cargarMatriz (char A[N][N]){
	
	int ascci=65, i, j;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			A[i][j]=((char)ascci); 
			ascci++; 
		}	
	}
}

void impresion (char M[N][N]) {
	int i, j; 
	for (i=0; i<N; i++) {
			printf("\n\n");
		for (j=0; j<N; j++) {
			printf("\t%c", M[i][j]); 
		}	 
	}
	
}

void leerPuntos (PUNTO *ptr1, PUNTO *ptr2) {
	
	printf("\nIngrese el valor de x,y del primer punto: "); 
		scanf("%d,%d", &ptr1->x, &ptr1->y );
	
	printf("\nIngrese el valor de x,y del primer punto: "); 
		scanf("%d,%d", &ptr2->x, &ptr2->y );
	 
	// validacion de que p2 este despues de p1 
	
	while ((ptr1->x > ptr2->x)&&(ptr1->y > ptr2->y)) {
			
		printf("\n\nEl valor introducido para el segundo punto es invalido. Recuerde que p1 es %d,%d y p2 debe estar despues ", ptr1->x, ptr1->y ); 
		printf("\nIngrese el valor de x,y del segundo punto: "); 
			scanf("%d,%d", &ptr2->x, &ptr2->y );
			
	}
} 
void marcarMatriz (char A[N][N], PUNTO *ptr1, PUNTO *ptr2) {
	
	int  i, j;
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) { 
			if ((i < ptr1->x)||(j<ptr1->y)) {
				
				A[i][j] ='*'; 
				
			}
			if ((i > ptr2->x)||(j > ptr2->y)) {
				
				A[i][j] ='*'; 
				
			}
		}
	}	
}

