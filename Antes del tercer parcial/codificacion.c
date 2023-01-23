/* 
Segundo Parcial de IEN - Colbes 
Jazmin Gamarra 
8/06/22 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define TAM_CHAR 20

// PROTOTIPOS =) 
void verificarInvalidez(char cadena[], char cadenaCodificada[]); 
void codificar (char cadOr[], char cadCod[]);
int calcularIndiceMatriz(int longitud);
void cargarMatriz ( int indiceMatriz, char matriz[indiceMatriz][indiceMatriz], char cadOr[]) ; 
void imprimirMatriz(int indiceMatriz, char matriz[indiceMatriz][indiceMatriz]) ; 


int main (){
    // leemos y verificamos la cadena original 
    char cadenaOriginal[TAM_CHAR]; 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\nIngrese la cadena a codificar: "); 
    fflush(stdin); 
    fgets(cadenaOriginal, TAM_CHAR, stdin   );

    char cadenaCodificada[calcularIndiceMatriz(strlen(cadenaOriginal))]; 
    verificarInvalidez(cadenaOriginal, cadenaCodificada); 

    codificar(cadenaOriginal, cadenaCodificada); 

    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n La cadena codificada es [ %s ]", cadenaCodificada); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
}

void codificar (char cadOr[], char cadCod[]) {

    // generamos y cargamos la matriz 
    int indiceMatriz = calcularIndiceMatriz(strlen(cadOr)); 
    char matriz [indiceMatriz][indiceMatriz]; 
    cargarMatriz(indiceMatriz, matriz, cadOr); 
    imprimirMatriz(indiceMatriz, matriz);  

    // CREAMOS EL CODIGO

    int k=0; // representa la pos de la cadena en donde se guardará 
    int longitud = indiceMatriz*indiceMatriz;  // es el nro de caracteres que se debe guardar en el codigo 

    // primero guardamos los caracteres de la diagonal principal
    for (k; k<indiceMatriz; k++) {
        cadCod[k]=matriz[k][k]; 
    }


    /*Para los caracteres del triangulo superior, iteraremos desde la primera posicion despues de la diagonal 
    principal hasta la ultima casilla donde i=0 y j=indiceMatriz

    Al llegar a la ultima columna donde j=indiceMatriz, deben volver arriba y correrse a la sgte diagonal 
    la variable fila indica la siguiente posicion de inicio, que seria (0, columna)
    las variables i y j son las que recorren
    */

    int i=0, j=1, columna=1; 

    while ((columna != indiceMatriz)) {

        cadCod[k]=matriz[i][j]; 
        i++; j++; k++; 

        if (j==indiceMatriz) {
            columna++;     
            i=0;     
            j=columna; 
        }
    }

    /* Para los caracteres del triangulo inferior haremos lo mismo pero invirtiendo las cond. en cuanto a filas y columnas */

    i=1; j=0; int fila=1; 

    while ((fila != indiceMatriz)) {

        cadCod[k]=matriz[i][j]; 
        i++; j++; k++; 

        if (i==indiceMatriz) {
            fila++;     
            j=0;     
            i=fila; 
        }
    }
    cadCod[k]  = '\0'; 


}

void cargarMatriz ( int indiceMatriz, char matriz[indiceMatriz][indiceMatriz], char cadOr[]) {
     int k=0; 
    for (int i=0; i<indiceMatriz; i++) {
        for (int j = 0; j < indiceMatriz; j++) {
            if (k < strlen(cadOr)-1) {  // le resto uno para que no cargue el \n que cierra la cadena 
                matriz[i][j] = cadOr[k]; 
                k++; 
            } else {
                matriz[i][j] = '?'; 
            }
        }
    }
}

void verificarInvalidez(char cadena[], char cadenaCodificada[]) {
    for (int i=0; i<strlen(cadena); i++) {
        if ((int)cadena[i] == 63) {
            strcpy(cadenaCodificada, cadena); 
            printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
            printf("\nLa cadena introducida tiene un caracter invalido.\n=>  La cadena codificada es %s. \nSe cerrara el programa.", cadenaCodificada); 
            printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
            exit(-1);
        }
    }
}

int calcularIndiceMatriz(int longitud) {
    int temporal = 0; 

    while ((temporal * temporal) < longitud) {
        temporal++; 
    }
    return temporal; 
}

void imprimirMatriz(int indiceMatriz, char matriz[indiceMatriz][indiceMatriz]) {
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\nLa matriz generada es: \n"); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    for (int i=0; i<indiceMatriz; i++) {
            printf("\n\t"); 
        for (int j=0; j<indiceMatriz; j++) { 
            printf("%3c", matriz[i][j]); 
        }
    }
}