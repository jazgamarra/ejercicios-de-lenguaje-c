#include <stdio.h>

#define N 5

// Prototipos. 
void cargarMatriz (int matriz [N][N], int i, int j); 
void imprimirMatriz (int matriz [N][N], int i, int j); 

// Función Principal. 
int main (){
    int matriz[N][N]; 
    cargarMatriz(matriz,0,0); 
    imprimirMatriz(matriz,0,0); 
}

// Cargar matriz. 
void cargarMatriz (int matriz [N][N], int i, int j) {
    if ( j < N && i < N){
		matriz[i][j] = i+j;
        if (j == N - 1){
            j = 0;
            i++;
        }else{
            j++;
        }
        cargarMatriz(matriz, i, j);
    } 
}

// Imprimir matriz. 
void imprimirMatriz (int matriz [N][N], int i, int j) {
    if ( j < N && i < N){
		printf("%4d", matriz[i][j]);

        // Si se llega al final de la columna 
        if (j == N - 1){
            j = 0;
            i++;
            printf("\n");
        // Si no es el final de la columna 
        }else{
            j++;
        }
        imprimirMatriz(matriz,i, j);
    }
}