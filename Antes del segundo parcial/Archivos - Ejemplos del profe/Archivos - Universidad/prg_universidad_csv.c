#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARCHIVO_DATOS "universidad.csv"
#define MODO_APERTURA "r"
#define TAM_FAC 12
#define TAM_CAR 5
#define TAM_NOM 30

// Definimos la estructura donde almacenar cada registro
// del archivo.
typedef struct {
    char facultad[TAM_FAC];
    char carrera[TAM_CAR];
    short curso;
    long cedula;
    char alumno[TAM_NOM];
} RegistroArchivo;

// Definimos la estructura que contiene los campos de control
// y de calculo conforme el enunciado.
typedef struct {
    char grupoFacultad[TAM_FAC];
    char grupoCarrera[TAM_CAR];
    short grupoCurso;
    short totalAlumnosCurso;
    short totalAlumnosCarrera;
    short totalAlumnosFacultad;
    short cantidadCursos;
} RegistroControl;

// Prototipos de las funciones.
FILE *abrirArchivo(char[], char[]);
void cerrarArchivo(FILE *);
void primerRegistro(RegistroArchivo, RegistroControl *);
void procesarRegistro(RegistroArchivo, RegistroControl *);
void corteCurso(RegistroArchivo, RegistroControl *);
void corteCarrera(RegistroArchivo, RegistroControl *);
void corteFacultad(RegistroArchivo, RegistroControl *);
void procesarArchivo(FILE *);
RegistroArchivo leerRegistroArchivo(FILE *);

int main(void)
{
    // Abrimos el archivo y leemos el primer registro.
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

    // Leemos el registro actual del archivo.
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
        if (strcmp(regArchivo.facultad, regControl.grupoFacultad) != 0)  {
            corteFacultad(regArchivo, &regControl);
        } else if (strcmp(regArchivo.carrera, regControl.grupoCarrera) != 0) {
            corteCarrera(regArchivo, &regControl);
        } else if (regArchivo.curso != regControl.grupoCurso) {
            corteCurso(regArchivo, &regControl);
        }
        // Procesamos el registro actual.
        procesarRegistro(regArchivo, &regControl);
        // Leemos el siguiente registro del archivo.
        regArchivo = leerRegistroArchivo(fd);
    }
    // Al llegar al final del archivo estamos ante el ultimo grupo
    // de datos que debe procesarse.
    corteFacultad(regArchivo, &regControl);

}

// Inicializa los valores ante el primer registro leido e
// imprime los titulos de la cabecera.
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->totalAlumnosFacultad = 0;
    regControl->totalAlumnosCarrera  = 0;
    regControl->totalAlumnosCurso    = 0;
    regControl->cantidadCursos       = 0;
    regControl->grupoCurso          = regArch.curso;
    strcpy(regControl->grupoCarrera,  regArch.carrera);
    strcpy(regControl->grupoFacultad, regArch.facultad);
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    printf("\n\t\t\t%ld\t%s\n", regArch.cedula, regArch.alumno);
    regControl->totalAlumnosCurso++;
}

// Procesa el corte del grupo anterior de curso.
void corteCurso(RegistroArchivo regArch, RegistroControl *regControl){
    printf("\n\t\tTotal de Alumnos del curso %hd: %hd\n",
            regControl->grupoCurso, regControl->totalAlumnosCurso);
    regControl->totalAlumnosCarrera += regControl->totalAlumnosCurso;
    regControl->totalAlumnosCurso   = 0;
    regControl->grupoCurso         = regArch.curso;
    regControl->cantidadCursos++;
}


// Procesa el corte del grupo anterior de la carrera.
void corteCarrera(RegistroArchivo regArch, RegistroControl *regControl){
    corteCurso(regArch, regControl);
    printf("\n\t\tPromedio de Alumnos de la carrera %s: %.2f\n",
           regControl->grupoCarrera,
           (float)regControl->totalAlumnosCarrera / regControl->cantidadCursos);
    regControl->totalAlumnosFacultad += regControl->totalAlumnosCarrera;
    regControl->totalAlumnosCarrera   = 0;
    regControl->cantidadCursos        = 0;
    strcpy(regControl->grupoCarrera, regArch.carrera);
}

// Procesa el corte del grupo anterior de la facultad.
void corteFacultad(RegistroArchivo regArch, RegistroControl *regControl){
    corteCarrera(regArch, regControl);
    printf("\n\t\tCantidad de Alumnos de la Facultad %s: %hd\n",
            regControl->grupoFacultad, regControl->totalAlumnosFacultad);
    regControl->totalAlumnosFacultad += regControl->totalAlumnosCarrera;
    regControl->totalAlumnosFacultad= 0;
    strcpy(regControl->grupoFacultad, regArch.facultad);
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

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

// Lee el registro actual del archivo cuyo puntero se recibe
// como parametro.
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    //Dejamos un espacio en la lectura de la facultad para que se ignore
    //el \n que quedo en el buffer luego de haber leido el nombre del alumno.
    fscanf(fd, " %[^,],%[^,],%hd,%ld,%[^\n]", r.facultad, r.carrera, &r.curso,
                                            &r.cedula, r.alumno);
    return r;
}
