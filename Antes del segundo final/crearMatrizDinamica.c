
#include <stdio.h>
#include <stdlib.h>

// Prototipos
int ** reservarEspacioMatriz(int ** matriz, int filas, int columnas); 
void imprimirMatriz(int **matriz, int m, int n); 
int ** cargarMatriz(int **matriz, int m, int n) ; 

void main(){
 int f,c,i,j;
 int **matriz = NULL;

// Se leen las dimensiones  
    printf("Numero de hileras =>");
    scanf("%d",&f);
    printf("Numero de columnas =>");
    scanf("%d",&c);

// Se asigna el espacio a la matriz 
    matriz = reservarEspacioMatriz(matriz, f, c); 

// Se cargan elementos en la matriz 
    matriz = cargarMatriz(matriz, f, c); 

// Se imprime la matriz 
    imprimirMatriz(matriz, f, c); 
}

// Se reserva el espacio para la matriz 
int ** reservarEspacioMatriz(int ** matriz, int filas, int columnas){
    matriz = (int **) malloc (sizeof(int *)*filas);
    for (int j = 0; j < columnas; j++){
        *(matriz+j) = (int*) malloc (sizeof(int)*columnas);
    }

    if (matriz == NULL){
        printf("\n ERROR EN LA ASIGNACION DE LA MEMORIA "); 
        exit(-1); 
    } 

    return matriz; 
}

// Se imprime la matriz 
void imprimirMatriz(int **matriz, int m, int n) {
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d",  *(*(matriz+i)+j)); 
        }
    }
}

// Se carga la matriz
int ** cargarMatriz(int **matriz, int m, int n) {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            *(*(matriz+i)+j) = i+j; 
        }
    }
    return matriz; 
}

