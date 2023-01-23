/*
Notas sobre punteros y matrices 
Jazmin Gamarra 
22/06/2022
 
- - - - - - - - - - - - - - - - - - - - - NOTAS - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
A. ¿Cómo podemos acceder a una posición determinada?
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    Teniendo como posición de origen un puntero al elemento [0][0] de la matriz, para acceder al elemento ubicado en 
    A[2][1] debemos movernos 2 filas y 1 columna, lo cual se hace mediante la fórmula de direccionamiento: 

        p = &A[0][0] 
        A[2][1] = (p+4*2+1) 
        ---------------------------------
        Fórmula: *(puntero + i * N + j) 
        ---------------------------------
    Se puede intercambiar siempre la notación de vectores a la de punteros usando la formula de direccionamiento. 

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
B. Error comun al trabajar con puntero a punteros 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        Al trabajar con un puntero a punteros, no se puede asignar directamente así 
            int ** p; 
            p = matriz;
        debe hacerse así: 
            int matriz [m][n]
            int (*r)[n]; //puntero a un vector de n elementos 
            r = matriz; 

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
C. Puntero a Puntero vs. Vector de Punteros 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        Puntero a un vector de n enteros
            int (*arreglo)[n]; 
        Vector de n punteros a enteros 
            int *arreglo[n]
*/

#include <stdio.h>
#include <stdlib.h>

// prototipos 
    #define M 5 
    #define N 4 
    void imprimirMatriz(int * puntero, int m, int n); 
    void imprimirMatriz2(int vector[], int m, int n); 
    void imprimirMatriz3(int *p[], int m, int n); 
    void imprimirMatriz4(int **q, int m, int n); 

// FUNCION PRINCIPAL (cómo llamar a cada subrutina)
int main (){

    int matriz[M][N] = {1,3,2,5,  1,4,3,5,  2,3,2,5,  3,3,2,5,  4,4,3,1 };

    printf("\n\n- Imprime la matriz en notacion de punteros tratandolo como un vector largo \n");   
    imprimirMatriz(&matriz[0][0], M, N); 

    printf("\n\n- Combinando notacion de punteros y de vectores (recibe un vector de parametro)  \n");   
    imprimirMatriz2(&matriz[0][0], M, N); 
    
    printf("\n\n- Teoria de vector de punteros (notacion de vectores)\n");   

    // guardo en mi vector la direccion de memoria del primer elemento de cada fila 
    int *p[M]; 

    for (int i = 0; i < M; i++){
        p[i] = &matriz[i][0]; 
    }
    imprimirMatriz3(p, M, N); 

    printf("\n\n- Puntero a puntero \n");   
    // usando lo del ejercicio anterior 
    int ** puntero = p; 
    imprimirMatriz4(puntero, M, N); 

}

/* Imprime la matriz en notacion de punteros tratandolo como un vector largo */
void imprimirMatriz(int * puntero, int m, int n) {
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d", *(puntero + i * n + j)); 
        }
    }
}

/* Imprime la matriz combinando notacion de punteros y de vectores (recibe un vector de parametro) */
void imprimirMatriz2(int vector[], int m, int n) {
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d",  vector[i * n + j]); 
        }
    }
}

/* Imprime la matriz usando la teria de vector de punteros (notacion de vectores) */
void imprimirMatriz3(int *p[], int m, int n) {
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d",  p[i][j]); 
        }
    }
}

/* Imprime la matriz usando punteros dobles. */
void imprimirMatriz4(int **q, int m, int n) {
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d",  q[i][j]); 
        }
    }
}

