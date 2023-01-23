/*Escribir una función que utilice punteros para buscar la dirección de un entero dado en un
array dado. Si se encuentra el entero dado, la función devuelve su dirección; en caso contrario, devuelve NULL */

#include <stdio.h> 
#include <stdlib.h> 

// CONSTANTES 
#define N 5 
#define ELEMENTO_BUSCADO 7 
#define VERDADERO 1

// PROTOTIPOS 
int * buscarElemento(int * vector, int elemento, int indiceVector); 
void verificar(void * puntero); 
void cargarVector(int *vector); 
void imprimirVector(int *vector, int indice);
  
// FUNCION PRINCIPAL
int main () {

    int * vector; 
    vector = malloc(N*sizeof(int)); 
    verificar(vector); 
    cargarVector(vector); 
    printf("- - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n El elemento buscado es %d. \n- - - - - - - - - - - - - - - - - - - - -\n Impresion del vector con sus posiciones: \n", ELEMENTO_BUSCADO); 
    imprimirVector(vector, N); 
    printf("\n- - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n La posicion del elemento es: %p ", buscarElemento(vector, ELEMENTO_BUSCADO, N));  
    printf("\n- - - - - - - - - - - - - - - - - - - - -"); 

}

int * buscarElemento(int * vector, int elemento, int indiceVector) {
    int posicion = 0;
    for (int i = 0; i < indiceVector; i++) {
        if (*(vector + i) == elemento) {
            posicion = i; 
            break;
        }
    }
    if (posicion != 0) {
        return (vector + posicion); 
    } else {
        return NULL; 
    }
}

void verificar(void * puntero) {
    if (puntero == NULL ){
        printf("\nError en la asignacion dinamica. Se cerrara el programa"); 
        exit(-1); 
    } 
}

void cargarVector(int *vector) {
    for (int i=0; i<N; i++) {
        *(vector+i) = rand()%10 ; 
    }
}

void imprimirVector(int *vector, int indice) {
    for (int i=0; i<indice; i++) {
        printf("\n [%d] Dato: %d - Posicion: %p", i, *(vector+i), (vector+i)); 
    }
}
