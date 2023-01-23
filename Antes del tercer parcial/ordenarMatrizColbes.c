/* 
Primer Final de IEN - Colbes 
Jazmin Gamarra 
11/06/22 

Nota: No sé porque no funciona para todos los casos :(
*/

#include <stdio.h>
#include <stdlib.h>

// prototipos 
int leervalidarIndice (); 
void generarMatriz ( int N, int matriz[N][N]);
void imprimirMatriz (int N, int matriz[N][N]); 
void ordenarCuadrante(int N, int matriz[N][N], int filaInicio, int columnaInicio, int filaFin, int columnaFin); 
void ordenarMatriz ( int indiceMatriz, int matriz[indiceMatriz][indiceMatriz]) ;

// funcion principal
int main () {
    int indice = leervalidarIndice(); 
    int matriz[indice][indice]; 
    generarMatriz(indice, matriz); 
    printf("\n\n MATRIZ DESORDENADA\n"); 
    imprimirMatriz(indice, matriz); 
    ordenarMatriz(indice, matriz); 
    printf("\n\n MATRIZ ORDENADA\n"); 
    imprimirMatriz(indice, matriz); 
}

int leervalidarIndice () {
    int indice;
    printf("Ingrese el indice de la matriz: "); 
    scanf("%d",&indice); 
    while ((indice % 2 != 0) || (indice < 3)) {
        printf("\n INGRESE EL NUMERO DE NUEVO \n Debe ser mayor a tres y par c:"); 
        scanf("%d",&indice); 
    }
    return indice; 
}

void generarMatriz ( int N, int matriz[N][N]) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            matriz[i][j] = rand () % (2*N-1); 
        }
    }
}

void imprimirMatriz (int N, int matriz[N][N]) {
    for (int i=0; i<N; i++) {
        printf("\n"); 
        for (int j=0; j<N; j++) {
            printf ("%5d",matriz[i][j]); 
        }
    }
}

void ordenarMatriz ( int indiceMatriz, int matriz[indiceMatriz][indiceMatriz]) {
    
    int indiceCuadrante = indiceMatriz / 2; 

    ordenarCuadrante(indiceMatriz, matriz, 0, 0, indiceCuadrante, indiceCuadrante); 
    ordenarCuadrante(indiceMatriz, matriz, 0, indiceCuadrante, indiceCuadrante, indiceMatriz); 
    ordenarCuadrante(indiceMatriz, matriz, indiceCuadrante, 0, indiceMatriz, indiceCuadrante); 
    ordenarCuadrante(indiceMatriz, matriz, indiceCuadrante, indiceCuadrante, indiceMatriz, indiceMatriz);  

}

void ordenarCuadrante(int N, int matriz[N][N], int filaInicio, int columnaInicio, int filaFin, int columnaFin) {
    int auxiliar; 
    for (int i=filaInicio; i<filaFin-1; i++){
        for (int j=columnaInicio; j<columnaFin; j++){ 
            if ( matriz[i+1][j] < matriz[i][j]){
                auxiliar=matriz[i][j]; 
                matriz[i][j]=matriz[i+1][j]; 
                matriz[i+1][j]=auxiliar; 
            }
        }
	}	
}