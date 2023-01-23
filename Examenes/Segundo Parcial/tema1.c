#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MESES 13
#define ARCHIVO_DATOS "lluvias.csv"
#define MODO_APERTURA "r"

    typedef struct {
        struct Fecha {
            int dia;
            int mes;
            int anho; 
        } fecha; 
        float cantidad; 
    } RegistroArchivo; 

    typedef struct {

        int anhoUsuario; 

        struct DiaMenosLLuvia { // guardo en una estructura todos los datos relativos a el dia de menos lluvia 
            int dia;
            int mes; 
            float cantidad; 
        }menosLluvia; 

        float acumCantLLuvia[N_MESES];  
        // Es un acumulador de las lluvias que se leyeron por mes. Elegi un vector y no un corte por mes porque los meses estan ordenados por region, no estan todos juntos.
        // Ademas, sabemos que un año solo tiene 12 meses. Mi vector es de 13 porque cargare cada mes en el numero que le corresponde ignorando el cero. 

        int contLluviaAbundante; // Es un contador de los dias de lluvia que superaron los 150mm 

        int sumaPromedio; 
        int cantidadLluvias; 

    } RegistroControl;

    

    // PROTOTIPADO
    FILE *abrirArchivo(char[], char[]);
    void cerrarArchivo(FILE *);
    void primerRegistro(RegistroArchivo, RegistroControl *);
    void procesarRegistro(RegistroArchivo, RegistroControl *);
    void procesarCorte(RegistroArchivo, RegistroControl *);
    void procesarArchivo(FILE *);
    RegistroArchivo leerRegistroArchivo(FILE *); 
    char *obtenerNombreMes(short);

int main(void) {

    // Abrimos el archivo especificado en ARCHIVO_DATOS.
    FILE *fd = abrirArchivo(ARCHIVO_DATOS, MODO_APERTURA);

    // Procesamos el archivo por corte de control.
    procesarArchivo(fd);

    // Cerramos el archivo de datos.
    cerrarArchivo(fd);

    return 0;

}

void procesarArchivo(FILE *fd) {
    
    // Declaramos las variables estructuradas para datos y control.
    RegistroArchivo regArchivo;
    RegistroControl regControl;

    // Leemos el año 
    printf("\n Introduzca el anho del que desea ver los registros: ");
    scanf("%d", &regControl.anhoUsuario); 
    
    while ((regControl.anhoUsuario > 2020) || (regControl.anhoUsuario < 2000)) { // Valido que el año leido este en el rango 2000 - 2020 
        printf("\n El anho introducido es invalido. Favor introduzca un anho entre 2000 y 2020: ");
        scanf("%d", &regControl.anhoUsuario); 
    }

    int centinela = 0; 
    // Leemos el primer registro del archivo.
    regArchivo = leerRegistroArchivo(fd);

    // Verificamos que el archivo no este vacio.
    if (feof(fd)) {
       printf("El archivo %s esta vacio.\n", ARCHIVO_DATOS);
       return;
    }

    primerRegistro(regArchivo, &regControl);
    
    while (!feof(fd) && centinela == 0) {
        
        if (regArchivo.fecha.anho == regControl.anhoUsuario) {
            procesarRegistro(regArchivo, &regControl); 
            centinela = 1; 
        }
        regArchivo = leerRegistroArchivo(fd); 
    }

    // valida si se proceso el registro alguna vez 
    if (centinela == 1){
        procesarCorte(regArchivo, &regControl); // se imprimen los resultados
    } else { // si no se proceso significa q no existe 
        printf("\n No existen registros del anho %d \n", regControl.anhoUsuario); 
    }

}

// Inicializa los valores ante el primer registro leido 
void primerRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    for (int i=0; i<N_MESES; i++ ) { // aunque ignore la posicion cero la inicializare como 0 para no generar errores inesperados xd 
        regControl->acumCantLLuvia[i]=0; 
    } 
    // promedio 
    regControl->cantidadLluvias = 0;
    regControl->sumaPromedio = 0; 

    // dia menor de lluvia: inicializo con los valores del primer registro para comparar desde ahi  
    regControl->contLluviaAbundante=0; 
    regControl->menosLluvia.cantidad=regArch.cantidad; 
    regControl->menosLluvia.dia = regArch.fecha.dia; 
    regControl->menosLluvia.mes = regArch.fecha.mes; 


}

// Procesa el registro actual.
void procesarRegistro(RegistroArchivo regArch, RegistroControl *regControl) {
    regControl->acumCantLLuvia[regArch.fecha.mes] += regArch.cantidad; 
    regControl->sumaPromedio += regArch.cantidad; 
    regControl->cantidadLluvias += 1; 

    if (regArch.cantidad > 150) {  // si es un dia de lluvia abundante 
        regControl->contLluviaAbundante ++; 
    }
     if (( regControl->menosLluvia.cantidad > regArch.cantidad) ) { // si la cantidad de lluvia que tengo guardada es mayor a la que lei ahora... 
        
        printf("%f > %f - ", regControl->menosLluvia.cantidad, regArch.cantidad); 
        
        regControl->menosLluvia.cantidad = regArch.cantidad;    
        regControl->menosLluvia.dia = regArch.fecha.dia;    
        regControl->menosLluvia.mes = regArch.fecha.mes; 
    }

}

// Procesa el corte del bloque anterior.
void procesarCorte(RegistroArchivo regArch, RegistroControl *regControl){

    printf("\n LLuvia por mes:     "); 
    printf("\n------------------------------------"); 
    printf("\n MES\t\t   CANTIDAD "); 
    for (int i=1; i<N_MESES; i++ ) {
        if (regControl->acumCantLLuvia[i] != 0){ // imprime solo si es != 0 
            printf("\n %s  \t   %.2f mm",  obtenerNombreMes(i), regControl->acumCantLLuvia[i]);  
        }
    } 
    printf("\n"); 
    printf("\n Promedio: %.1f", (float) regControl->sumaPromedio / regControl->cantidadLluvias); 
    printf("\n Dia de menor lluvia: %d de %s", regControl->menosLluvia.dia, obtenerNombreMes(regControl->menosLluvia.mes)); 
     if (regControl->contLluviaAbundante != 0){ // imprime solo si hay dias de lluvia abundante 
        printf("\n Atencion: Hubo %d dias de LLuvia Abundante.", regControl->contLluviaAbundante); 
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
    fscanf(fd, "%*[^,],%d,%d,%d,%f,%*s", &r.fecha.anho, &r.fecha.mes, &r.fecha.dia, &r.cantidad);
    // printf( "\n%d,%d,%d,%f", r.fecha.anho, r.fecha.mes, r.fecha.dia, r.cantidad);

    return r;
}

// Cierra el archivo cuyo descriptor se recibe como parametro.
void cerrarArchivo(FILE *fd) {
    if (fd != NULL)
        fclose(fd);
}

char *obtenerNombreMes(short nroMes){
   // Creamos nuestra lista de nombres de meses con tamanho indeterminado.
   char meses[][N_MESES] = {"", "Enero", "Febrero", "Marzo", "Abril",
                               "Mayo     ", "Junio", "Julio", "Agosto", "Setiembre",
                               "Octubre", "Noviembre", "Diciembre"};
   // Creamos una copia con el nombre del mes en el monticulo.
   char *nombreMes = malloc(strlen(meses[nroMes]));
   strcpy(nombreMes, meses[nroMes]);
   // Retornamos el nombre del mes creado en el monticulo.
   return nombreMes;
}
