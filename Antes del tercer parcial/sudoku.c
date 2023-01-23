#include <stdio.h>
#include <stdlib.h>


#define N 9
#define TRUE 1
#define FALSE 0


// prototipos 
void cerarMatriz(int matriz [N][N]); // no es recursiva 
void imprimirMatriz(int matriz [N][N]);  // no es recursiva 
int recorrerMatriz(int i, int j, int matriz[N][N]);
int cargarElemento (int i, int j, int matriz[N][N], int bandera);
int verificarElementoFila(int f, int COL, int matriz[N][N], int banderita, int elemento); 
int verificarElementoColumna (int FILA, int c, int matriz[N][N], int banderita, int elemento) ; 

int main () {

    int matriz[N][N]; 
    cerarMatriz(matriz); 

    // imprimirMatriz(matriz); 
    recorrerMatriz(0, 0, matriz);
    imprimirMatriz(matriz); 

}
// RECORRER MATRIZ: recorre la matriz y llama a la funcion que carga los datos !! 
int recorrerMatriz(int i, int j, int matriz[N][N]) {

    if ((i == N)&&(j == N)) {
        return 0; 
    } else {
        if (matriz[i][j] == 0) { // si aun no se cargo elementos en ese campo... 
            cargarElemento(i, j, matriz, FALSE); 
        } 
        if (j == N) {
            j=0; 
            i=i+1; 
        }
        recorrerMatriz(i, j, matriz); 
    }
}

// CARGAR DATOS EN LA MATRIZ 
int cargarElemento (int i, int j, int matriz[N][N], int bandera) {

    if (bandera == TRUE) {
        return 0; 
    } else {
        matriz [i][j]= (rand() % 9)+1; 
        int banderitaFila = verificarElementoFila(0, j, matriz, TRUE, matriz[i][j]); 
        int banderitaColumna = verificarElementoFila(i, 0, matriz, TRUE, matriz[i][j]); 

        if ((banderitaFila == TRUE) && (banderitaColumna == TRUE)) {
            bandera = TRUE; 
        } 
        cargarElemento(i,j,matriz,bandera); 
    }
}

// Recorre la fila para verificar si ya existe ese elemento en la fila 
int verificarElementoFila(int f, int COL, int matriz[N][N], int banderita, int elemento) { // COL esta en mayusculas porque la columna es constante DENTRO DE ESTA FUNCION 
    if (f == N) {
        return banderita; 
    } else {
        if (matriz[f][COL] == elemento) {
            banderita = FALSE; 
        }
        verificarElementoFila(f+1, COL, matriz, banderita, elemento);
    }
}

int verificarElementoColumna (int FILA, int c, int matriz[N][N], int banderita, int elemento) { // FILA esta en mayusculas porque la fila es constante DENTRO DE ESTA FUNCION 
    if (c == N) {
        return banderita; 
    } else {
        if (matriz[FILA][c] == elemento) {
            banderita = FALSE; 
        }
        verificarElementoColumna(FILA, c+1, matriz, banderita, elemento); 
    }
}

// IMPRESION DE LA MATRIZ 
void imprimirMatriz(int matriz [N][N]) {
    
    for (int i=0; i<N; i++) {
        printf("\n");
        for (int j=0; j<N; j++) {
            printf ("%4d", matriz[i][j]); 
        }
    }
}

void cerarMatriz(int matriz [N][N]) {
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            matriz[i][j] = 0; 
        }
    }
}