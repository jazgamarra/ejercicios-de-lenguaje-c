#include <stdio.h> 
#include <stdlib.h> 

// Constantes 
#define N 4
#define VERDADERO 1
#define FALSO 0 
#define BUSCAR_MAYOR 2
#define BUSCAR_MENOR 3 
#define VACIO 0

typedef struct nodo {
    int inicio, longitud; 
} Vector; 

// Prototipos
int buscarPrimerElemento (int matriz[N][N], int menor, int i, int j, int bandera); 
Vector * recursionPrincipal (int matriz[N][N], int elemento, int existe, int condicionFin, int inicio, int longitud, Vector *secuencias, int * indiceVector); 
Vector * almacenarSecuencia(Vector *vector, int *indice, int inicio, int longitud); 
int buscarPrimerElemento (int matriz[N][N], int elemento, int i, int j, int bandera); 
int buscarElemento (int matriz[N][N], int elemento, int centinela, int i, int j); 
void imprimirVector(Vector *vector, int indice); 
void imprimirMatriz (int matriz [N][N], int i, int j); 
void errorMemoria (); 
void resultadosFinales(Vector *vector, int indiceVector); 

// Funcion Principal 
int main () {

	int matriz[N][N] = {15,2,12,8,1,14,10,5,8,9,3,16,11,8,6,7}; 
    imprimirMatriz(matriz, 0, 0); 

    // Se comenzara a iterar desde el menor elemento buscando siempre n+1 
    int menor = buscarPrimerElemento (matriz, matriz[0][0], 0, 0, BUSCAR_MENOR); 
    int mayor = buscarPrimerElemento (matriz, matriz[0][0], 0, 0, BUSCAR_MAYOR); 
    printf("\nEl elemento menor es %d y el mayor es %d", menor, mayor); 

    // recursion principal 
    Vector *secuencias = NULL; int indiceVector = 0;  
    secuencias = recursionPrincipal(matriz, menor, FALSO, mayor, VACIO, VACIO, secuencias, &indiceVector); 

    resultadosFinales(secuencias, indiceVector); 
}

/* Recursion principal */
Vector * recursionPrincipal (int matriz[N][N], int elemento, int existe, int condicionFin, int inicio, int longitud, Vector *secuencias, int * indiceVector) {
    if (elemento == condicionFin) {
        return secuencias; 
    }  
    // si es el primer elemento de una secuencia 
    if (existe == VERDADERO && longitud == VACIO) {
        inicio = elemento-1; 
    }
    // si existe el elemento se aumenta la longitud en uno
    if (existe == VERDADERO) { 
        longitud++; 
    }

    // si se rompe una secuencia mayor o igual a 2 
    if (existe == FALSO && longitud >= 2) {    
        secuencias = almacenarSecuencia(secuencias, indiceVector, inicio, longitud); 
        inicio = 0; 
        longitud = 0; 
    } 
    existe = buscarElemento(matriz, elemento, FALSO, 0, 0); 
    recursionPrincipal (matriz, elemento+1, existe, condicionFin, inicio, longitud, secuencias, indiceVector); 
}

/* Se iniciara con el numero menor */
int buscarPrimerElemento (int matriz[N][N], int elemento, int i, int j, int bandera) {
    if ( j < N && i < N){
        
        if (bandera == BUSCAR_MENOR){
            if (matriz [i][j] < elemento) {
                elemento = matriz[i][j]; 
            }
        }

        if (bandera == BUSCAR_MAYOR){
            if (matriz [i][j] > elemento) {
                elemento = matriz[i][j]; 
            }
        }

        if (j == N - 1){
            j = 0;
            i++; 
        }else{
            j++;
        }

        buscarPrimerElemento (matriz, elemento, i, j, bandera); 
    } else {
        return elemento; 
    } 
}

/* Se busca si existe n+1 en la matriz*/
int buscarElemento (int matriz[N][N], int elemento, int centinela, int i, int j) {
    if (j >= 0 && j < N && i >= 0 && i < N){
        
        // busco si existe el elemento 
        if (matriz [i][j] == elemento) {
            centinela = VERDADERO;  
        }

        if (j == N - 1){
            j = 0;
            i++;
        }else{
            j++;
        }
        buscarElemento (matriz, elemento, centinela, i, j); 
    } else {
        return centinela; 
    }
}


void imprimirMatriz (int matriz[N][N], int i, int j) {
    if ( j < N && i < N){
        printf("%5d", matriz [i][j]); 
        if (j == N - 1){
            j = 0;
            i++;
            printf("\n"); 
        }else{
            j++;
        }
        imprimirMatriz(matriz, i, j);
    }
}

/* Lista enlazada para almacena las secuencias mayores a 2 */
Vector * almacenarSecuencia(Vector *vector, int *indice, int inicio, int longitud) {
    if (* indice == 0){
        vector = malloc(VERDADERO); 
    }
    * indice = * indice + 1; 
    vector = realloc(vector, *indice * sizeof(Vector)); 
    if (vector != NULL){
        vector[*indice-1].inicio = inicio; 
        vector[*indice-1].longitud = longitud; 
    } else {
        errorMemoria(); 
    }

    return vector; 
}

/*Imprime un mensaje si no se puede continuar la ejecucion or un error en la memoria */ 
void errorMemoria () {
	printf("Error en el almacenamiento de la memoria =(");
	exit(-1); 
}

void resultadosFinales(Vector *vector, int indiceVector) { 
    for (int k=0; k<indiceVector; k++){
        printf("\n Secuencia #%d", k+1); 
        for (int i=0; i<vector[k].longitud; i++) {
            printf("%4d", i+vector[k].inicio); 
        }
    }
}