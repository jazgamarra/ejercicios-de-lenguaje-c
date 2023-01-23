/* Tema 2 - Primer Final - TAA Sosa 
Jazmin Gamarra 
12/06/2022
*/ 
 
#include <stdio.h>
#include <stdlib.h>

#define N 10  /* N es la longitud del vector. Se especifica en el ejercicio que es constante. */

// ESTRUCTURA
typedef struct nodo {
	int dato;
    int posicion;  
	struct nodo * siguiente; 
} NODO;    

// PROTOTIPOS 
void cargarLista(NODO **lista, int dato, int posicion); 
void validarDatosIngresados ( int * posicion); 
void leerDatos (int * dato, int * posicion); 
int * generarVector (int * vector, NODO * lista); 
void imprimirVector(int * vector); 

// MAIN 
int main () {

        NODO *lista = NULL; 
        int dato, posicion, n; 
        printf("\n Ingrese la cantidad de datos que quiere introducir. Tenga en mente que el vector tiene %d posiciones ", N); 
        scanf("%d", &n); 

        for (int i=0; i<n; i++) {  
            leerDatos(&dato, &posicion);
            if (dato != 0){
                cargarLista(&lista, dato, posicion); 
            } 
        } 

    int * vector; 
    vector = generarVector(vector, lista); 
    imprimirVector(vector);

    if (lista != NULL) {
        free(lista); 
    }
}
/*- - - - - SUBRUTINAS - - - - - */

/* Se leen datos y posiciones */
void leerDatos (int * dato, int * posicion) {
    printf("\n Dato: "); 
    scanf("%d", dato);        
    printf(" Posicion: "); 
    scanf("%d", posicion); 
    validarDatosIngresados(posicion); 
}

/*CargarLista carga el numero leido a la lista */
void cargarLista(NODO **lista, int dato, int posicion){
    NODO *nuevo, *aux = *lista;

    nuevo = (NODO *)malloc(sizeof(NODO));
    if (nuevo != NULL){
        nuevo->dato = dato;
        nuevo->posicion = posicion;  
        nuevo->siguiente=NULL;
        
        // si la lista esta vacia asignamos directamente el nodo nuevo como primer elemento 
        if (*lista == NULL) {
            *lista = nuevo; 
        } else {
            // si no recorremos la lista ligada buscando el ultimo elemento; el que tiene .siguiente en NULL 
            while (aux->siguiente != NULL ) {
                aux = aux->siguiente;  
		    }
		    aux->siguiente = nuevo; 
        }
    }
}

/* Se valida que la posicion ingresada no supere el limite y que no sea negativa*/
void validarDatosIngresados ( int * posicion) {

    while (*posicion > N || *posicion < 0){
        printf("\n La posicion ingresada es invalida. Ingrese una nueva: ");
        scanf("%d", posicion); 
    }

}

/* Se genera un vector de N campos y se carga los datos de la lista */
int * generarVector (int * vector, NODO * lista) {
    vector = (int *) calloc (N, sizeof(int)); 
    if (vector != NULL){
        for(NODO *aux = lista; aux != NULL; aux=aux->siguiente) {
            *(vector+aux->posicion) = aux->dato; 
        }
    } 
    return vector; 
}

/* Se imprime el vector generado */
void imprimirVector(int * vector) {
    printf("\n Este es el vector:  \n");
    for (int i = 0; i < N; i ++){
        printf("%4d", *(vector+i)); 
    }
 }   