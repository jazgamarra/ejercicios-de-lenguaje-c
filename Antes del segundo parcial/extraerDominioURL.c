#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ; 
void cerrarArchivo(FILE *fd) ; 

int main (){
    char url[50]; 
    strcpy(url, "http://lulzsecurity.com/releases" ); 
// cargo mis dominios en un vector de 10 
    char dominios[10][5]; 
    FILE *fd;
    fd = abrirArchivo("archivosCSV/ejer2_Dominios.csv", "r"); 
    for (int i=0; i<10; i++) {
        fscanf(fd, " %s", dominios[i]); 
    }
    printf("\n Dominios: "); 
    for (int i=0; i<10; i++) {
        printf(" %s", dominios[i]); 
    }
    cerrarArchivo(fd); 
// comparo que dominio coincide ???
    int dominio; 
    
    printf("\nEl dominio es: %s", dominios[dominio]); 
}


/* Funcion encargada de la apertura del archivo a procesar, en caso de falla, terminamos el programa.*/
FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

/* Cierra el archivo cuyo descriptor se recibe como parametro. */
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}
