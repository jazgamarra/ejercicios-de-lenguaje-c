/* Ejercicio 3

Implemente la solución del ejercicio anterior, aumentando la cantidad de cortes y agregue al informe cuanto sigue:
1. Por puesto de peaje:
    3. El promedio mensual de recaudación.
    4. Los meses de mayor y menor recaudación.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //  para el calculo de mi mayor / menor 

// CONSTANTES
    #define ARCHIVO_DATOS "peajes.csv"
    #define MODO_APERTURA "r"
    #define CANT_CATEG 5
    #define CANT_MESES 12 

// ESTRUCTURAS
    typedef struct {
        int puestoPeaje; 
        int categoriaVehiculo; 
        struct f { 
            int mes; 
        } fecha; 
    } RegistroArchivo; 

    typedef struct {
        int grupoPuestoPeaje; 
        int grupoMes; 

        int totalAnho; 
        int vehicPorCategoria[CANT_CATEG]; 
        int preciosPorCategoria[CANT_CATEG]; 

        struct meses {
            int sumTotal; // sumatoria de los precios del mes q estoy leyendo
            int sumaPromPorPeaje; // se suma el totalMes en el corte por mes 
            int cant; // cuenta de cuantos meses distintos sumamos para el promedio ya que no podemos asumir que se cargaron registros para los 12 meses
        } mes; 

        struct recaudacion {
            int montoRecaudacion; 
            int mesRecaudacion; 
        } mayor, menor; 

    } RegistroControl;

// PROTOTIPOS 
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void cortePeaje(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    int calculoAnho(RegistroArchivo r); 
    RegistroArchivo leerRegistroArchivo(FILE *);
    void corteMes(RegistroArchivo regArch, RegistroControl *regControl);  
    void cabecera (int nroPeaje) ; 

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
    cabecera (regControl.grupoPuestoPeaje); 

    while (!feof(fd)) {
        
        if (regArchivo.puestoPeaje != regControl.grupoPuestoPeaje) {
            cortePeaje(regArchivo, &regControl);
            cabecera(regControl.grupoPuestoPeaje); 
        } else if (regControl.grupoMes != regArchivo.fecha.mes){
            corteMes(regArchivo, &regControl); 
        }

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);

    }
    cortePeaje(regArchivo, &regControl);
}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 
    regControl->grupoMes=regArch.fecha.mes; 

    regControl->totalAnho = 0; 

    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoria[i] = 0; 
    }

    regControl->preciosPorCategoria[0]=10000; 
    regControl->preciosPorCategoria[1]=20000; 
    regControl->preciosPorCategoria[2]=20000; 
    regControl->preciosPorCategoria[3]=30000; 
    regControl->preciosPorCategoria[4]=40000; 

    regControl->mes.sumTotal=0; 
    regControl->mes.cant=0; 
    regControl->mes.sumaPromPorPeaje=0;  

    regControl->mayor.mesRecaudacion = regArch.fecha.mes; 
    regControl->menor.mesRecaudacion = regArch.fecha.mes; 
    regControl->mayor.montoRecaudacion = 0; 
    regControl->menor.montoRecaudacion = INT_MAX; // es una constante q representa el mayor nro q puede ser int sin generar overflow. 


}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // calculamos segun el tipo de vehiuculo y el precio asignado.  
    int peajeCobrado = regControl->preciosPorCategoria[regArch.categoriaVehiculo]; 
    regControl->totalAnho += peajeCobrado; 

    // sumamos uno al vector de autos por categoria que pasaron 
        regControl->vehicPorCategoria[regArch.categoriaVehiculo] += 1; 

    // sumamos el monto del peajeCobrado a los totales
        regControl->mes.sumTotal += peajeCobrado;  


}

void corteMes(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->mes.sumaPromPorPeaje += regControl->mes.sumTotal; 
    regControl->mes.cant ++; 

    if (regControl->mayor.montoRecaudacion < regControl->mes.sumTotal) {
        regControl->mayor.mesRecaudacion = regControl->grupoMes; 
        regControl->mayor.montoRecaudacion = regControl->mes.sumTotal; 
    }
    if (regControl->menor.montoRecaudacion > regControl->mes.sumTotal) {
        regControl->menor.mesRecaudacion = regControl->grupoMes; 
        regControl->menor.montoRecaudacion = regControl->mes.sumTotal; 
    }

    char meses [12][10] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Set", "Oct", "Nov", "Dic" }; 
    printf("\n   %s->   %11d gs. ", meses[regControl->grupoMes], regControl->mes.sumTotal ); 

    regControl->grupoMes=regArch.fecha.mes; 
    regControl->mes.sumTotal = 0; 

}

// Procesa el corte del bloque anterior.
void cortePeaje(RegistroArchivo regArch, RegistroControl *regControl){
    corteMes(regArch, regControl);

    printf("\n-----------------------------"); 
    printf("\n=> Total del anho: Gs. %d ", regControl->totalAnho); 
    printf("\n=> Promedio Mensual:  Gs. %d ", regControl->mes.sumaPromPorPeaje / regControl->mes.cant); 
    printf("\n-----------------------------"); 

    char meses [12][10] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Set", "Oct", "Nov", "Dic" }; 
    printf("\n=> Mes de mayor rec.: Gs. %s ", meses[regControl->mayor.mesRecaudacion] ); 
    printf("\n=> Mes de menor rec.: Gs. %s ", meses[regControl->menor.mesRecaudacion]  ); 
    printf("\n-----------------------------"); 

    printf("\n=> VEHICULOS POR CATEGORIA <="); 
    printf("\n- - - - - - - - - - - - - - -  "); 
    printf("\n Categoria \t Cantidad "); 
    printf("\n-----------------------------"); 
    for (int i = 0; i<CANT_CATEG; i++){
        printf("\n%5d%16d", i+1, regControl->vehicPorCategoria[i]); 
    }
    printf("\n-----------------------------"); 
    printf("\n  "); 
 

    // volvemos a inicializar 
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 
    regControl->totalAnho = 0; 
    regControl->mes.cant = 0; 
    regControl->mes.sumaPromPorPeaje = 0; 
    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoria[i] = 0; 
    }
    regControl->mayor.mesRecaudacion = regArch.fecha.mes; 
    regControl->menor.mesRecaudacion = regArch.fecha.mes; 
    regControl->mayor.montoRecaudacion = 0; 
    regControl->menor.montoRecaudacion = INT_MAX; 
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
    fscanf(fd, "%d,%d,%*d,%d", &r.puestoPeaje, &r.fecha.mes, &r.categoriaVehiculo);
    r.categoriaVehiculo = r.categoriaVehiculo - 1; // mis vectores inician en cero
    r.fecha.mes = r.fecha.mes - 1; 
    return r;
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

void cabecera (int nroPeaje) {
    printf("\n  "); 
    printf("\n  "); 
    printf("\n- - - - - - - - - - - - - - -  "); 
    printf("\n==== PUESTO PEAJE NRO #%d ====",nroPeaje); 
    printf("\n- - - - - - - - - - - - - - -  "); 
    printf("\n= = > TOTAL MENSUAL  < = = "); 
    printf("\n- - - - - - - - - - - - - - -  "); 
    printf("\n  Mes \t\t Total "); 
    printf("\n-----------------------------"); 
    
}