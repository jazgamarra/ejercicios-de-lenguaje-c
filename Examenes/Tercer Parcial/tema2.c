/* Segundo tema - Tercer Parcial 
Jazmin Gamarra 
15/06/2022
*/

#include <stdio.h> 

// CONSTANTES 
    #define M 5 
    #define N 4 
    /* declaro la dimension de la matriz como constante porque no se debe 
    inicializar una matriz con variables (genera error al depurar y compilar) */
    #define RANGO 25 // Se puede asumir que los valores del array siempre son enteros del 1 al 25.
    #define NULO 0

// PROTOTIPOS
void hayarSecuencia (int matriz[M][N], int c, int f, int numerosRepetidos[RANGO], int *elemento, int *repeticiones, int *columna); 
void inicializarVector(int vector[RANGO],int i); 
void compararRepeticiones(int vector[RANGO], int i, int *elemento, int *repeticiones, int *columna, int col); 
void imprimirColumna (int matriz[M][N], int c, int f, int columna); 
void impresionResultados (int elemento, int repeticiones, int columna, int matriz[M][N]); 

// FUNCION PRINCIPAL 
int main () {

    int numerosRepetidos[RANGO], elemento, repeticiones = 0, columna; 
    inicializarVector(numerosRepetidos, 0); 
    /* Cargare la cantidad de repeticiones de cada numero en un vector, 
    correspondiendo el indice del vector al numero leido */

    int matriz[M][N] = {1,3,2,5,  1,4,3,5,  2,3,2,5,  3,3,2,5,  4,4,3,1 };  // Se declara la matriz del ejemplo 

    hayarSecuencia (matriz,0,0, numerosRepetidos, &elemento, &repeticiones, &columna); 
    impresionResultados(elemento, repeticiones, columna, matriz); 
} 

/* Se inicializa el vector numerosRepetidos */
void inicializarVector(int vector[RANGO], int i){
    if (i < RANGO){
        vector[i] = NULO;
		i++;
        inicializarVector(vector, i);
    }
}

/* Se recorre la matriz */
void hayarSecuencia (int matriz[M][N], int c, int f, int numerosRepetidos[RANGO], int *elemento, int *repeticiones, int *columna){
    if (f >= 0 && f < M && c >= 0 && c < N){
        numerosRepetidos[matriz[f][c]]++; 
        if (f == M - 1){
            f = 0;
            c++;
            inicializarVector(numerosRepetidos, 0); // se inicializa de nuevo el vector para leer una nueva columna 
        }else{
            compararRepeticiones(numerosRepetidos, 0, elemento, repeticiones, columna, c ); 
            f++;
        }
        hayarSecuencia(matriz, c, f, numerosRepetidos, elemento, repeticiones, columna);
    }
}

/* Se compara si las repeticiones de esa columna son mayores a la que se tenia cargada. 
Si es el caso se modifican los valores de elementos y repeticiones */
void compararRepeticiones(int vector[RANGO], int i, int *elemento, int *repeticiones, int *columna, int col) {
    if (i < RANGO){
		if (vector[i] > *repeticiones ) {
            * elemento = i; 
            * repeticiones = vector[i]; 
            * columna = col+1; 
        } 
		i++;
        compararRepeticiones(vector, i, elemento, repeticiones, columna, col);
    }
}

/* Se imprime la columna  */
void imprimirColumna (int matriz[M][N], int c, int f, int columna){
    if (f >= 0 && f < M && c >= 0 && c < N){
        if (c == columna){
            printf("  %d", matriz[f][c]); 
        }
        if (f == M - 1){
            f = 0;
            c++;
        }else{
            f++;
        }
        imprimirColumna(matriz, c, f, columna);
    }
}

/*Se imprimen los resultados :) */
void impresionResultados (int elemento, int repeticiones, int columna, int matriz[M][N]) {
    printf("\n Elemento: %d \n Frecuencia de aparicion: %d \n Columna: #%d ", elemento, repeticiones, columna);
    printf("\n Impresion de la columna: "); 
    imprimirColumna(matriz, 0, 0, columna-1); 
    printf("\n"); 
}