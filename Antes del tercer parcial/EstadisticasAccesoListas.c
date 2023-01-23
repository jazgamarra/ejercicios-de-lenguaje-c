/* 
Impresion del acceso por dias de la semana - Con listas ligadas. 
18/05/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// CONSTANTES 
#define ARCHIVO "EstadisticasAcceso.csv"
#define MODO_APERTURA "r" 
#define ANHO 2008
#define MESES 12
#define DIAS_SEM 7 
#define SIN_REGISTRO "nulo"

// ESTRUCTURAS
    typedef struct reg {
        int codCliente; 
        struct f {
            int dia, mes, diaDeLaSemana; 
        } fecha; 
        char ip[15]; 
        int bytes; 

    } RegistroArchivo;

    typedef struct nodo {
        int codCliente; 
        struct fe {
            int dia, mes, diaDeLaSemana; 
        } fecha; 
        char ip[15]; 
        int bytes;  
        struct nodo * siguiente;    
    } NODO; 


// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]); 
    void cerrarArchivo(FILE *);
    void procesarArchivo(FILE *);
    RegistroArchivo leerRegistroArchivo(FILE *);
    int diaDeLaSemana (int d, int m); 
    NODO* CrearNodo (RegistroArchivo regArch); 
    int InsertarInicio (NODO **cabeza, RegistroArchivo regArch);
    int InsertarFinal (NODO **lista, RegistroArchivo regArch); 
    void ImprimirLista (NODO *lista); 
    void errorMemoria(); 

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

    NODO *lista = NULL; 
    
    // Declaramos las variables estructuradas 
    RegistroArchivo regArchivo;

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO);
       return;
    }
    
    // Recorremos el archivo
    regArchivo = leerRegistroArchivo(fd);
    InsertarInicio(&lista, regArchivo); 
    
    while (!feof(fd)) {
        regArchivo = leerRegistroArchivo(fd);
        InsertarFinal(&lista, regArchivo); 
    }
    ImprimirLista(lista); 
}


/* Lee el registro actual del archivo */
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    fscanf(fd, " %d,%d/%d,%*d:%*d,%[^,],%d", &r.codCliente, &r.fecha.dia, &r.fecha.mes, r.ip, &r.bytes);
    r.fecha.diaDeLaSemana = diaDeLaSemana(r.fecha.dia, r.fecha.mes); 
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

// CREAR NODO 
NODO* CrearNodo (RegistroArchivo regArch) {
	NODO *nuevo = NULL; 
	nuevo = (NODO *) malloc (sizeof(NODO)); 
	
	if (nuevo != NULL ) { // con eso comprobamos que se haya podido reservar el espacio 
		nuevo->codCliente = regArch.codCliente; 
		nuevo->fecha.dia = regArch.fecha.dia; 
		nuevo->fecha.mes = regArch.fecha.mes; 
		nuevo->fecha.diaDeLaSemana = regArch.fecha.diaDeLaSemana; 
        strcpy(nuevo->ip, regArch.ip); 
        nuevo->bytes = regArch.bytes; 

		nuevo->siguiente = NULL; 

	} else {
        errorMemoria(); 
    }

	return nuevo; 
}

// INSERTAR AL FINAL 
int InsertarFinal (NODO **lista, RegistroArchivo regArch) {
	NODO *nuevo = NULL, *aux = *lista; 
	nuevo = CrearNodo (regArch); 
	
	if (nuevo != NULL ) {	
		// recorremos la lista ligada buscando el ultimo elemento; el que tiene .siguiente en NULL 
		while (aux->siguiente != NULL ) {
			aux = aux->siguiente;  
		} 
		aux->siguiente = nuevo; 
	
	}else {
        errorMemoria(); 
    }

}

void ImprimirLista (NODO *r) {
    char dias[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" }; 

    printf("\nCliente\t    IP \t\t     Bytes  \t Fecha  "); 
	for(NODO *aux = r; aux->siguiente != NULL; aux=aux->siguiente) {
        printf("\n %2d \t%s \t %10d \t %s, %d/%d ", aux->codCliente,  aux->ip, aux->bytes, dias[aux->fecha.diaDeLaSemana], aux->fecha.dia, aux->fecha.mes); 

    }
}

void errorMemoria() {
    printf("Error en la asign. dinamica de la memoria"); 
    exit(-1); 
}

int InsertarInicio (NODO **cabeza, RegistroArchivo regArch) {

    NODO *nuevo = NULL; 
    nuevo = CrearNodo (regArch); 

    if (nuevo != NULL ) {	
        nuevo->siguiente = NULL; 
        *cabeza = nuevo; 
        return 1; 
    }
    return 0; 
}