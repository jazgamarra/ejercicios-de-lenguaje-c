/*Implemente una funcion que reciba como uno de sus parametros una cadena de longitud variable y retorne un struct cuanto sigue 

- canridad de vocales 
- cantidad de consonantes 
- cantidad de simbolos de puntuacion 

obs: no se puede utilizar ninguna de las funciones de la libreria */

#include <stdio.h>

#define N 20

 
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void cantVocales (char *puntero, char vocales[10]) {
	
	int contador = 0, i, j; 
	
	for (i=0; i<strlen(puntero); i++) {
		for (j=0; j<10; j++)
			/*evalua si la letra esta dentro del vector vocales*/
			if (*(puntero+i) == vocales[j]) {  
				contador=contador+1; 
			}
	}
	printf("\nLa cantidad de vocales es %d", contador); 
	
	}
	
void cantConsonantes (char *puntero, char vocales[10]) {
	
	int contador = 0, i, j, aux, centinela = 0; 
	
	for (i=0; i<strlen(puntero); i++) {
		for (j=0; j<10; j++) {
		
			/*evalua si la letra NO esta dentro del vector vocales 
			si pertenece al rango ascci del abecedario (para que no me cuente simbolos)
			si centinela == 1 para que me cuente solo una vez cada letra (el for de las vocales se pasea mucho)*/

   				aux = (int) *(puntero+i); 
				
				if ( (*(puntero+i) != vocales[j] ) ) {
					if ((aux>64) && (aux <123)) {
						if (centinela == 1) {
						
						printf("\n - %s", (puntero+i)); 
	
						contador=contador+1; 
						centinela=0; 
					}
				}
				}
		}
			centinela = 1; 
	}
		printf("\nLa cantidad de consonantes es %d", contador); 

}

int main (){
	printf("\nIntroduzca la cadena: "); 
	char cadena[N]; 
	fgets(cadena, N, stdin   ); 
	
	char *puntero; 
	puntero = &cadena; 
	
	char vocales[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	cantVocales(puntero, vocales); 
	cantConsonantes(puntero, vocales); 
}








































