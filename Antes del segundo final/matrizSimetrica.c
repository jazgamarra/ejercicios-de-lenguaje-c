/*Escribir un programa que decida si una matriz de números reales es simétrica. Utilizar: 
1- una función de tipo bool que reciba como entrada una matriz de reales, así como el número de filas y de columnas, 
y decida si la matriz es simétrica; 
2- otra función que genere la matriz de 10 filas y 10 columnas de números aleatorios de 1
a 100; 
3- un programa principal que realice llamadas a las dos funciones. Nota: usar la transmisión de matrices como parámetros punteros y
la aritmética de punteros para la codificación 

Jazmin Gamarra 
28/06/22
*/ 
 
#include <stdio.h>
#include <stdlib.h> 

#define N 3
#define FALSO 0 
#define VERDADERO 1

// Prototipos. 
int ** reservarEspacioMemoria(int ** matriz); 
int ** cargarMatriz(int ** matriz); 
void verificarErrorMemoria( void * puntero ); 
void imprimirMatriz(int ** matriz); 
int verificarSimetria (int ** matriz) ; 

// Funcion Principal 
int main () { 

    int ** matriz; 
    matriz = reservarEspacioMemoria(matriz); 
    matriz = cargarMatriz(matriz); 
    imprimirMatriz(matriz); 

    if (verificarSimetria(matriz) == VERDADERO) {
        printf("\n La matriz es simetrica"); 
    } else {
        printf("\n La matriz no es simetrica"); 
    }
}

// Reservar espacio para la matriz en la memoria 
int ** reservarEspacioMemoria(int ** matriz) {
    matriz = (int **) malloc (sizeof(int *)*N);
    verificarErrorMemoria(matriz); 

    for (int j = 0; j < N; j++){
        *(matriz+j) = (int*) malloc (sizeof(int)*N);
        verificarErrorMemoria(*(matriz+j)); 
    } 

    return matriz;
}

// Cargar la matriz del ejemplo 
int **  cargarMatriz(int ** matriz){
    int temporal[N][N] = {1,1,5,1,2,3,5,3,4};

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            *(*(matriz+i)+j) = *(*(temporal+i)+j);
        } 
    }
    return matriz; 
}

// Verificar si el puntero vuelve nulo 
void verificarErrorMemoria( void * puntero ){
    if (puntero == NULL) {
        printf("ERROR!!!!"); 
        exit(-1); 
    }
}

// Se imprime la matriz 
void imprimirMatriz(int ** matriz) {
    for (int i = 0; i < N; i++){
        printf("\n"); 
        for (int j = 0; j < N; j++){
            printf("%4d", *(*(matriz+i)+j)); 
        }
    }
}

// Se verifica la simetria de la matriz 
int verificarSimetria (int ** matriz) {
    int bandera = VERDADERO; 
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (*(*(matriz + i)+j) != *(*(matriz + j)+i) && i != j) {
                bandera = FALSO;
            }
        }
        if (bandera == FALSO){
            break; 
        }
    }
    return bandera; 
}