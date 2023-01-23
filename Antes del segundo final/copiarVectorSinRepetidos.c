/* Escribir un programa que lea un número determinado de enteros (1000 como máximo) del terminal y los visualice en el mismo orden y con
la condición de que cada entero sólo se escriba una vez. Si el entero ya se ha impreso, no se debe visualizar de nuevo. Por ejemplo, si los 
números siguientes se leen desde el terminal 55 - 78 – 25 - 55 - 24 –3 - 7 el programa debe visualizar lo siguiente: 55 78 –25 55 24 –3 7. Se
debe tratar con punteros para tratar con el array en el que se hayan almacenado los números

NOTA: quiero crear un array dinamico q sea copia del array con los numeros no repetidos 
Jazmin Gamarra 
21/06/2022
*/

#include <stdio.h> 
#include <stdlib.h> 

// CONSTANTES 
#define N 20 
#define VERDADERO 1 
#define FALSO 0 

// PROTOTIPOS 
void cargarVector(int *vector); 
void imprimirVector(int *vector, int indice); 
void verificar(void * puntero); 
int * copiarSinEspacios (int * vector, int *copia, int *indiceCopia); 
void copiarVector (int * vector1, int * vector2, int indice); 
void liberar (void * puntero); 
int * cargarVectorCopia (int *copia, int *indiceCopia, int dato); 

// FUNCION PRINCIPAL
int main () {

    // se crea el vector con la dimension declarada como constante 
    int * vector; 
    vector = malloc(N*sizeof(int)); 
    verificar(vector); 

    // se carga con random e imprime el vector original 
    cargarVector(vector); 
    printf("\nEste es el vector original: ");
    imprimirVector(vector, N); 

    // se llama a la funcion que recorrera el vector para crear la copia 
    int * copia = NULL; 
    int indiceCopia = 0; 
    copia = copiarSinEspacios(vector, copia, &indiceCopia); 
    liberar(vector); 

    // se imprime la copia final 
    printf("\n\nEsta es la copia: ");
    imprimirVector(copia, indiceCopia);
    printf("\n\n"); 

}

int * copiarSinEspacios (int * vector, int *copia, int *indiceCopia){
    /* Se declaran dos banderas, una que controla si existe el elemento en el vector copia y la otra 
    controla si se repite en el vector original (para q se carguen los que aparecen una vez nomas)*/
    int existe, seRepite; 
    
    copia = malloc(VERDADERO); 

    for (int i=0; i<N; i++) {
        seRepite = FALSO; 
        for (int j=0; j<N; j++) {
            // si se encuentra el mismo elemento en una posicion que no es la misma 
            
            if (*(vector+i)==*(vector+j) && i!=j){
                // se verifica si ya está en el vector 
                seRepite = VERDADERO; 
                existe = FALSO; 
                for (int k=0; k<*indiceCopia; k++) {
                    if (*(copia+k) == *(vector+i)) {
                        existe = VERDADERO; 
                    }
                }

                // si no esta en el vector copia, se carga 
                if (existe == FALSO){   
                    copia = cargarVectorCopia(copia, indiceCopia, vector[i]); 
                } 
            }
        }
        // si el numero no se repite en el vector original debe cargarse ne la copia igualmente 
        if (seRepite == FALSO) {
            copia = cargarVectorCopia(copia, indiceCopia, vector[i]); 
        }
    }
    return copia; 
}

int * cargarVectorCopia (int *copia, int *indiceCopia, int dato){
    //  si el indice es distinto a cero se crea una copia temporal de los elementos q ya estan 
    int * temporal = NULL ; 
    if (*indiceCopia != 0){ 
        temporal = malloc(*indiceCopia * sizeof(int)); 
        verificar(temporal); 
        copiarVector(temporal, copia, *indiceCopia); 
    }

    // se redimensiona el vector y se copia lo que teniamos en temporal 
    *indiceCopia = *indiceCopia + 1; 
    copia = realloc(copia, *indiceCopia * sizeof(int)); 
    verificar(copia); 
    copiarVector(copia, temporal, *indiceCopia-1); 
    
    // se añade el ultimo elemento (nuevo :p)
    *(copia + (*indiceCopia-1)) = dato; 

    liberar(temporal); 
    return copia; 
}

void cargarVector(int *vector) {
    for (int i=0; i<N; i++) {
        *(vector+i) = rand()%10 ; 
    }
}

void imprimirVector(int *vector, int indice) {
    for (int i=0; i<indice; i++) {
        printf("%4d", *(vector+i)); 
    }
}

void verificar(void * puntero) {
    if (puntero == NULL ){
        printf("\nError en la asignacion dinamica. Se cerrara el programa"); 
        exit(-1); 
    } 
}

void copiarVector (int * vector1, int * vector2, int indice) {
    for (int m=0; m<indice; m++){
        *(vector1 + m) = *(vector2 + m);
    }
}

void liberar (void * puntero) { 
    if (puntero != NULL) {
        free(puntero); 
    }
}
