/*Gonzalo Cristaldo
5278949 - IEN */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <limits.h> 

#define NRO_PRODUCTOS 20
#define TAM_CHAR 20
#define FIN "fin"
#define NULO "nulo"

typedef struct prod { 
    struct f {
        int dia, mes, anho;
    } fecha;
    char codigo[TAM_CHAR]; 
    int precioInicial; 
    int variacionPrecio; 
} Producto; 

void impresion (Producto producto[NRO_PRODUCTOS], int posicion) ; 
int verificar (char codigo[TAM_CHAR], Producto producto[NRO_PRODUCTOS]) ; 
void intercambiar(int *a, int *b);

int main (){
    Producto producto[NRO_PRODUCTOS]; 

    // inicializo el vector
    for (int j=0; j<NRO_PRODUCTOS; j++) {
        strcpy(producto[j].codigo, NULO); // para que entre al ciclo  
        producto[j].variacionPrecio = 0;  // para poder usar como acumulador 
        producto[j].precioInicial  = 0; 
    }

    char codProducto[TAM_CHAR]; 
    int posicion=0, nuevoPrecio; 

    // iteracion para leer y modificar precios 
    while (strcmp(producto[posicion].codigo, FIN) != 0){
        printf("\nIngrese el codigo del producto (fin para terminar): "); 
        scanf("%s", codProducto); 
        posicion = verificar(codProducto, producto);  
        strcpy(producto[posicion].codigo, codProducto); 
        if (strcmp(producto[posicion].codigo, FIN) != 0){
            if ((producto[posicion].precioInicial == 0)){
                printf("Ingrese el precio inicial "); 
                scanf("%d", &producto[posicion].precioInicial); 
            } else {
                printf("Ingrese el nuevo precio  "); 
                scanf("%d", &nuevoPrecio);
                producto[posicion].variacionPrecio += (nuevoPrecio-producto[posicion].precioInicial); 
                producto[posicion].precioInicial = nuevoPrecio; 
            }
        }
        // impresion(producto, posicion); 
    }

    // precios q no variaron son los que tienen variacion == 0
    printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    printf("\n Estos son los productos cuyos precios no variaron: \n"); 
    for (int i=0; i<NRO_PRODUCTOS; i++) {
        if (producto[i].variacionPrecio == 0 && (strcmp(producto[i].codigo, NULO)!=0) && (strcmp(producto[i].codigo, FIN)!=0)) {
            impresion(producto, i); 
        }
    }
    
    // precios con mas variacion 
    printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
    printf("\n Estos son los productos cuyos precios mas variaron: \n"); 

    int mayor= 0; int mayorAnterior = INT_MAX; int pos; 
    for (int k=0; k<3; k++){
        for (int i=0; i<NRO_PRODUCTOS; i++) {
            if (mayor<producto[i].variacionPrecio && mayorAnterior>producto[i].variacionPrecio) {
                mayor = producto[i].variacionPrecio; 
                pos = i; 
            }
        }
        printf("\n Producto #%d con mas variacion: %s", k+1, producto[pos].codigo); 
        mayorAnterior = mayor; 
        mayor = 0; 
    }
}

// intercambia los valores en el ordenamiento burbuja 
void intercambiar(int *a, int *b) {
  int temporal = *a;
  *a = *b;
  *b = temporal;
}

int verificar (char codigo[TAM_CHAR], Producto producto[NRO_PRODUCTOS]) {
    int posicion=0, bandera=0; 

    // verifico si existe el producto
    for (int i=0; i<NRO_PRODUCTOS; i++) {
        if (strcmp(codigo, producto[i].codigo) == 0) {
            bandera = 1; 
            posicion = i; 
        }
    }
    if (bandera == 0){ // si la bandera es cero dp de recorrer el vector buscando el codigo significa q no existe, buscamos alguna posicion nula 
        for (int i=0; i<NRO_PRODUCTOS; i++) {
            if (strcmp(producto[i].codigo, NULO) == 0 && bandera == 0) {
                posicion = i; 
                bandera=1; 
            }
        }
    }
        // printf("\n Posicion: %d", posicion); 

    return posicion; // retorno la pos donde esta en el vector 
}

void impresion (Producto producto[NRO_PRODUCTOS], int posicion) {
        printf("\n\tCodigo: %s", producto[posicion].codigo); 
        // printf("\n\t Variacion de precio: %d", producto[posicion].variacionPrecio); 
}