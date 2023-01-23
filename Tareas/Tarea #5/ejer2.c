/* 
Informe de dominios por usuario por mes 
Jazmin Gamarra, Manu Baez y Silvia Candia
12/05/2022*/

#include <stdio.h>
#include <stdlib.h> // registros 
#include <string.h> // strcmp

// CONSTANTES 
    #define ARCHIVO "archivosCSV/ejer2_Informacion.csv"
    #define DOMINIOS "archivosCSV/ejer2_Dominios.csv"
    #define MODO_LECTURA "r" 
    #define TAM_CHAR 50 
    #define NRO_DOM 11 // nro de campos para la cabecera de la matriz que contiene los dominios
    #define BYTE 1048576

// ESTRUCTURAS
    typedef struct {
        int usuario; 
        int mes; 
        int bytes; 
        char url[5]; 
    } Datos; 

    typedef struct {
        char cadena[TAM_CHAR]; 
    } VectorCadena ; 

    typedef struct {
        int bytes[12]; 
        int mes[12]; 
        int cabecera; 
    } Matriz; 

// PROTOTIPOS 
    FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) ;
    void cerrarArchivo(FILE *fd) ; 
    void procesarArchivo(FILE *fd); 
    void errorMemoria(); 
    VectorCadena *leerDominios (VectorCadena dominios[10]) ;
    Matriz **guardarDato (Matriz **matriz, Datos dato, int *indice, VectorCadena dominios [10]) ;
    Matriz **inicializarMatriz(Matriz **matriz, int indice, int usuario  ) ;
    void impresion (Matriz **matriz, int indiceMatriz, VectorCadena dominios[10]); 
    void totales(Matriz ** matriz, int indiceMatriz ); 

// FUNCION PRINCIPAL 

int main() {

     // abrimos el archivo
    FILE *fd; 
    fd = abrirArchivo(ARCHIVO, MODO_LECTURA); 

    //procesamos el archivo 
    procesarArchivo(fd); 

    // cerramos el archivo 
    cerrarArchivo(fd); 

}
/* Procesamos el archivo, creamos la matriz y vector necesario para el efecto, llamamos a las demas funciones */
void procesarArchivo(FILE *fd) {
    Datos dato; // variable temporal donde almacenar los datos que voy leyendo 

    /*Declaro una matriz que en su posicion i=0 tendra todos los dominios posibles y en j=0 tendra a cada usuario. 
    En cada posicion de la matriz se enecuentra un vector de 12. Se guarda de la sgte manera =  
    fila[0] = dominios 
    columna[0] = usuarios 
    Matriz [fila][columna] = Se encuentra el vector de 12 que almacena los mb consumidos en cada mes por usuario por dominio  */
     
    Matriz **matriz; 
    int indiceMatriz = 1; 
    matriz = (Matriz **)malloc(NRO_DOM*sizeof(Matriz)); 

    /* Declaro un vector de cadenas en donde guardare los nombres de mis dominios (leidos desde un archivo)*/
    VectorCadena dominios[10]; 
    leerDominios(dominios);
    char url[TAM_CHAR]; 

    if (matriz == NULL) {
        errorMemoria(); 
    } else {
        matriz = inicializarMatriz(matriz, 0, 0);
        if (matriz != NULL) {
            fscanf(fd, "%d,%*d/%d %*d:%*d,%d,%s", &dato.usuario, &dato.mes, &dato.bytes, url ); 
            while (!feof(fd)) {
                for (int i=0; i<10; i++){
                    if (strstr(url,dominios[i].cadena) != NULL) {
                        strcpy(dato.url,dominios[i].cadena); 
                    }
                }
                matriz = guardarDato(matriz, dato, &indiceMatriz, dominios); 
                fscanf(fd, "%d,%*d/%d %*d:%*d,%d,%s", &dato.usuario, &dato.mes, &dato.bytes, url ); 

           }   
        }
    }
    impresion(matriz, indiceMatriz, dominios);  
}

/*Leo los valores de los dominios que nos interesan desde un archivo llamado Dominios.csv*/
VectorCadena * leerDominios (VectorCadena dominios[10]) {
    FILE *fd;
    fd = abrirArchivo(DOMINIOS, MODO_LECTURA); 

    for (int i=0; i<10; i++) {
        fscanf(fd, " %s", dominios[i].cadena); 
    }
    
    cerrarArchivo(fd); 
    return dominios; 
}

/* Recorre la matriz. Si el usuario ya tiene una fila en la matriz, guarda los datos. 
Si no, le reserva espacio y guarda sus datos */

