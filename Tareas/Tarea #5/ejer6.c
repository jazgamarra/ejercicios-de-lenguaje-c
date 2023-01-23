/* 

Prestamos biblioteca
Jazmin Gamarra, Manu Baez y Silvia Candia
18 /05/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CONSTANTES 
#define ARCHIVO "archivosCSV/ejer6_PrestamosBiblioteca.csv"
#define MODO_APERTURA "r" 
#define TAM_CHAR_COD 10
#define LIMITE_PRESTAMOS 50
#define LIBRE "LIBRE"

// ESTRUCTURAS
    typedef struct {
        int cedula; 
        int dia; 
        char codLibro[TAM_CHAR_COD]; 
        char tipoOper; 
        
    } RegistroArchivo;

    typedef struct {
        int grupoCedula; 
        struct lib {
            char codLibro [TAM_CHAR_COD]; 
            int diaPrestamo; 
            int diaDevolucion; 
        } libro[LIMITE_PRESTAMOS]; 
        int cantLibrosPrestados; // contador 
        int numeroLibrosDevueltos; // para prom de dias de prestamo 
        int acumuladorDiasDePrestamo; // para prom de dias de prestamo
        int acumuladorPrestamosPorDia;  // para prom de prestamos x dia 
        int acumuladorDevolucionesPorDia; // para prom de devoluciones x dia 
        int cantidadDias; // contador cantidad de dias para promedio de prestamos y devoluciones 
        int ultimoRegistroDias; // para verificar que ningun dia se cuente mas de una vez
    } RegistroControl;

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void procesarCorte(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    RegistroArchivo leerRegistroArchivo(FILE *);

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
        
        if (regArchivo.cedula != regControl.grupoCedula) {
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
    regControl->grupoCedula = regArch.cedula;

    // struct lib
   for (int i=1; i<LIMITE_PRESTAMOS; i++) {
        strcpy(regControl->libro[i].codLibro, LIBRE); 
        regControl->libro[i].diaPrestamo=0; 
        regControl->libro[i].diaDevolucion=0;
   }
    
    // contadores acumuladores totalizadores etc etc etc 
    regControl->cantLibrosPrestados =  0; 
    regControl->numeroLibrosDevueltos =  0;
    regControl->acumuladorDevolucionesPorDia =  0;
    regControl->acumuladorDiasDePrestamo =  0;
    regControl->acumuladorPrestamosPorDia =  0;
    regControl->cantidadDias =  0;
    regControl->ultimoRegistroDias =  0;

}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // struct lib 
    int indiceLibro = 0; int i=0; 

    while ((strcmp(regControl->libro[i].codLibro,LIBRE) != 0 ) ) {
        if (strcmp(regArch.codLibro, regControl->libro[i].codLibro) == 0) {
            indiceLibro = i; 
        }
        i++; 
    }
    if (indiceLibro == 0) { // si aun no existe el libro en el vector 
        // buscamos el sgte campo libre 
        i=0; 
        while (strcmp(regControl->libro[i].codLibro,LIBRE) != 0) {
            i++; 
        }
        indiceLibro = i; // encontré :p

        regControl->cantLibrosPrestados += 1;  
        indiceLibro=regControl->cantLibrosPrestados-1; 
        strcpy( regControl->libro[indiceLibro].codLibro, regArch.codLibro);  
        regControl->libro[indiceLibro].diaPrestamo=0; 
        regControl->libro[indiceLibro].diaDevolucion=0;
    }
    if (regArch.tipoOper == 'P') {
        regControl->libro[indiceLibro].diaPrestamo=regArch.dia;
        regControl->acumuladorPrestamosPorDia += 1;     
    }
    if (regArch.tipoOper == 'D') {
        // valido q nunca se va a devolver un libro q no se prestó
        if (regControl->libro[indiceLibro].diaPrestamo != 0) {
            regControl->libro[indiceLibro].diaDevolucion=regArch.dia;
            regControl->acumuladorDevolucionesPorDia += 1; 
            regControl->numeroLibrosDevueltos += 1; 
            regControl->acumuladorDiasDePrestamo += (regControl->libro[indiceLibro].diaDevolucion - regControl->libro[indiceLibro].diaPrestamo); 
        }
    }

    // cantidad de dias, acumulador prestamo dias 
    if (regControl->ultimoRegistroDias != regArch.dia){
        regControl->cantidadDias += 1; 
        regControl->ultimoRegistroDias = regArch.dia; 
    }

}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *r){
    
    printf("\n\n Cedula del alumno: %d", r->grupoCedula); 
    printf("\n\t Numero de libros prestados: %d", r->cantLibrosPrestados);
    printf("\n\t Numero de libros devueltos: %d", r->numeroLibrosDevueltos);
    printf("\n\t Promedio de dias de prestamo: %d ", r->acumuladorDiasDePrestamo/r->numeroLibrosDevueltos);
    printf("\n\t Libros adeudados: ");

    int i=0; 
    while ((strcmp(r->libro[i].codLibro,LIBRE)!=0) && (i<LIMITE_PRESTAMOS)){
        if (r->libro[i].diaDevolucion == 0) {
            printf("%s - ", r->libro[i].codLibro); 
        }
        i++; 
    }
    printf("\n\t Promedio de prestamos por dia: %f ", (float)r->acumuladorPrestamosPorDia/r->cantidadDias);
    printf("\n\t Promedio de devoluciones por dia: %f", (float)r->acumuladorDevolucionesPorDia/r->cantidadDias);

    // inicializar de nuevo 
     r->grupoCedula = regArch.cedula;
    
    // struct lib
    for (int i=0; i<LIMITE_PRESTAMOS; i++) {
        strcpy(r->libro[i].codLibro, LIBRE); 
        r->libro[i].diaPrestamo=0; 
        r->libro[i].diaDevolucion=0;
   }

    // contadores acumuladores totalizadores etc etc etc 
    r->cantLibrosPrestados =  0; 
    r->numeroLibrosDevueltos =  0;
    r->acumuladorDevolucionesPorDia =  0;
    r->acumuladorDiasDePrestamo =  0;
    r->acumuladorPrestamosPorDia =  0;
    r->cantidadDias =  0;
    r->ultimoRegistroDias =  0;
}

/* Lee el registro actual del archivo */
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    fscanf(fd, "%d,%d,%[^,],%c", &r.cedula, &r.dia, r.codLibro, &r.tipoOper );
    return r;
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
