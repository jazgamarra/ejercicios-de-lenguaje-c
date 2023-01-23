/*
Jazmin Gamarra 
*/

#include <stdio.h> 

#define TRUE 1
#define FALSE 0

int main () {
	
	printf("\nIngrese el valor N: "); 
	int N; scanf("%d",&N); 
	
	validarN(&N); // funcion para validar N 
	
	sucesionFarey(N); 

} 

/*Funcion que valida que el valor de N este entre 1 y 10 */
int validarN (int *N) { 
	
	while (*N<0 || *N>10) {
		printf("\nIngrese un numero valido (entre cero y diez): "); 
		scanf("%d",*N); 
	}
	
}

void sucesionFarey (int N) {
	
	printf("\n  0/1  "); 

	float i=1, j=1, centinela = FALSE; 
	
	float A=0; // numero anterior de la sucesion 
	float b=1, c=1; //  para guardar las fracciones, iba a ser mas elegante un struct pero no se puede usar >:c 
	float D= b/c ; // auxiliar para la comparacion 
	
		while (centinela == FALSE) { 
			centinela=TRUE; 
			for (i=1; i<=N; i++) {
				for (j=2; j<=N; j++) {	
					if ((i/j <= 1)&&(i!=j)) {
						if ((i/j<D)&&(i/j>A)){ // si es mayor al numero anterior (A) y menor al mayor (D)
							b=i; 
							c=j; 
							D=b/c;  
							centinela=FALSE;  // si ocurre el if se cambia el valor del centinela 
						}
					}
				}
			}
			
			/* si el centinela llega hasta aqui con valor TRUE significa que ya no existe otro numero que cumpla todas las condiciones que validamos 
			entonces, se imprimira el ultimo numero de la sucesion, el 1/1                                                                             */
			
					if (centinela==TRUE){  
						b=1; c=1; 
					} 
			A=b/c; // se asigna a (A) el valor del ultimo numero 
			D=1; 
			
			printf("  %d/%d ", (int)b, (int)c); 
		}
	
}
