/* Primer tema - Tercer Parcial 
Jazmin Gamarra 
15/06/2022
*/

#include <stdio.h>
#include <stdlib.h> // registros 
#include <string.h> // strcmp y strcpy - carga y comparacion de cadenas 
#include <math.h> // abs - valor absoluto 

// CONSTANTES 
    #define ARCHIVO "mov90s.csv"
    #define MODO_LECTURA "r" 
    #define TAM_CHAR 20
    #define EXTRACCION 'E'
    #define DEPOSITO 'D'
    #define NULO 0

// ESTRUCTURAS
    typedef struct  {
            int dia, mes, anho; 
    } Fecha; 

    typedef struct {
        char cuenta [TAM_CHAR]; 
        Fecha fecha; 
        float importe; 
        char operacion; 
    } RegistroArchivo;

    typedef struct {
        // Por cliente 
        char grupoCuenta [TAM_CHAR]; 
        float saldoPorCuenta; 
        int cantSobregiros; 
        int sumaSobregiros; 
        // Por año 
        int grupoAnho; 
        float totalExtracciones; 
        float totalDepositos; 
        // Mayor sobregiro 
        float importeMayor; 
        Fecha fechaMayorSobregiro;
    } RegistroControl;
   

// PROTOTIPOS
    FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ;
    void cerrarArchivo(FILE *fd) ; 
    void procesarArchivo(FILE *fd); 
    RegistroArchivo leerRegistroArchivo(FILE *fd); 
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void corteCuenta(RegistroArchivo regArch, RegistroControl *regControl); 
    void corteAnho(RegistroArchivo regArch, RegistroControl *regControl); 
    void guardarFechaSobregiro(RegistroArchivo regArch, RegistroControl *regControl); 
    void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl); 

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

/* Procesamos el archivo, llamando a la funcion que lee el archivo y al que procesa cada regArch */
void procesarArchivo(FILE *fd) {
    
    RegistroArchivo regArch; 
    RegistroControl regControl; 

    regArch = leerRegistroArchivo(fd);

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO);
       return;
    }

    primerRegistro(regArch, &regControl);

    while (!feof(fd)) {
        
        if (regControl.grupoAnho != regArch.fecha.anho) {
            corteAnho(regArch, &regControl);
        } else if (strcmp (regControl.grupoCuenta,regArch.cuenta) != NULO){
            corteCuenta(regArch, &regControl); 
        }

        procesarRegistro(regArch, &regControl);
        regArch = leerRegistroArchivo(fd);

    }
}

/* Se inicializan los datos del registro de control*/
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    strcpy(regControl->grupoCuenta, regArch.cuenta); 
    regControl->saldoPorCuenta = NULO; 
    regControl->cantSobregiros = NULO; 
    regControl->sumaSobregiros = NULO; 

    regControl->grupoAnho = regArch.fecha.anho;
    regControl->totalDepositos = NULO; 
    regControl->totalExtracciones = NULO; 
    guardarFechaSobregiro(regArch, regControl);     
    regControl->importeMayor = NULO; 
}

/* Funcion para guardar la fecha del sobregiro = )*/
void guardarFechaSobregiro(RegistroArchivo regArch, RegistroControl *regControl) { 
    regControl->fechaMayorSobregiro.dia = regArch.fecha.dia;
    regControl->fechaMayorSobregiro.mes = regArch.fecha.mes;
    regControl->fechaMayorSobregiro.anho = regArch.fecha.anho;
}

/* Procesa cada regArch leido para cargar los datos al regControl */
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // se suma o resta el importe del saldo segun sea el tipo de operacion 
    if (regArch.operacion == DEPOSITO) {
        regControl->saldoPorCuenta += regArch.importe; 
        regControl->totalDepositos += regArch.importe; 
        
    }    
    if (regArch.operacion == EXTRACCION) {
        regControl->saldoPorCuenta -= regArch.importe; 
        regControl->totalExtracciones += regArch.importe; 
    }  
    
    // se compara si el saldo es negativo (si ocurre un sobregiro)

    if (regControl->saldoPorCuenta < NULO) {

        regControl->sumaSobregiros += abs(regControl->saldoPorCuenta); 
        regControl->cantSobregiros ++; 

        // si es el primer sobregiro, lo guardamos en importeMayor para compararlo con los siguientes 
        if (regControl->importeMayor == NULO) {
            regControl->importeMayor = (float) abs(regControl->saldoPorCuenta); 
        }

        // comparo si el importe de sobregiro actual es mayor al que teniamos antes 
        if (regControl->importeMayor <= (float)abs(regControl->saldoPorCuenta)) {
            regControl->importeMayor = (float) abs(regControl->saldoPorCuenta); 
            guardarFechaSobregiro(regArch, regControl);    
        }
    }

}

/* Lee el regArch actual del archivo */
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;  
     
    fscanf(fd, " %[^,],%d,%d,%d,%f,%c", r.cuenta, &r.fecha.anho, &r.fecha.mes, &r.fecha.dia, &r.importe, &r.operacion); 
    // printf("\n Se obtuvo: %s, %d,  %d,   %d,  %f,  %c", r.cuenta, r.fecha.anho, r.fecha.mes, r.fecha.dia, r.importe, r.operacion); 
    return r;
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

/* Corte por anho  */
void corteAnho(RegistroArchivo regArch, RegistroControl *regControl) { 
    corteCuenta(regArch, regControl); 
    printf("\n---------------------------------------------------------------------"); 
    printf("\n\n\n = = = ANHO %d = = = ", regControl->grupoAnho); 
    printf("\n El monto total de extracciones fue %.1f", (float)regControl->totalExtracciones); 
    printf("\n El monto total de depositos fue %.1f", (float)regControl->totalDepositos); 
    printf("\n La fecha de mayor sobregiro fue el %d/%d/%d con un monto de %1.f \n\n", regControl->fechaMayorSobregiro.dia, regControl->fechaMayorSobregiro.mes, regControl->fechaMayorSobregiro.anho, (float)regControl->importeMayor); 
    
    regControl->grupoAnho = regArch.fecha.anho; 
    regControl->totalDepositos = NULO; 
    regControl->totalExtracciones = NULO; 
    regControl->importeMayor = NULO; 
    guardarFechaSobregiro(regArch, regControl);
}

/* Corte por cuenta */
void corteCuenta(RegistroArchivo regArch, RegistroControl *regControl) {

    printf("\n---------------------------------------------------------------------"); 
    printf("\n -> CUENTA %s", regControl->grupoCuenta); 
    printf("\n El saldo actual de la cuenta es %.1f", regControl->saldoPorCuenta); 

    if (regControl->cantSobregiros != NULO){
        printf("\n La cantidad de sobregiros que hubo es de %d ", regControl->cantSobregiros); 
        printf("\n El promedio de sobregiros es de %.1f", (float)(regControl->sumaSobregiros)/(regControl->cantSobregiros)); 
    } else {
        printf("\n Esta cuenta no ha tenido sobregiros."); 
    }

    strcpy(regControl->grupoCuenta, regArch.cuenta); 
    regControl->saldoPorCuenta = NULO; 
    regControl->cantSobregiros = NULO; 
    regControl->sumaSobregiros = NULO; 
}