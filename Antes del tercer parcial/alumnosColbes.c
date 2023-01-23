/* Ejercicio Prof. Colbes 
Franjas Etarias (Alumnos ) - Archivos sin corte de control 
Jazmin Gamarra 
12/06/2022
*/

#include <stdio.h>
#include <stdlib.h> // registros 
#include <string.h> // strcpy

// CONSTANTES 
    #define ARCHIVO "alumnosColbes.csv"
    #define MODO_LECTURA "r" 
    #define TAM_CHAR 20 
    #define FEMENINO 'F'
    #define MASCULINO 'M'
    #define CANT_FRANJAS_ETARIAS 5
    #define ANHO_ACTUAL 2022
    #define MENOR_ANHO 2015 
    
// ESTRUCTURAS
    typedef struct {
        int dia, mes, anho; 
    } Fecha; 

    typedef struct {
        int cedula; 
        char apellido[TAM_CHAR]; 
        char nombre[TAM_CHAR]; 
        char sexo; 
        Fecha fecha; 
        int anhoIngreso; 
        int edad; 
    } Alumno;

    typedef struct {
        int masculino, femenino, total; 
    } FranjasEtarias; 

    typedef struct { 
        FranjasEtarias franjas[CANT_FRANJAS_ETARIAS]; 
        Alumno masJoven; 
    } DatosAlmacenados;
   
// PROTOTIPOS
    FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ;
    void cerrarArchivo(FILE *fd) ; 
    void procesarArchivo(FILE *fd); 
    Alumno leerRegistroArchivo(FILE *fd); 
    void procesarRegistro(Alumno, DatosAlmacenados *);
    void imprimirInforme (DatosAlmacenados informe); 
    void inicializarDatosAlmacenados (DatosAlmacenados * informe, Alumno registro) ; 
    int calcularFranjaEtaria (int edad) ; 
    void guardarAlumnoMasJoven(Alumno registro, DatosAlmacenados *informe); 

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
    
    Alumno registro; 
    DatosAlmacenados informe; // asociaré el indice del vector a el codigo de empleado. Le sumo 1 porque dejare la posicion 0 vacia 


    registro = leerRegistroArchivo(fd);
    inicializarDatosAlmacenados(&informe, registro); 
    while (!feof(fd)) {
        procesarRegistro(registro, &informe);
        registro = leerRegistroArchivo(fd);
    }
    imprimirInforme(informe); 
}

/* Impresion del informe final */
void imprimirInforme (DatosAlmacenados informe) {
    printf("\n El alumno mas joven es %s %s con %d anhos", informe.masJoven.nombre, informe.masJoven.apellido, informe.masJoven.edad); 

        for (int j=0; j<CANT_FRANJAS_ETARIAS; j++){
            printf("\n\n- Franja [%d] - - - \n Masculino: %d \n Femenino: %d \n Total: %d ", j , informe.franjas[j].masculino, informe.franjas[j].femenino, informe.franjas[j].total);
        } 
}

/* Se inicializan las variables que guardaran las sumatorias */
void inicializarDatosAlmacenados (DatosAlmacenados * informe, Alumno registro) {
    for (int i=0; i<CANT_FRANJAS_ETARIAS; i++){
        informe->franjas[i].femenino = 0; 
        informe->franjas[i].masculino = 0; 
        informe->franjas[i].total = 0; 
    }
    // se guarda la edad del primer alumno para comparar desde ahi
    guardarAlumnoMasJoven(registro, informe); 
}

/* Procesa cada registro leido para cargar los datos al informe */
void procesarRegistro(Alumno registro, DatosAlmacenados * informe ) {

    // busco en donde sumar segun franja etaria y sexo 
    int franjaEtaria = calcularFranjaEtaria(registro.edad); 
    informe->franjas[franjaEtaria].total++; 

    if (registro.sexo == MASCULINO) {
        informe->franjas[franjaEtaria].masculino++; 
    }
    if (registro.sexo == FEMENINO) {
        informe->franjas[franjaEtaria].femenino++; 
    }

    // comparo con la edad del alumno mas joven 
    if (registro.anhoIngreso >= MENOR_ANHO) { // valido que su ingreso sea mayor o igual a 2015
        if (registro.edad < informe->masJoven.edad) {
            guardarAlumnoMasJoven(registro, informe); 
        }

        // si las edades son iguales, comparo el mes del cumple :)
        if (registro.edad == informe->masJoven.edad) {
            if (registro.fecha.mes < informe->masJoven.fecha.mes) {
                guardarAlumnoMasJoven(registro, informe);

            // si son del mismo mes, comparo los dias :)
            } else if (registro.fecha.mes == informe->masJoven.fecha.mes) {
                if (registro.fecha.dia < informe->masJoven.fecha.dia) {
                    guardarAlumnoMasJoven(registro, informe);
                }
            }
        }
    }
}

/* Se compara la edad para ver a que franja etaria corresponde */
int calcularFranjaEtaria (int edad) {
    
    int franjaEtaria; 

    if (edad < 19) {
        franjaEtaria = 0; 

    } else if (edad >= 19 && edad < 21) { 
        franjaEtaria = 1; 

    } else if (edad >= 21 && edad < 24) {
        franjaEtaria = 2; 

    } else if (edad >= 24 && edad < 30) {
        franjaEtaria = 3; 

    } else if ( edad > 30) {
        franjaEtaria = 4; 
        
    }
    return franjaEtaria; 

}

/* Se guardan los datos del alumno mas joven */
void guardarAlumnoMasJoven(Alumno registro, DatosAlmacenados *informe) {

    strcpy (informe->masJoven.nombre, registro.nombre); 
    strcpy (informe->masJoven.apellido, registro.apellido); 
    informe->masJoven.cedula = registro.cedula; 
    informe->masJoven.sexo = registro.sexo; 
    informe->masJoven.fecha.dia = registro.fecha.dia; 
    informe->masJoven.fecha.mes = registro.fecha.mes; 
    informe->masJoven.fecha.anho = registro.fecha.anho; 
    informe->masJoven.edad = registro.edad; 
}

/* Lee el registro actual del archivo */
Alumno leerRegistroArchivo(FILE *fd){
    Alumno r;  
    fscanf(fd, "%d,%[^,],%[^,],%c,%d/%d/%d,%d", &r.cedula, r.apellido, r.nombre, &r.sexo, &r.fecha.anho, &r.fecha.mes, &r.fecha.dia, &r.anhoIngreso);
    // printf("\n\t Se obtuvo: %d, %s, %s, %c, %d/%d/%d, %d", r.cedula, r.apellido, r.nombre, r.sexo, r.fecha.anho, r.fecha.mes, r.fecha.dia, r.anhoIngreso); 
    r.edad = ANHO_ACTUAL - r.fecha.anho;  

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