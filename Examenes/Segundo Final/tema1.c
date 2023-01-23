/* Segundo final - Tema 1 
Jazmin Gamarra
29/06/2022
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> // para que el random genere numeros distintos al probar varias veces 

// Constantes. 
#define CANT_TAREAS 5 
#define CANT_CLASES 10
#define CANT_CLASES_TOTAL 20
#define TAM_CHAR 50

#define TEORICAS 't'
#define PRACTICAS 'p'

#define AUSENCIA 0 
#define PAR 0
#define IMPAR 1 
#define FALSO 0 
#define VERDADERO 1 
#define SECUENCIA_NECESARIA 2 
#define NULO 0 

// Estructuras
typedef char * String; // Para facilitar las cadenas y vectores dinamicos xd
typedef int * Array; 

typedef struct {
    int cedula; 
    String nombre;
    String apellido; 
    String materia; 
    Array asistencias; 
    Array notasTareas; 
} TAlumno;

// Prototipos. 
TAlumno * inicializarAlumno(TAlumno * alumno); 
void verificarErrorMemoria( void * puntero ); 
TAlumno * crearAlumno(TAlumno * alumno, int cedula, char nombre[TAM_CHAR], char apellido[TAM_CHAR], char materia[TAM_CHAR]); 
void imprimirAlumno (TAlumno * alumno); 
void destruirAlumno (TAlumno * alumno); 
int obtenerPromedioAsistencia(TAlumno * alumno, char tipoDeClase, int sumatoria, int i, int parImpar); 
int tieneDerechoExamen (float promedioTeoricas, float promedioPracticas); 
int obtenerAusenciasContiguas(TAlumno * alumno, char tipoDeClase, int ausenciasContiguas, int secuencia, int i, int parImpar); 

// Función Principal. 
int main (){ 

    TAlumno * alumno = NULL; 

    //  Se llama a la subrutina crearAlumno 
    alumno = crearAlumno(alumno, 5271520, "Jazmin", "Gamarra", "Algoritmica II"); 

    // Subrutina de impresion
    imprimirAlumno(alumno); 

    // Se calcula el promedio de asistencia 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    float promedioTeoricas = (float)obtenerPromedioAsistencia(alumno, TEORICAS, NULO, NULO, PAR) / CANT_CLASES;     
    float promedioPracticas = (float)obtenerPromedioAsistencia(alumno, PRACTICAS, NULO, NULO, IMPAR) / CANT_CLASES; 

    // Se imprime el promedio de asistencias 
    printf("\nEl promedio de asistencia de las clases teoricas es %0.f %%", promedioTeoricas*100); 
    printf("\nEl promedio de asistencia de las clases practicas es %0.f %%", promedioPracticas*100); 

    // Obtener derecho a examen 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    if (tieneDerechoExamen(promedioTeoricas, promedioPracticas) == VERDADERO) {
        printf("\nEl alumno tiene derecho a examen"); 
    } else {
        printf("\nEl alumno no posee derecho a examen");
    }

    // Obtener asistencias contiguas 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\nLa cantidad de ausencias contiguas en las clases practicas es: %d", obtenerAusenciasContiguas(alumno, PRACTICAS, NULO, NULO, NULO, IMPAR)); 
    printf("\nLa cantidad de ausencias contiguas en las clases teoricas es: %d", obtenerAusenciasContiguas(alumno, TEORICAS, NULO, NULO, NULO, PAR)); 

    // Se libera el espacio en memoria ocupado por la estructuras 
    destruirAlumno(alumno); 
}

// Inicializar alumno: inicializo las estructuras dinamicas 
TAlumno * inicializarAlumno(TAlumno * alumno){

    // Se reserva espacio para las cadenas 
        alumno->nombre = malloc(sizeof(TAM_CHAR*sizeof(char))); 
        verificarErrorMemoria(alumno->nombre); 

        alumno->apellido = malloc(sizeof(TAM_CHAR*sizeof(char))); 
        verificarErrorMemoria(alumno->apellido); 

        alumno->materia = malloc(sizeof(TAM_CHAR*sizeof(char))); 
        verificarErrorMemoria(alumno->materia); 

    // Se reserva espacio para los vectores
        alumno->asistencias = malloc(sizeof(int)*CANT_CLASES_TOTAL); 
        verificarErrorMemoria(alumno->asistencias); 

        alumno->notasTareas = malloc(sizeof(int)*CANT_TAREAS); 
        verificarErrorMemoria(alumno->notasTareas); 

    return alumno; 
}

// Crear Alumno. 
TAlumno * crearAlumno(TAlumno * alumno, int cedula, char nombre[TAM_CHAR], char apellido[TAM_CHAR], char materia[TAM_CHAR]) {

    // Reservamos el espacio en la memoria 
    alumno = malloc(sizeof(TAlumno)); 
    verificarErrorMemoria(alumno); 

    // Inicializamos las estructuras dinamicas dentro de alumno
    alumno = inicializarAlumno(alumno); 

    // Cargamos los datos recibidos como parámetros 
    alumno->cedula = cedula; 
    strcpy(alumno->nombre, nombre); 
    strcpy(alumno->apellido, apellido); 
    strcpy(alumno->materia, materia); 

    // Voy a generar las ausencias y notas de tareas con random para no recibir mil parámetros (ya que son 20 registros de ausencia/presencia)
    srand (time(NULL)); // Para que genere distintos numeros al probar distintas veces 
    
    for (int i = 0; i<CANT_TAREAS; i++) {
        *(alumno->notasTareas+i) = ((rand() % 10) * 10) + 10; 
    }
    for (int i = 0; i<CANT_CLASES_TOTAL; i++) {
        *(alumno->asistencias+i) = rand() % 2; 
    }
    
    return alumno; 
}

// Imprimir alumno.
void imprimirAlumno (TAlumno * alumno) {
    printf("\n- - - - - - - - - - - - - - - - - - - "); 
    printf("\nCedula: %d", alumno->cedula);
    printf("\nNombre: %s", alumno->nombre);
    printf("\nApellido: %s", alumno->apellido);
    printf("\nMateria: %s", alumno->materia);
    printf("\n- - - - - - - - - - - - - - - - - - - "); 
    printf("\nNOTAS DE LAS TAREAS "); 
    printf("\n- - - - - - - - - - - - - - - - - - - \n "); 
    for (int i = 0; i<CANT_TAREAS; i++) {
        printf("%6d", *(alumno->notasTareas+i)); 
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\nAUSENCIAS ");
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"); 
    for (int i = 0; i<CANT_CLASES_TOTAL; i++) {
       if (i%2 == PAR){
            printf("%4c", 't'); 
       } else {
            printf("%4c", 'p'); 
       }
    }
    printf("\n"); 
    for (int i = 0; i<CANT_CLASES_TOTAL; i++) {
        printf("%4d", *(alumno->asistencias+i)); 
    }
}

// Obtener ausencias contiguas.
int obtenerAusenciasContiguas(TAlumno * alumno, char tipoDeClase, int ausenciasContiguas, int secuencia, int i, int parImpar) {
if (i == CANT_CLASES_TOTAL) { 
        // Agrego esta comparacion porque si se rompe una secuencia en el ultimo elemento queda colgada 
        if (secuencia >= SECUENCIA_NECESARIA) {
            ausenciasContiguas++; 
        } 
        return ausenciasContiguas; 
    } else {
   
        // Dependiendo si la posicion es par o impar se suma o no 
        if (i%2 == parImpar) {
            if ( *(alumno->asistencias+i) == AUSENCIA) {
                secuencia ++; 
            } else {
                // Si se rompe una secuencia mayor a dos 
                if (secuencia >= SECUENCIA_NECESARIA) {
                    ausenciasContiguas++; 
                } 
                secuencia = NULO; 
            }
        }
        i++; 
        obtenerAusenciasContiguas(alumno, tipoDeClase, ausenciasContiguas, secuencia, i, parImpar); 
    } 
}

// Obtener promedio de ausencias. 
int obtenerPromedioAsistencia(TAlumno * alumno, char tipoDeClase, int sumatoria, int i, int parImpar) {
    if (i == CANT_CLASES_TOTAL) { 
        return sumatoria; 
    } else {

        // Sumo dependiendo de si corresponde o no sumar 
        if (i%2 == parImpar) {
            sumatoria += *(alumno->asistencias+i); 
            // Sumo directamente el contenido del vector porque si no se asistió 
            // se tiene "cero" y eso no va a afectar al resultado final
        }
        i++; 
        obtenerPromedioAsistencia(alumno, tipoDeClase, sumatoria, i, parImpar); 
    } 
} 

// Obtener derecho a examen 
int tieneDerechoExamen (float promedioTeoricas, float promedioPracticas){
    int temporal = FALSO;
    if ((promedioPracticas >= 0.8) && (promedioTeoricas >= 0.6)){
        temporal = VERDADERO; 
    } else {
        temporal = FALSO;
    }
    return temporal; 
}

// Destruir Alumno.
void destruirAlumno (TAlumno * alumno){
    if (alumno != NULL) {
        free(alumno); 
        printf("\n\n+ + + + + + + + + + + + +"); 
        printf("\nSe libero la memoria.  "); 
        printf("\n+ + + + + + + + + + + + +"); 
    }
}

// Verificar si el puntero vuelve nulo y cierra el programa 
void verificarErrorMemoria( void * puntero ){
    if (puntero == NULL) {
        printf("\nError en la asignación de memoria =("); 
        exit(-1); 
    }
}