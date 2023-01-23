#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTES
Z



// ESTRUCTURAS
    typedef struct {
        char facultad[SHORT_CHAR]; 
        char carrera[SHORT_CHAR]; 
        int curso; 
        int cedula; 
        char nombre[LONG_CHAR]; 
    } RegistroArchivo; 

    typedef struct {
        char grupoFacultad[SHORT_CHAR]; 
        char grupoCarrera[SHORT_CHAR]; 
        int grupoCurso; 

        int totalAlumnosCurso; 
        int cantidadAlumnosPorCarrera; 
        int cantidadCursosPorCarrera; 
        int totalAlumnosFacultad; 

    } RegistroControl;

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void corteFacultad(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    int calculoAnho(RegistroArchivo r); 
    RegistroArchivo leerRegistroArchivo(FILE *);
    void cabeceraCurso (int nroPeaje) ; 
    void corteCarrera(RegistroArchivo regArch, RegistroControl *regControl);  
    void corteCurso(RegistroArchivo regArch, RegistroControl *regControl) ; 

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

    primerRegistro(regArchivo, &regControl);
    cabeceraFacu(regArchivo.facultad);
    cabeceraCurso(regArchivo.curso);

    while (!feof(fd)) {
        
        if (strcmp (regArchivo.facultad, regControl.grupoFacultad) != 0) {
            corteFacultad(regArchivo, &regControl);
            cabeceraFacu(regArchivo.facultad);
            cabeceraCurso(regArchivo.curso);
        } else if (strcmp (regControl.grupoCarrera,regArchivo.carrera) != 0){
            corteCarrera(regArchivo, &regControl); 
        } else if (regControl.grupoCurso != regArchivo.curso){
            corteCurso(regArchivo, &regControl); 
            cabeceraCurso(regArchivo.curso);
        } 

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);

    }
    corteFacultad(regArchivo, &regControl);
}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // inicializamos los grupos 
    strcpy (regControl->grupoFacultad, regArch.facultad); 
    strcpy (regControl->grupoCarrera, regArch.carrera); 
    regControl->grupoCurso = regArch.curso; 

    // inicializamos contadores y totalizadores 
    regControl->totalAlumnosCurso = 0; 
    regControl->cantidadAlumnosPorCarrera = 0; 
    regControl->cantidadCursosPorCarrera = 0; 
    regControl->totalAlumnosFacultad = 0; 
    
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    regControl->totalAlumnosCurso ++; 
    regControl->cantidadAlumnosPorCarrera ++; 
    regControl->cantidadCursosPorCarrera ++; 
    regControl->totalAlumnosFacultad ++; 

    if (regControl->grupoCurso == regArch.curso)    {
        printf("\n %s \t %s \t %d \t %s ", regArch.facultad, regArch.carrera, regArch.curso, regArch.nombre); 
    }
}

// Procesamos los cortes
void corteCurso(RegistroArchivo regArch, RegistroControl *regControl) {
    printf("\n---------------------------------------------------------------------"); 
    printf("\nTotal de alumnos del curso %d: %d",regControl->grupoCurso, regControl->totalAlumnosCurso); 
    regControl->totalAlumnosCurso = 0; 
    regControl->grupoCurso = regArch.curso; 

}

void corteCarrera(RegistroArchivo regArch, RegistroControl *regControl) {
    corteCurso(regArch, regControl);
    float promedio = regControl->cantidadAlumnosPorCarrera / regControl->cantidadCursosPorCarrera; 
    printf("\nPromedio de alumnos por curso en la carrera %s: %d", regControl->grupoCarrera, promedio); 

    strcpy (regControl->grupoCarrera, regArch.carrera); 
    regControl->cantidadAlumnosPorCarrera = 0; 
    regControl->cantidadCursosPorCarrera = 0; 
}

void corteFacultad(RegistroArchivo regArch, RegistroControl *regControl){
    corteCarrera(regArch, regControl);
    printf("\n\nTotal de alumnos de la facultad %s: %d", regControl->grupoFacultad, regControl->totalAlumnosFacultad); 
    strcpy (regControl->grupoFacultad, regArch.facultad); 
    regControl->totalAlumnosFacultad = 0; 
    printf("\n---------------------------------------------------------------------"); 
}

// Funcion encargada de la apertura del archivo a procesar, en caso de falla, terminamos el programa.
FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("ERROR: No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

// Lee el registro actual del archivo 
RegistroArchivo leerRegistroArchivo(FILE *fd){

    RegistroArchivo r;
    fscanf(fd, " %[^,],%[^,],%d,%d,%[^\n]", r.facultad, r.carrera, &r.curso, &r.cedula, r.nombre); 
    // printf("\n Se obtuvo: %s,%s,%d,%d,%s", r.facultad, r.carrera, r.curso, r.cedula, r.nombre); 

    return r; 
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

void cabeceraCurso (int curso) {
    printf("\n\n ============== ALUMNOS DEL CURSO %d  ============== \n", curso);     
} 

void cabeceraFacu (char facultad[SHORT_CHAR]) {
    printf("\n\n\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n FACULTAD: %s ", facultad);     
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"); 
} 
