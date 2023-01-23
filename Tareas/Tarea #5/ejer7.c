/* 
Estadisticas de acceso por dias de la semana 
Jazmin Gamarra, Manu Baez y Silvia Candia
18/05/2022
Obs: En el informe, imprimo solo aquellos campos que tienen datos dentro, para no imprimir tantas lineas sin informacion
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CONSTANTES 
#define ARCHIVO "archivosCSV/ejer7_EstadisticasDeAcceso.csv"
#define MODO_APERTURA "r" 
#define ANHO 2008
#define MESES 12
#define DIAS_SEM 7 
#define SIN_REGISTRO "nulo"

// ESTRUCTURAS
    typedef struct {
        int codCliente; 
        struct f {
            int dia, mes, diaDeLaSemana; 
        } fecha; 
        char ip[15]; 
        int bytes; 

    } RegistroArchivo;

    typedef struct {
        int grupoCliente; 
        struct m {
            char ip[15]; 
            int bytes; 
        } informe[DIAS_SEM][MESES]; 
    } RegistroControl;

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]); 
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void procesarCorte(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    RegistroArchivo leerRegistroArchivo(FILE *);
    int diaDeLaSemana (int d, int m); 

// PROGRAMA PRINCIPAL 
int main(void) {

    // Abrimos el archivo especificado en ARCHIVO_DATOS.
    FILE *fd = abrirArchivo(ARCHIVO, MODO_APERTURA);
    // Procesamos el archivo por corte de control.
    procesarArchivo(fd);

    // Cerramos el archivo de datos.
    cerrarArchivo(fd);

    return 0;

}

/* Procesa el archivo con acceso secuencial mediante la tecnica del corte de control o ruptura por bloques.*/
void procesarArchivo(FILE *fd) {

    // Declaramos las variables estructuradas para datos y control.
    RegistroArchivo regArchivo;
    RegistroControl regControl;

    // Leemos el primer registro del archivo.
    regArchivo = leerRegistroArchivo(fd);

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO);
       return;
    }
    
    primerRegistro(regArchivo, &regControl);
    
    while (!feof(fd)) {
        
        if (regArchivo.codCliente != regControl.grupoCliente) {
            procesarCorte(regArchivo, &regControl);
        }

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);
    }
     procesarCorte(regArchivo, &regControl);
}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    // grupo 
    regControl->grupoCliente = regArch.codCliente;

    // matriz
   for (int i=0; i<DIAS_SEM; i++) {
        for (int j=0; j<MESES; j++)  {
                strcpy(regControl->informe[i][j].ip,SIN_REGISTRO); 
                regControl->informe[i][j].bytes = 0; 
        }
   }
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    for (int i=0; i<DIAS_SEM; i++) {
        for (int j=0; j<MESES; j++)  {
            if ((regArch.fecha.diaDeLaSemana == i) && (regArch.fecha.mes-1 == j)) {
                strcpy (regControl->informe[i][j].ip,regArch.ip); 
                regControl->informe[i][j].bytes += regArch.bytes ; 
            }
        }
   }

}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *r){
    
    char meses [12][10] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Setiembre", "Octubre", "Noviembre", "Diciembre" }; 
    char dias [7][10] = {"Domingo","Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"}; 
    int banderaMes; // para imprimir una vez nomas el mes 
    printf("\n\n Cliente: %d\n", r->grupoCliente); 
    
    for (int j=0; j<MESES; j++)  {
        banderaMes = 0; 
        for (int i=0; i<DIAS_SEM; i++) {
            if (strcmp(r->informe[i][j].ip , SIN_REGISTRO) != 0){
                if (banderaMes==0){
                    printf("\n\tMes: %s \n ", meses[j]); 
                    banderaMes = 1; 
                }
                printf("\t\tDia: %s | IP: %s | Bytes: %.2f ", dias[i],  r->informe[i][j].ip,((float)r->informe[i][j].bytes / (float) 1048576)); 
                printf("\n");
            }
        }
   }

    
    r->grupoCliente=regArch.codCliente; 
    for (int i=1; i<DIAS_SEM; i++) {
        for (int j=1; j<DIAS_SEM; j++)  {
            strcpy(r->informe[i][j].ip, SIN_REGISTRO); 
            r->informe[i][j].bytes = 0; 
        }
   }
   
}

/* Lee el registro actual del archivo */
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    fscanf(fd, " %d,%d/%d,%*d:%*d,%[^,],%d", &r.codCliente, &r.fecha.dia, &r.fecha.mes, r.ip, &r.bytes);
    r.fecha.diaDeLaSemana = diaDeLaSemana(r.fecha.dia, r.fecha.mes); 
            // printf("\n -> %d,%d/%d,%s,%d,%d", r.codCliente, r.fecha.dia, r.fecha.mes, r.ip, r.bytes, r.fecha.diaDeLaSemana); 
    return r;
}

/* Calculo del dia de la semana */
int diaDeLaSemana (int d, int m) {
    int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6}; // 2008 fue bisiesto :p
    m=bisiesto[m-1];
    d=(((ANHO-1)%7)+((((ANHO-1)/4)-((3*(((ANHO-1)/100)+1))/4))%7)+m+(d%7))%7;
    return d; 
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
