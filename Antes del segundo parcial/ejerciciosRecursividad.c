//Determinar la potencia de un número con funciones recursivas

#include <stdio.h> 
int potencia (int resultado, int base, int exponente, int contador); 
int main (){
    printf("\nIngrese un numero: "); 
    int n; scanf("%d", &n); 

    printf("\nIngrese el exponente: "); 
    int e; scanf("%d", &e);

    printf("\nLa potencia es %d", potencia (1, n, e, 0)); 
}

int potencia (int resultado, int base, int exponente, int contador) {
    if (exponente == contador) {
        return resultado; 
    } else {
        potencia(resultado * base, base, exponente, contador + 1); 
    }
} 

/*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
//Producto de Dos Números con Recursividad

#include <stdio.h> 
int multiplicacion (int resultado, int a, int b, int contador) ; 
int main (){

    printf("\nIngrese el primer numero: "); 
    int a; scanf("%d", &a); 
    printf("\nIngrese el segundo numero: "); 
    int b; scanf("%d", &b);

    /* Voy a calcular la multiplicacion a traves de sumar el numero A la cantidad B de veces
    asi que me aseguro de que el numero que uso de contador (B) sea el menor 
    (para que se repita la menor cantidad de veces )*/
    int resultado; 
    if (a>b) {
        resultado = multiplicacion (0, a, b, 0); 
    } else {
        resultado = multiplicacion(0, b, a, 0); 
    }
    printf("\nEl producto es %d", resultado); 
}

int multiplicacion (int resultado, int a, int b, int contador) {
    if (contador == b ) {
        return resultado; 
    } else {
        multiplicacion (resultado+a, a, b, contador+1); 
    }
}

/*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
//Escribir una función recursiva que devuelva la cantidad de dígitos de un número entero.

#include <stdio.h> 
int cantidadDeDigitos (int dato, int contador, int potenciaDeDiez);
int main (){

    printf("\nIngrese el  numero: "); 
    int n; scanf("%d", &n); 

    printf("\nLa cantidad de digitos es %d", cantidadDeDigitos(n, 0, 1)); 
}

int cantidadDeDigitos (int dato, int contador, int potenciaDeDiez) {
    if (potenciaDeDiez>dato) {
        return contador; 
    } else { 
        cantidadDeDigitos(dato, contador+1, potenciaDeDiez * 10); 
    }
}

/*  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */
//Recorrer una matriz de forma recursiva. (Generar e imprimir)

#include <stdio.h> 
#include <stdlib.h>

int recorrerMatriz (int FILAS, int COLUMNAS, int i, int j, int matriz [FILAS][COLUMNAS]); 

int main () {
	printf("\nIngrese el numero de filas y columnas: "); 
	int f, c; 
	scanf("%d,%d", &f, &c);  
	int matriz[f][c]; 

	printf("\n"); 
	recorrerMatriz( f, c, 0, 0, matriz);
}

int recorrerMatriz (int FILAS, int COLUMNAS, int i, int j, int matriz [FILAS][COLUMNAS]) {
	if (i==FILAS && j==COLUMNAS){ 
		return 0; 
	} else  {
		matriz[i][j] = rand() % 10; 
		
		if (i<FILAS) {
			printf("  %d  ", matriz[i][j]);
			recorrerMatriz(FILAS, COLUMNAS, i+1, j, matriz); 
		}
		if (i == FILAS) {
			printf("\n\n"); 
			recorrerMatriz(FILAS, COLUMNAS, 0, j+1, matriz);  
		}
	}
}
