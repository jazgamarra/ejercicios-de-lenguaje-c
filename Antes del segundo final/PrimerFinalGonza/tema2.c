/*Tema 2 
Gonzalo Cristaldo - IEN
5278949 */
#include <stdio.h>
#include <stdlib.h>

#define VERDADERO 1
#define FALSO 0
#define N 7  

int validarDiagonalesCero( int n, int matriz [n][n] ); 
int validarCuadradaImpar(int n, int m) ; 
void verificar(int estado); 
void imprimirMatriz(int n, int matriz[n][n]) ; 
int reflejo(int n, int matriz[n][n]); 
void cargarMatriz(int n, int matriz[n][n]); 

int main(){
    int n , m ; 

    printf("\nIngrese las dimensiones de la matriz en formato i,j: "); 
    scanf("%d,%d", &n, &m); 

    // valido que sea cuadrada e impar 
    int estado = VERDADERO; 
    estado = validarCuadradaImpar(n, m); 
    verificar(estado); 

    int matriz[n][n];   
    cargarMatriz(n, matriz);
    imprimirMatriz(n, matriz); 
    
    // valido que las diagonales sean igual a cero 
    estado = validarDiagonalesCero(n, matriz); // mando solo N como indice de la matriz porque ya valide que es cuadrada :) 
    verificar(estado); 

    // valido que se refleje 
    estado = reflejo(n, matriz); 
    verificar(estado);


    if (estado == VERDADERO) {
        printf("\n\n La matriz es trebol !\n"); 
    }
} 

/* VALIDO QUE LAS DIAGONALES SEA CERO */
int validarDiagonalesCero( int n, int matriz [n][n] ) {
    int bandera = VERDADERO; 
    // valido la diagonal principal, que cumple i=j 
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            if (i==j && matriz[i][j]!=0) {
                bandera = FALSO; 
            }
            if (i+j==n-1 && matriz[i][j]!=0) {
                bandera = FALSO; 
            }
        }
    }
    return bandera; 
}

/* VALIDO QUE SEA CUADRADA E IMPAR */
int validarCuadradaImpar(int n, int m) {
    int bandera = VERDADERO; 
    if (n != m) {
        printf("\n No es cuadrada"); 
        bandera = FALSO  ; 
    } 
    if (m%2 == 0) {
        printf("\n No tiene cantidad de columnas impares "); 
        bandera =  FALSO; 
    }
    return bandera; 
}

/* VALIDO QUE SE REFLEJE */
int reflejo(int n, int matriz[n][n]) {
    int bandera = VERDADERO, I = n, C = n;
    for (int i = 0; i < n; i++) {
        C = n; // asigno a la columna el valor de n 
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] != matriz[I-1][C-1]) {
                printf("\n No se refleja "); 
                bandera = FALSO;
            }
            C--;
        }
        C = n;
        I--;
    }
    return bandera;
}

/* En cada valdiacion verificamos el estado de la matriz. 
Si indica falso en alguna condicion, significa que no es trebol. 
Imprimimos el resultado y cerramos el programa */
void verificar(int estado) {
    if (estado == FALSO) {
        printf("\n La matriz no es trebol"); 
        exit(0); 
    }
}

void imprimirMatriz(int n, int matriz[n][n]) {
    for (int i = 0; i<n; i++) {
        printf("\n"); 
        for (int j = 0; j<n; j++) {
            printf("%4d", matriz[i][j]); 
        }
    }
}

void cargarMatriz(int n, int matriz[n][n]) {
    // Inicializamos la matriz
    printf("\n Ingrese los valores de la matriz %d x %d\n",n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("\n Posicion [%d][%d]: ", i, j); 
            scanf("%d", &matriz[i][j]);
        }
    }
}

