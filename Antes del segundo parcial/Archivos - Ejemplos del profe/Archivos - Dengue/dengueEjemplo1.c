/**
 * Pequenho programa en donde se implementa el algoritmo para el procesamiento
 * secuencia de un archivo CSV por medio de la tecnica de corte de control.
 * Author: gdsosa@pol.una.py
 * Version: 20.SET.2016
 */

#include <stdio.h>
#include <stdlib.h>
#define ARCHIVO_DATOS "dengue.csv"
#define MODO_APERTURA "r"

// Definimos la estructura donde almacenar cada registro
// del archivo.
typedef struct {
    short etapaVida;
} RegistroArchivo;

// Definimos la estructura que contiene los campos de control
// y de calculo conforme el enunciado.
typedef struct {
    short grupoEtapaVida;
    short cantidadXEtapa;
    short totalPacientes;
} RegistroControl;

// Prototipos de las funciones.
FILE *abrirArchivo(char[], char[]);
void cerrarArchivo(FILE *);
void primerRegistro(RegistroArchivo, RegistroControl *);
void procesarRegistro(RegistroArchivo, RegistroControl *);
void procesarCorte(RegistroArchivo, RegistroControl *);
void imprimirCabecera(void);
void imprimirResultadosFinales(RegistroControl);
void procesarArchivo(FILE *);
RegistroArchivo leerRegistroArchivo(FILE *);

int main(void) {

    // Abrimos el archivo especificado en ARCHIVO_DATOS.
    FILE *fd = abrirArchivo(ARCHIVO_DATOS, MODO_APERTURA);

    // Procesamos el archivo por corte de control.
    procesarArchivo(fd);

    // Cerramos el archivo de datos.
    cerrarArchivo(fd);

    return 0;

}

// Procesa el archivo con acceso secuencial mediante la
// tecnica del corte de control o ruptura por bloques.
void procesarArchivo(FILE *fd) {

    // Declaramos las variables estructuradas para datos y control.
    RegistroArchivo regArchivo;
    RegistroControl regControl;

    // Leemos el primer registro del archivo.
    regArchivo = leerRegistroArchivo(fd);

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO_DATOS);
       return;
    }

    // Establecemos los valores iniciales para los calculos.
    primerRegistro(regArchivo, &regControl);

    // Iteramos sobre cada registro del archivo de datos.
    while (!feof(fd)) {
        // Verificamos si el registro actual ya pertenece al
        // siguiente grupo de procesamiento.
        if (regArchivo.etapaVida != regControl.grupoEtapaVida) {
            procesarCorte(regArchivo, &regControl);
        }
        // Procesamos el registro actual.
        procesarRegistro(regArchivo, &regControl);
        // Leemos el siguiente registro del archivo.
        regArchivo = leerRegistroArchivo(fd);
    }
    // Al llegar al final del arhivo estamos ante el ultimo bloque
    // de datos que debe procesarse.
    procesarCorte(regArchivo, &regControl);

    // Imprimimos los totales generales.
    imprimirResultadosFinales(regControl);

}

// Inicializa los valores ante el primer registro leido e
// imprime los titulos de la cabecera.
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->cantidadXEtapa = 0;
    regControl->totalPacientes = 0;
    regControl->grupoEtapaVida = regArch.etapaVida;
    imprimirCabecera();
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
   regControl->cantidadXEtapa++;
}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *regControl){
    printf("%5hd%18hd\n", regControl->grupoEtapaVida, regControl->cantidadXEtapa);
    regControl->totalPacientes += regControl->cantidadXEtapa;
    regControl->cantidadXEtapa = 0;
    regControl->grupoEtapaVida = regArch.etapaVida;
}

// Imprime los titulos de la cabecera.
void imprimirCabecera(void) {
    printf("%s\t%15s\n", "Etapa", "Cantidad");
    printf("%s\t%15s\n", "-----", "--------");
}

// Imprime los resultados finales.
void imprimirResultadosFinales(RegistroControl regControl) {
    printf("-----------------------\n");
    printf("Total Pacientes: %6hd\n", regControl.totalPacientes);
    printf("-----------------------\n");
}

// Funcion encargada de la apertura del archivo a procesar,
// en caso de falla, terminamos el programa.
FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

// Lee el registro actual del archivo cuyo puntero se recibe
// como parametro.
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    fscanf(fd, "%hd,%*hd", &r.etapaVida);
    return r;
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}
