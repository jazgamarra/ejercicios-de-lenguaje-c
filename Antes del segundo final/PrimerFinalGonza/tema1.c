/*Tema 1 
Gonzalo Cristaldo - IEN
5278949 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    #define ARCHIVO_DATOS "tema1.csv"
    #define MODO_APERTURA "r"
    #define TAM_CHAR 20 
    #define PRIMER_SEMESTRE 1
    #define SEGUNDO_SEMESTRE 2 
    #define VACIO -1 

    typedef struct {
        int codSuc; 
        int codVend ;
        char codArt[TAM_CHAR]; 
        int precio; 
        int semestre; 
    } RegistroArchivo; 

    typedef struct {
        int grupoSucursal; 
        int grupoSemestral; 
        int totalSemestral;  
        int totalPorSucursal; 
        int cantArticulosVendidos;
        struct {
            int codSuc; 
            int total; 
        } sucursalMayorVenta; 
        struct {
            int codSuc; 
            int cantidad; 
        } sucursalMasArticulos;
        int articulosPorSucursal; 
    } RegistroControl;

    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void corteSucursal(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    RegistroArchivo leerRegistroArchivo(FILE *);
    void corteSemestral(RegistroArchivo regArch, RegistroControl *regControl);  
    void cabecera(); 

int main(void) {

    FILE *fd = abrirArchivo(ARCHIVO_DATOS, MODO_APERTURA);
    procesarArchivo(fd);
    cerrarArchivo(fd);

    return 0;

}

void procesarArchivo(FILE *fd) {

    RegistroArchivo regArchivo;
    RegistroControl regControl;


    regArchivo = leerRegistroArchivo(fd);

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO_DATOS);
       return;
    }
    cabecera(); 
    primerRegistro(regArchivo, &regControl);

    while (!feof(fd)) {
        
        if (regArchivo.codSuc != regControl.grupoSucursal) {
            corteSucursal(regArchivo, &regControl);
        } else if (regControl.grupoSemestral != regArchivo.semestre){
            corteSemestral(regArchivo, &regControl); 
        }

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);

    }
    corteSucursal(regArchivo, &regControl);
    
}

void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    // inicializo los valores de los grupos en la variable de control 
    regControl->grupoSucursal = regArch.codSuc; 
    regControl->grupoSemestral = regArch.semestre; 

    // inicio los contadores y totalizadores 
    regControl->cantArticulosVendidos = 0; 
    regControl->totalPorSucursal = 0; 
    regControl->sucursalMayorVenta.total = 0; 
    regControl->totalSemestral = 0; 
    regControl->sucursalMasArticulos.cantidad = 0; 
    regControl->articulosPorSucursal = 0; 

}

void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    // se suman los contadores y totalizadores
    regControl->cantArticulosVendidos++; 
    regControl->totalSemestral += regArch.precio; 
    regControl->totalPorSucursal += regArch.precio; 
}

void corteSemestral(RegistroArchivo regArch, RegistroControl *regControl) {

    // se imprime el informe semestral
    printf("\n"); 
    printf("\n  #%d%14d%14d%10d", regControl->grupoSucursal, regControl->grupoSemestral, regControl->totalSemestral, regControl->cantArticulosVendidos); 
    printf("\n"); 
    
    regControl->articulosPorSucursal += regControl->cantArticulosVendidos; 
    regControl->grupoSemestral = regArch.semestre; 
    regControl->cantArticulosVendidos = 0; 
    regControl->totalSemestral = 0; 
}

void corteSucursal(RegistroArchivo regArch, RegistroControl *regControl){
    corteSemestral(regArch, regControl);

    // se realizan los calculos por sucursal 

    // comparo si vendi mas articulos 
    if (regControl->sucursalMasArticulos.cantidad < regControl->articulosPorSucursal) {
        regControl->sucursalMasArticulos.cantidad = regControl->articulosPorSucursal; 
        regControl->sucursalMasArticulos.codSuc = regControl->grupoSucursal; 
    }

    // comparo si obtuve una venta mayor a la mayor venta 
    if (regControl->sucursalMayorVenta.total < regControl->totalPorSucursal) {
        regControl->sucursalMayorVenta.total = regControl->totalPorSucursal; 
        regControl->sucursalMayorVenta.codSuc = regControl->grupoSucursal; 
    }
    
    // Si es el ultimo registro, imprimo los resultados.
    // Sé que es el ultimo registro a procesar porque el sgte leido tiene precio cero
    if (regArch.precio == 0) {
        printf("\nLa sucursal con mayor venta fue la %d con Gs. %d", regControl->sucursalMayorVenta.codSuc, regControl->sucursalMayorVenta.total); 
        printf("\nLa sucursal que vendio mas fue la %d con %d articulos", regControl->sucursalMasArticulos.codSuc, regControl->sucursalMasArticulos.cantidad); 
        printf("\n\n"); 
    }

    // vuelvo a inicializar mis variables de control 
    regControl->grupoSucursal = regArch.codSuc; 
    regControl->totalPorSucursal = 0; 
    regControl->sucursalMayorVenta.total = 0; 
    regControl->sucursalMasArticulos.cantidad = 0; 
    regControl->articulosPorSucursal = 0  ; 
}

FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    int mes; 
    fscanf(fd, "%d,%d,%*d/%d/%*d,%[^,],%d", &r.codSuc, &r.codVend, &mes, r.codArt, &r.precio);
    /*No necesito almacenar el mes, solo necesito saber en que semestre se encuentra
    Asi que comparo y almaceno solo el semestre*/
    if (mes > 0 && mes < 7) {
        r.semestre = PRIMER_SEMESTRE; 
    }
    if (mes > 6 && mes < 13) {
        r.semestre = SEGUNDO_SEMESTRE; 
    }
    return r;
}

void cerrarArchivo(FILE *fd) {
    if (fd != NULL) // si ya se llego a la ultima linea del archivo
        fclose(fd);
}

void cabecera() {
    printf("\n------------------------------------------------"); 
    printf("\n%3s %12s %10s %14s", "SUCURSAL", "SEMESTRE", "TOTAL", "ARTICULOS"); 
    printf("\n------------------------------------------------"); 
}