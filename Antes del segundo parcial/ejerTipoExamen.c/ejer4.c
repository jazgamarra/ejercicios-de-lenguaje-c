/* Ejercicio 4
Dada la solución del ejercicio anterior, agregue al informe cuanto sigue:
5. Por mes (se debe imprimir el nombre del mes):
    2. El promedio diario de recaudación.
    3. Las fechas de mesMayor y mesMenor recaudación.
6. Por día:
    1. Un ranking descendente de la cantidad de vehículos de cada categoría que pasaron.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //  para el calculo de mi mesMayorRec / mesMenorRec 

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
            int mes, dia; 
        } fecha; 
    } RegistroArchivo; 

    typedef struct {
        int grupoPuestoPeaje; 
        int grupoMes; 
        int grupoDia; 

        int totalAnho; 
        int vehicPorCategoriaPeaje[CANT_CATEG]; 
        int preciosPorCategoria[CANT_CATEG]; 

        struct meses {
            int sumTotal; // sumatoria de los precios del mes q estoy leyendo
            int sumaPromPorPeaje; // se suma el totalMes en el corte por mes 
            int cant; // cuenta de cuantos meses distintos sumamos para el promedio ya que no podemos asumir que se cargaron registros para los 12 meses
        } mes; 

        struct recaudacion {
            int monto; 
            int fecha; 
        } mesMayorRec, mesMenorRec, diaMayorRec, diaMenorRec; 

        struct dias { 
            int sumTotal; // para el promedio diario de recaudacion 
            int cant; 
        } dia; 

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
    void glosario (); 
    void corteDia(RegistroArchivo regArch, RegistroControl *regControl);  

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
        } else if (regControl.grupoDia != regArchivo.fecha.dia){
            corteDia(regArchivo, &regControl); 
        }

        procesarRegistro(regArchivo, &regControl);
        regArchivo = leerRegistroArchivo(fd);

    }
    cortePeaje(regArchivo, &regControl);

     glosario (); 

}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 
    regControl->grupoMes=regArch.fecha.mes; 

    regControl->totalAnho = 0; 

    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoriaPeaje[i] = 0; 
    }

    regControl->preciosPorCategoria[0]=10000; 
    regControl->preciosPorCategoria[1]=20000; 
    regControl->preciosPorCategoria[2]=20000; 
    regControl->preciosPorCategoria[3]=30000; 
    regControl->preciosPorCategoria[4]=40000; 

    regControl->mes.sumTotal=0; 
    regControl->mes.cant=0; 
    regControl->mes.sumaPromPorPeaje=0;  

    regControl->mesMayorRec.fecha = regArch.fecha.mes; 
    regControl->mesMenorRec.fecha = regArch.fecha.mes; 
    regControl->mesMayorRec.monto = 0; 
    regControl->mesMenorRec.monto = INT_MAX; // es una constante q representa el mesMayorRec nro q puede ser int sin generar overflow. 

    regControl->diaMayorRec.fecha = regArch.fecha.mes; 
    regControl->diaMenorRec.fecha = regArch.fecha.mes; 
    regControl->diaMayorRec.monto = 0; 
    regControl->diaMenorRec.monto = INT_MAX; 
    regControl->dia.cant = 0; 
}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {

    // calculamos segun el tipo de vehiuculo y el precio asignado.  
    int peajeCobrado = regControl->preciosPorCategoria[regArch.categoriaVehiculo]; 
    regControl->totalAnho += peajeCobrado; 

    // sumamos uno al vector de autos por categoria que pasaron 
        regControl->vehicPorCategoriaPeaje[regArch.categoriaVehiculo] += 1; 

    // sumamos el monto del peajeCobrado a los totales mensuales
        regControl->mes.sumTotal += peajeCobrado;  

    // sumo el monto del peaje cobrado a mi total por dia 
        regControl->dia.sumTotal += peajeCobrado;  
    
}

void corteDia(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->dia.cant++; 

    if (regControl->diaMayorRec.monto < regControl->dia.sumTotal) {
        regControl->diaMayorRec.fecha = regControl->grupoDia; 
        regControl->diaMayorRec.monto = regControl->dia.sumTotal; 
    }
    if (regControl->diaMenorRec.monto > regControl->dia.sumTotal) {
        regControl->diaMenorRec.fecha = regControl->grupoDia; 
        regControl->diaMenorRec.monto = regControl->dia.sumTotal; 
    }

    regControl->grupoDia=regArch.fecha.dia; 
    regControl->dia.sumTotal = 0; 

}

void corteMes(RegistroArchivo regArch, RegistroControl *regControl) {
    corteDia(regArch, regControl); 

    regControl->mes.sumaPromPorPeaje += regControl->mes.sumTotal; 
    regControl->mes.cant ++; 

    if (regControl->mesMayorRec.monto < regControl->mes.sumTotal) {
        regControl->mesMayorRec.fecha = regControl->grupoMes; 
        regControl->mesMayorRec.monto = regControl->mes.sumTotal; 
    }
    if (regControl->mesMenorRec.monto > regControl->mes.sumTotal) {
        regControl->mesMenorRec.fecha = regControl->grupoMes; 
        regControl->mesMenorRec.monto = regControl->mes.sumTotal; 
    }

    char meses [12][10] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Set", "Oct", "Nov", "Dic" }; 
    printf("\n %s->   %4d %9d %10d %11d %11d ", meses[regControl->grupoMes], regControl->mes.sumTotal, (regControl->mes.sumTotal / regControl->dia.cant),  regControl->dia.cant, regControl->diaMayorRec.fecha, regControl->diaMenorRec.fecha); 
 

    regControl->grupoMes=regArch.fecha.mes; 
    regControl->mes.sumTotal = 0; 
    regControl->diaMayorRec.fecha = regArch.fecha.mes; 
    regControl->diaMenorRec.fecha = regArch.fecha.mes; 
    regControl->diaMayorRec.monto = 0; 
    regControl->diaMenorRec.monto = INT_MAX; 
    regControl->dia.cant = 0; 
  

}

// Procesa el corte del bloque anterior.
void cortePeaje(RegistroArchivo regArch, RegistroControl *regControl){
    corteMes(regArch, regControl);

    printf("\n--------------------------------------------------------------------"); 
    printf("\n=> Total del anho: Gs. %d ", regControl->totalAnho); 
    printf("\n=> Promedio Mensual:  Gs. %d ", regControl->mes.sumaPromPorPeaje / regControl->mes.cant); 

    char meses [12][10] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Set", "Oct", "Nov", "Dic" }; 
    printf("\n=> Mes de mayor rec.: Gs. %s ", meses[regControl->mesMayorRec.fecha] ); 
    printf("\n=> Mes de menor rec.: Gs. %s ", meses[regControl->mesMenorRec.fecha]  ); 
    printf("\n--------------------------------------------------------------------"); 

    printf("\n\t\t=> VEHICULOS POR CATEGORIA <="); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "); 
    printf("\n \t\tCategoria \t Cantidad "); 
    printf("\n---------------------------------------------------------------------"); 
    for (int i = 0; i<CANT_CATEG; i++){
        printf("\n\t\t%5d%16d", i+1, regControl->vehicPorCategoriaPeaje[i]); 
    }
    printf("\n---------------------------------------------------------------------"); 
    printf("\n  "); 
 

    // volvemos a inicializar 
    regControl->grupoPuestoPeaje = regArch.puestoPeaje; 
    regControl->totalAnho = 0; 
    regControl->mes.cant = 0; 
    regControl->mes.sumaPromPorPeaje = 0; 
    for (int i = 0; i<CANT_CATEG; i++){
        regControl->vehicPorCategoriaPeaje[i] = 0; 
    }
    regControl->mesMayorRec.fecha = regArch.fecha.mes; 
    regControl->mesMenorRec.fecha = regArch.fecha.mes; 
    regControl->mesMayorRec.monto = 0; 
    regControl->mesMenorRec.monto = INT_MAX; 
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
    fscanf(fd, "%d,%d,%d,%d", &r.puestoPeaje, &r.fecha.mes, &r.fecha.dia, &r.categoriaVehiculo);
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
    printf("\n\n  "); 
    printf("\n "); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n\t\t     PUESTO PEAJE NRO #%d      ",nroPeaje); 
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"); 
    printf("\n\t\t= = = > TOTAL MENSUAL  < = = = "); 
    printf("\n- - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - -"); 
    printf("\n  Mes\t Total\t   Prom.     Cant. Dias\t  Mayor Rec.   Menor Rec. "); 
    printf("\n----------------------------------------------------------------------"); 
    
}

void glosario (){ 

    printf("\n\n----------------------------------------------------------------------"); 
    printf("\n EN EL REGISTRO MENSUAL .....  "); 
    printf("\n Total: Sumatoria total de lo recaudado en ese mes "); 
    printf("\n Prom: Promedio de lo recaudado en ese mes "); 
    printf("\n Cant. Dias: La cantidad de dias de los que se tiene registro en ese mes"); 
    printf("\n Mayor y menor rec.: Dia de mayor y menor recaudacion en el mes correspondiente  "); 

    printf("\n----------------------------------------------------------------------"); 

        



} 
