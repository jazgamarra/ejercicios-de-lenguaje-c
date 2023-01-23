#include <stdio.h>
#include <stdlib.h>

#define NRO_MESES 12

// CONSTANTES
    #define ARCHIVO_DATOS "lluvia.csv"
    #define MODO_APERTURA "r"

// ESTRUCTURAS
    typedef struct {
        struct f {
            int dia, mes, anho; 
        } fecha; 
        float cantLluvia; 
    } RegistroArchivo; 

    typedef struct {
        float cantLLuviaMes[12]; 
        int diasLLuviaAbudante; 

        struct dml {
            int dia, mes, cantidad; 
        }diaMenosLLuvia; 

    } RegistroControl;

   

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void procesarCorte(RegistroArchivo, RegistroControl *);
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
    int anho, bandera = 0; 
    printf("\n INTRODUZCA EL ANHO: ");
    scanf("%d", &anho); 
    // valido q sea un anho valido !!
    while ((anho > 2020) || (anho < 2000)) {
        printf("\n El anho introducido es invalido. \n INTRODUZCA EL ANHO: ");
        scanf("%d", &anho); 
    }
 
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
    
    while (!feof(fd)) {
        
        if (regArchivo.fecha.anho == anho) {
            procesarRegistro(regArchivo, &regControl); 
            bandera = 1; 
        }
        regArchivo = leerRegistroArchivo(fd); 
    }
    if (bandera == 1)
        procesarCorte(regArchivo, &regControl);
    else 
        printf("\n---------------------------------\n No existen registros del anho %d \n---------------------------------", anho); 

}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    for (int i=0; i<NRO_MESES; i++ ) {
        regControl->cantLLuviaMes[i]=0; 
    } 
    regControl->diasLLuviaAbudante=0; 
    regControl->diaMenosLLuvia.cantidad=regArch.cantLluvia; 


}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->cantLLuviaMes[regArch.fecha.mes] += regArch.cantLluvia; 
    if (regArch.cantLluvia > 150) {
        regControl->diasLLuviaAbudante ++; 
    }
    if (regControl->diaMenosLLuvia.cantidad > regArch.cantLluvia) {
        regControl->diaMenosLLuvia.dia = regArch.fecha.dia; 
        regControl->diaMenosLLuvia.mes = regArch.fecha.mes; 
    }
}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *regControl){
    procesarRegistro(regArch, regControl); 

    char meses [12][10] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Set", "Oct", "Nov", "Dic" }; 


    printf("\n-----------------------------------"); 
    printf("\n    CANTIDAD DE LLUVIA POR MES "); 
    printf("\n------------------------------------"); 
    // LLUVIA POR MES 
    for (int i=0; i<NRO_MESES; i++ ) {
        if (regControl->cantLLuviaMes[i] != 0){
            printf("\n Mes: %s  ->  Cantidad: %.2f mm", meses[i], regControl->cantLLuviaMes[i]); 
        }
    } 
    // PROMEDIO ANUAL 
    int sumatoria = 0, indice = 0; 
    for (int i=0; i<NRO_MESES; i++ ) {
        if (regControl->cantLLuviaMes[i] != 0){
            sumatoria += regControl->cantLLuviaMes[i]; 
            indice ++; 
        }
    } 
    printf("\n------------------------------------"); 
    printf("\n Promedio: %.2f", (float) sumatoria / indice); 
    if (regControl->diasLLuviaAbudante != 0){
        printf("\n Dias de LLuvia Abundante: %d.", regControl->diasLLuviaAbudante); 
    }
    printf("\n Dia de menor lluvia: %d/%s", regControl->diaMenosLLuvia.dia,  meses[regControl->diaMenosLLuvia.mes]); 
    printf("\n------------------------------------"); 

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
// En el archivo se tiene en este orden: nro. puesto peaje, mes, día, categoría vehículo
RegistroArchivo leerRegistroArchivo(FILE *fd){
    RegistroArchivo r;
    fscanf(fd, "%d,%d,%d,%f", &r.fecha.anho, &r.fecha.mes, &r.fecha.dia, &r.cantLluvia);
    // printf( "\n%d,%d,%d,%f", r.fecha.anho, r.fecha.mes, r.fecha.dia, r.cantLluvia);

    r.fecha.mes = r.fecha.mes - 1;  // le restamos uno pq comienza en 0 mi vector 
    return r;
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

