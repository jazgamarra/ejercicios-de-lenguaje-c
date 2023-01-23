/* Palindromos  
Jazmin Gamarra
26/06/22 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define TAM_CHAR 20
#define VERDADERO 1
#define FALSO 0

// Prototipos.
void formaIterativa (char palabra[TAM_CHAR]); 

int main (){
    char palabra[TAM_CHAR]; 
    strcpy(palabra,"anna"); 

    formaIterativa(palabra); 

    int tmp = formaRecursiva(palabra, 0, strlen(palabra), 1); 
    verificarResultados(tmp); 
}

// Forma iterativa 
void formaIterativa (char palabra[TAM_CHAR]){
    int bandera = VERDADERO; 
    int repeticionesFor = strlen(palabra)/2;  // el FOR se usará para recorrer hasta la mitad de la cadena 

    int indiceFinal = strlen(palabra)-1; 
    /* despues de la mitad, se repetira del final hacia adelante. 
    El ultimo caracter ocupa la posicion strlen(palabra)-1. 
    A eso se le restara i */

    for (int i=0; i<repeticionesFor; i++) {
        if (palabra[i] != palabra[indiceFinal-i]) {
            bandera = FALSO; 
            break; 
        } 
    } 
    verificarResultados(bandera); 
}

// Forma recursiva 
int formaRecursiva (char palabra[TAM_CHAR], int indice, int longitud, int bandera){
    if (indice == longitud/2) {
        return bandera; 
    }
    if (bandera == FALSO){
        return bandera; 
    }
    if (palabra[indice] != palabra[longitud-1-indice]) {
        bandera = FALSO;
    }
    formaRecursiva(palabra, indice+1, longitud, bandera); 
}

// Imprime si es palindromo o no xd 
void verificarResultados (int bandera){
    if (bandera == VERDADERO){
        printf("\n Si es palindromo"); 
    } else {
        printf("\n No es palindromo"); 
    }
}