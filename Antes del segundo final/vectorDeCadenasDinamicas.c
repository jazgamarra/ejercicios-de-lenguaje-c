/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
A. Dada la declaración del array de punteros:
    #define N 4 y char *linea[N];
    Escribir las sentencias de código para leer N líneas de caracteres y asignar cada línea a un 
    elemento del array
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
B.  Escribir un código de programa que elimine del array de N líneas del Problema 11.7 todas
    aquellas líneas de longitud menor que 20.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

Jazmin Gamarra 
25/06/22
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
#define LIMITE 10

typedef char * String; 
String leerCadena(String *cadena); 
void imprimirCadena(char * cadena[N]); 

int main (){
    char * linea[N];
    // Se llama a la funcion que leerá las cadenas 
    for (int i=0; i<N; i++){
        leerCadena(&(linea[i])); 
    }

    // Impresion de la cadenas originales 
    imprimirCadena(linea); 

    // Se borran los arrays de mas de LIMITE lineas 
    for (int i=0; i<N; i++){
        if (strlen(linea[i]) > LIMITE){
            printf("\nLa linea %d es mayor al limite", i); 
            free(linea[i]); 
            strcpy(linea[i],""); 
        } 
    }

    // Impresion de la cadena 
    imprimirCadena(linea); 
}

String leerCadena(String *cadena) {

    char c; // almacena el caracter leido 
    int i = 1; // controla tamaño de la cadena

    String auxiliar = NULL; 

    // controlo si hay algo ya en la cadena 
    if (*cadena != NULL) {
        free (*cadena); 
        *cadena = NULL; 
    }
    printf("\nIngrese la cadena. Al finalizar presione ENTER: ");

    while ((c=getchar()) != '\n') { // si se aprieta enter sin leer nada queda nulo
        auxiliar=(String)realloc(auxiliar, (i+2)*sizeof(char)); 

        if (auxiliar == NULL) {
            printf("Insuficiente memoria !"); 
            exit(-1); 
        }
        auxiliar[i-1]=c; 
        auxiliar[i] = '\0'; 
        i++;
    }

    (*cadena) = (String)realloc((*cadena), (strlen(auxiliar)+1)*sizeof(char) );     
    strcpy(*cadena , auxiliar); 
    
    free(auxiliar);
}

void imprimirCadena(char * cadena[N]) { 
    for (int i=0; i<N; i++){
        printf("\n %d - %s ", i, cadena[i]); 
    }
}