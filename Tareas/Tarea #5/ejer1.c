/*
Aguas S.A
Jazmin Gamarra, Manu Baez y Silvia Candia
11/05/2022*/

#include <stdio.h>
#include <stdlib.h> 

// CONSTANTES 
    #define ARCHIVO "archivosCSV/ejer1_LecturaMes.csv"
    #define MODO_LECTURA "r"
    #define COSTO_FIJO 45000
    #define COSTO_POR_M3 7000 

// ESTRUCTURAS 
    typedef struct {
        int nroMedidor; 
        int lectAnterior;
        int lectActual;  
    } Medidor; 

    typedef struct {
        int aguaConsumida; 
        int impuestoCobrado; 
    } Totales;

// PROTOTIPOS 
    FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ;
    void cerrarArchivo(FILE *fd) ; 
    void procesarArchivo (FILE *fd) ;
    int facturar (Medidor medidor ) ; 
    int calcularImpuestos ( int costo) ; 

/* Programa principal */
int main () {
    // abrimos el archivo
    FILE *fd; 
    fd = abrirArchivo(ARCHIVO, MODO_LECTURA); 

    //procesamos el archivo 
    procesarArchivo(fd); 

    // cerramos el archivo 
    cerrarArchivo(fd); 
}

/* Procesamos el archivo */
void procesarArchivo (FILE *fd) {
    
    Medidor medidor; // se usa para almacenar temporalmente cada valor leido 
    Totales totales; // Se usa para aculular los totales de agua y impuestos 
    totales.aguaConsumida=0; totales.impuestoCobrado=0; 

    fscanf(fd, "%d,%d,%d", &medidor.nroMedidor, &medidor.lectAnterior, &medidor.lectActual);

    while (!feof(fd)) { 

        printf("\n\n Cliente: %d \n Metros cubicos facturados: %d", medidor.nroMedidor, medidor.lectActual - medidor.lectAnterior);
        
        // Se calcula cuanto debe pagar el cliente y los totales 
        totales.impuestoCobrado = totales.impuestoCobrado + facturar (medidor);   
        totales.aguaConsumida=totales.aguaConsumida + (medidor.lectActual - medidor.lectAnterior); 

        fscanf(fd, "%d,%d,%d", &medidor.nroMedidor, &medidor.lectAnterior, &medidor.lectActual);
	}
    printf("\n \n \n El total de agua consumida es %d", totales.aguaConsumida); 
    printf("\n El total de impuestos es Gs. %d \n", totales.impuestoCobrado); 


}

/* la funcion facturar imprime en pantalla el costo a cobrar al cliente y retorna el impuesto cobrado */
int facturar (Medidor medidor ) {
 
    int impuestos=0, costoCobrar=0; 

    if ((medidor.lectActual - medidor.lectAnterior) <= 20) { // Se tiene libre por mes 20 m3
        costoCobrar = COSTO_FIJO; 
    } else { 
        costoCobrar = COSTO_FIJO + (COSTO_POR_M3 * ((medidor.lectActual-medidor.lectAnterior) - 20)); // le resto 20 al agua consumida pq tiene libre por mes 20 m3  
    }
        impuestos = calcularImpuestos(costoCobrar); 
        costoCobrar = costoCobrar + impuestos ; 
        printf("\n El costo a cobrar es Gs.%d", costoCobrar); 
        printf("\n Corresponde a AGUAS S.A Gs. %2.f", impuestos*0.75 );
    return impuestos;  
}

/* Se calcula el impuesto segun el costo a cobrar */
int calcularImpuestos ( int costo) {
    if (costo < 50000) {
        return costo*0.04; 
    }
    if ((costo>50000) && (costo<120000)) {
        return costo*0.03; 
    }
    if (costo>120000) {
        return costo*0.025; 
    }
}

/* Abrir el archivo */
FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

/* Cerrar el archivo */
void cerrarArchivo(FILE *fd) {
    fclose(fd);
} 