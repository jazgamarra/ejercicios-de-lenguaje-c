/* Ejercicio Prof. Colbes 
Promedio de Horario de entrada - Archivos sin corte de control 
Jazmin Gamarra 
10/06/2022
*/

#include <stdio.h>
#include <stdlib.h> // registros 
#include <string.h> // strcmp

// CONSTANTES 
    #define ARCHIVO "promedioHoraEntrada.csv"
    #define MODO_LECTURA "r" 
    #define CANT_EMPLEADOS 4 
    #define TAM_CHAR 20
    #define SIN_NOMBRE "nulo"


// ESTRUCTURAS
    typedef struct {
        int codigoEmpleado; 
        char nombre [TAM_CHAR];
        int minutos;
        char tipoOperacion; 
    } DatosLeidos;

    
    typedef struct {
        char nombre [TAM_CHAR]; 
        int sumaEntrada; 
        int sumaSalida;
        int diasContados;
    } DatosAlmacenados;
   

// PROTOTIPOS
    FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ;
    void cerrarArchivo(FILE *fd) ; 
    void procesarArchivo(FILE *fd); 
    DatosLeidos leerRegistroArchivo(FILE *fd); 
    void procesarRegistro(DatosLeidos, DatosAlmacenados *);
    void inicializarInforme (DatosAlmacenados informe[CANT_EMPLEADOS]); 
    void imprimirInforme (DatosAlmacenados informe[CANT_EMPLEADOS]);
    int calcularCantMinutos(int hora, int minuto) ;
    int impresionHoras (int minutos, int dias);
    int impresionMinutos (int minutos, int dias);

// FUNCION PRINCIPAL 
    int main() {

        // abrimos el archivo
        FILE *fd; 
        fd = abrirArchivo(ARCHIVO, MODO_LECTURA); 

        //procesamos el archivo 
        procesarArchivo(fd); 

        // cerramos el archivo 
        cerrarArchivo(fd); 

    }

/* Procesamos el archivo, llamando a la funcion que lee el archivo y al que procesa cada registro */
void procesarArchivo(FILE *fd) {
    
    DatosLeidos registro; 
    DatosAlmacenados informe[CANT_EMPLEADOS+1]; // asociaré el indice del vector a el codigo de empleado. Le sumo 1 porque dejare la posicion 0 vacia 
    
    inicializarInforme(informe); 

    registro = leerRegistroArchivo(fd);

    while (!feof(fd)) {

        procesarRegistro(registro, informe);
        registro = leerRegistroArchivo(fd);

    }
    imprimirInforme(informe); 
}

void imprimirInforme (DatosAlmacenados informe[CANT_EMPLEADOS]){
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n\t%s%18s%13s", "Nombre", "Entrada", "Salida" ); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - -"); 

    for (int i=1; i<=CANT_EMPLEADOS; i++) {
        printf("\n\t%s\t", informe[i].nombre);
        printf("%10dh %2dm", (impresionHoras(informe[i].sumaEntrada, informe[i].diasContados)), (impresionMinutos(informe[i].sumaEntrada, informe[i].diasContados)));
        printf("%10dh %2dm", (impresionHoras(informe[i].sumaSalida, informe[i].diasContados)), (impresionMinutos(informe[i].sumaSalida, informe[i].diasContados)) );
    }
}

int impresionHoras (int minutos, int dias) {
    return (int)((minutos/60)/dias); 
}

int impresionMinutos (int minutos, int dias) {
    
    int temporal = minutos; 
    while (temporal >= 60) {
        temporal = temporal - 60; 
    }
    
    return temporal; 
}

/* Procesa cada registro leido para cargar los datos al informe */
void procesarRegistro(DatosLeidos registro, DatosAlmacenados *informe) {
    if (strcmp(informe[registro.codigoEmpleado].nombre, SIN_NOMBRE) == 0) {
        strcpy(informe[registro.codigoEmpleado].nombre, registro.nombre); 
    }

    if (registro.tipoOperacion == 'E') {
        informe[registro.codigoEmpleado].sumaEntrada += registro.minutos; 
        informe[registro.codigoEmpleado].diasContados++;  
    }

    if (registro.tipoOperacion == 'S') {
        informe[registro.codigoEmpleado].sumaSalida += registro.minutos;  
    }
}

void inicializarInforme (DatosAlmacenados informe[CANT_EMPLEADOS]) {
    for (int i=0; i<=CANT_EMPLEADOS; i++) {
        strcpy(informe[i].nombre, SIN_NOMBRE); 
        informe[i].diasContados = 0; 
        informe[i].sumaEntrada = 0; 
        informe[i].sumaSalida = 0; 
    }
}

/* Lee el registro actual del archivo */
DatosLeidos leerRegistroArchivo(FILE *fd){
    DatosLeidos r;  
    int hora, minuto; 


    /*typedef struct {
        int codigoEmpleado; 
        char nombre [TAM_CHAR];
        int minutosEntrada; 
        int minutosSalida; 
        char tipoOperacion; 
    } DatosLeidos;*/
     
    fscanf(fd, "%d,%[^,],%*d/%*d/%*d,%d:%d,%c", &r.codigoEmpleado, r.nombre, &hora, &minuto, &r.tipoOperacion ); 
    // printf("\n Se obtuvo: %d  %s  %d:%d  %c", r.codigoEmpleado, r.nombre, hora, minuto, r.tipoOperacion); 
    r.minutos = calcularCantMinutos(hora, minuto);
    return r;
}

/* Para facilitar el calculo de promedios lo convertire a minutos para poder sumar y dividir directamente */
int calcularCantMinutos(int hora, int minuto) {
    return (hora*60)+minuto; 
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

/* Imprime un mensaje si no se ha podido reservar la memoria :p*/ 
    void errorMemoria () {
        printf("\n =( Error en el almacenamiento de la memoria =("); 
        exit (-1); 
    }