Matriz ** guardarDato (Matriz **matriz, Datos dato, int *indice, VectorCadena dominios [10]) {
    int banderaUsuario = 0,banderaDominio = 0;
    for (int i=0; i<*indice; i++) {
        if (matriz[0][i].cabecera == dato.usuario) {
            banderaUsuario = i; // existe el usuario en la matriz   
        } 
    }
    if (banderaUsuario == 0) { // si el usuario no existe en la matriz reservamos espacio, inicializamos la matriz en cero y guardamos los datos 
        matriz [*indice] = malloc ( ( NRO_DOM * sizeof(Matriz)) ) ; 

        if (matriz != NULL) {
            inicializarMatriz(matriz, *indice, dato.usuario); 

            banderaUsuario = *indice; // guardamos el espacio que creamos para ese usuario 
            *indice = *indice + 1;   
        } else {
            errorMemoria(); 
        }
    }

    for (int j=1; j<NRO_DOM-1; j++) {
        for (int k=1; k<12; k++) {
            if (dato.mes == k){
                if (strcmp(dato.url, dominios[j-1].cadena) == 0) {
                    matriz[banderaUsuario][j].bytes[k] = matriz[banderaUsuario][j].bytes[k] + dato.bytes; 
                    banderaDominio = 1; // el dominio es uno de los que nos interesa 
                }
        
            }
        }
    }
    if (banderaDominio == 0) { // si el dominio no es de los que nos interesan, lo guardamos en la ultima columna "otros"
        matriz[banderaUsuario][10].bytes[dato.mes] = matriz[banderaUsuario][10].bytes[dato.mes] + dato.bytes ;
    }

    return matriz; 
}

/* Para inicializar la matriz, pongo los valores correspondientes en la cabecera 
fila[0] = dominios 
columna[0] = usuarios 
Todas los campos que no son cabecera se inicializan en cero porque sera n acumuladores para los datos
*/
Matriz ** inicializarMatriz(Matriz **matriz, int indice, int usuario ) {

    if (indice == 0 ) { // si es la primera fila de la matriz se cargan las cabeceras (numeros del 1 al 10 que representan los diferentes dominios)
        for(int i=1; i<NRO_DOM; i++) {
            matriz[0][i].cabecera = i; 
        }
    } else {
        for(int i=1; i<NRO_DOM; i++) {
            for(int k=1; k<12; k++) {
                matriz[indice][i].bytes[k] = 0; 
            }
        }
    }
    matriz[indice][0].cabecera = usuario; 
    return matriz; 
}

/* Abrir el archivo */
FILE *abrirArchivo(char nombreArchivo[], char modoApertura[]) {
    FILE *fd = fopen(nombreArchivo, modoApertura);
    if (fd == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombreArchivo);
        exit(-1);
    }
    return fd;
}

/* Cerrar el archivo */
void cerrarArchivo(FILE *fd) {
    fclose(fd);
} 

/* Imprime un mensaje si no se ha podido reservar la memoria :p*/ 
void errorMemoria () {
    printf("\n =( Error en el almacenamiento de la memoria =("); 
    exit (-1); 
}

/* Se imprime el informe y se libera el espacio de la memoria */
void impresion(Matriz **matriz, int indiceMatriz, VectorCadena dominios[10]){ 

    VectorCadena meses [12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}; 
    int bandera = 0; 

    for(int i=1;i<indiceMatriz;i++){
        printf("\n\n\n -- > Usuario: %d", i);
        for(int j=1;j<NRO_DOM;j++){
            for(int k=0;k<12;k++){
                if (matriz[i][j].bytes[k] != 0) {
                    
                        printf("\n\n\tDominio: %s", dominios[j-1].cadena); 
                       
                    printf("\n\t Mes: %s | Consumo: %f mb", meses[k-1].cadena, (((float)matriz[i][j].bytes[k]) / BYTE)); 
                }
            }
            bandera = 0; 
        }
    } 
    // Impresion de los totales 
    totales(matriz, indiceMatriz); 


    // libero el espacio despues de imprimir el reporte 
    if (matriz != NULL) {
        free (matriz); 
    }
}

void totales(Matriz ** matriz, int indiceMatriz ) {

    int totalGeneral =0 , totalUsuario=0; 

    printf("\n"); 

    for(int i=1;i<indiceMatriz;i++){
        printf("\n Total del usuario %d: ", i);
        for(int j=1;j<NRO_DOM;j++){
            for(int k=0;k<12;k++){
                totalUsuario += matriz[i][j].bytes[k]; 
                totalGeneral += matriz[i][j].bytes[k]; 
            }
        }
        printf("%f mb", (float) totalUsuario/BYTE); 
        totalUsuario = 0; 
    } 
    printf("\n Total general: %f mb", (float)totalGeneral/BYTE); 
} 