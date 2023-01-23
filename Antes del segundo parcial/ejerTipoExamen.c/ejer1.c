/* Ejercicio 1 

El archivo está ordenado por nro puesto peaje, mes y día donde el costo de
peaje por categoría de vehículo se puede observar en la siguiente figura:
Se desea obtener el siguiente informe:
1. Por puesto de peaje:
    1. El monto total del peaje cobrado.
    2. La cantidad de vehículos de cada categoría que pasaron.
2. El total general recaudado del año. 
nro. puesto peaje, mes, día, categorí vehículo 
*/ 

#include <stdio.h>
#include <stdlib.h>

// CONSTANTES
    #define ARCHIVO_DATOS "peajes.csv"
    #define MODO_APERTURA "r"
    #define CANT_CATEG 5

// ESTRUCTURAS
    typedef struct {
        int puestoPeaje; 
        int categoriaVehiculo; 
    } RegistroArchivo; 

    typedef struct {
        int grupoPuestoPeaje; 
        int totalAnho; 
        int vehicPorCategoria[CANT_CATEG]; 
        int preciosPorCategoria[CANT_CATEG]; 
    } RegistroControl;

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void procesarCorte(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    int calculoAnho(RegistroArchivo r); 
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
        
        if (regArchivo.puestoPeaje != regControl.grupoPuestoPeaje) {
            procesarCorte(regArchivo, &regControl);
        }

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);

    }
    procesarCorte(regArchivo, &regControl);
}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 

    regControl->totalAnho = 0; 

    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoria[i] = 0; 
    }

    regControl->preciosPorCategoria[0]=10000; 
    regControl->preciosPorCategoria[1]=20000; 
    regControl->preciosPorCategoria[2]=20000; 
    regControl->preciosPorCategoria[3]=30000; 
    regControl->preciosPorCategoria[4]=40000; 
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // calculamos segun el tipo de vehiuculo y el precio asignado.  
    int peajeCobrado = regControl->preciosPorCategoria[regArch.categoriaVehiculo]; 
    regControl->totalAnho += peajeCobrado; 

    // sumamos uno al vector de autos por categoria que pasaron 
        regControl->vehicPorCategoria[regArch.categoriaVehiculo] += 1; 

}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *regControl){
    
    printf("\n-----------------------------"); 
    printf("\n==== PUESTO PEAJE NRO #%d ====", regControl->grupoPuestoPeaje); 
    printf("\n-----------------------------"); 
    printf("\nCategoria \t Cantidad "); 
    for (int i = 0; i<CANT_CATEG; i++){
        printf("\n%5d%16d", i+1, regControl->vehicPorCategoria[i]); 
    }
    printf("\n-----------------------------"); 
    printf("\n==> Monto total: Gs. %d <== ", regControl->totalAnho); 
    printf("\n\n"); 

    // volvemos a inicializar 
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 
     regControl->totalAnho = 0; 

    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoria[i] = 0; 
    }

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
    fscanf(fd, "%d,%*d,%*d,%d", &r.puestoPeaje, &r.categoriaVehiculo);
    r.categoriaVehiculo = r.categoriaVehiculo - 1; // mis vectores inician en cero
    return r;
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

