/*
Funciones con listas enlazadas
Jazmin Gamarra 
23/06/22
*/

#include <stdio.h>
#include <stdlib.h>

// Estructuras. 
    struct nodo {
        int dato; 
        struct nodo *siguiente; 
    };  
    typedef struct nodo *Nodo; 
    typedef struct nodo *Lista; 

// Prototipos. 
    Lista insertarNodo (Lista, int); 
    void imprimirLista (Lista);
    Lista borrarNodo (Lista lista, int dato);
    Lista insertarEnOrden (Lista lista, int dato); 
    Lista ordenarLista (Lista lista); 
    Lista insertarEnPosicion (Lista lista, int dato, int posicion); 
    int promedioLista (Lista lista); 
    void liberarLista (Lista lista); 

// Función Principal.
int main (){ 
    Lista lista = NULL; 

    printf("\n-> Insertar al final \n"); 
    lista = insertarNodo(lista, 10); 
    lista = insertarNodo(lista, 20); 
    lista = insertarNodo(lista, 30); 
    lista = insertarNodo(lista, 40); 
    imprimirLista(lista);


    printf("\n-> Borrar un nodo \n"); 
    lista = borrarNodo(lista, 30); 
    imprimirLista(lista);


    printf("\n-> Insertar en medio ordenadamente\n"); 
    lista = insertarEnOrden(lista, 30); 
    imprimirLista(lista);


    printf("\n-> Ordenar nodos \n"); 
    lista = insertarNodo(lista, 25); 
    lista = insertarNodo(lista, 15); 
    imprimirLista(lista); 
    lista = ordenarLista(lista); 
    imprimirLista(lista); 


    printf("\n-> Insertar en una determinada posicion \n"); 
    lista = insertarEnPosicion(lista, 44, 4); 
    imprimirLista(lista); 

    lista = borrarNodo(lista, 15); 
    lista = borrarNodo(lista, 25); 
    lista = borrarNodo(lista, 44); 


    int promedio; 
    promedio = promedioLista(lista); 
    printf("\n-> El promedio de la lista es %d \n", promedio); 
    imprimirLista(lista); 


    printf("\n\n - - - - \n Liberar lista");
    liberarLista(lista); 
}

// Insertar nodo
Lista insertarNodo(Lista lista, int dato) {
    Nodo nuevo = malloc (sizeof(struct nodo)); 
    if (nuevo != NULL){
        nuevo->dato = dato; 
        nuevo->siguiente = NULL; 

        // Si es el primer elemento de la lista... 
        if (lista == NULL) {
            lista = nuevo; 
        } else { 
            // Almacenamos la direccion de memoria del primer nodo para recorrerla buscando el ultimo nodo
            Lista temporal = lista; 
            while (temporal->siguiente != NULL){
                temporal = temporal->siguiente; 
            }
            // Asignamos su lugar al nuevo nodo
            temporal->siguiente = nuevo; 
        }
    }
    return lista; 
}

// Borrar nodo. 
Lista borrarNodo (Lista lista, int dato) {
    Lista anterior = NULL; 
    Lista temporal = lista; 

    while (temporal != NULL){
        if (temporal->dato == dato){
            if (anterior == NULL) {
                anterior = temporal; 
                temporal = anterior->siguiente; 
                free(anterior); 
                lista = temporal; 
            } else {
                anterior->siguiente = temporal->siguiente; 
                free(temporal); 
                temporal = anterior->siguiente; 
            }
        } else {
            anterior = temporal; 
            temporal = temporal->siguiente; 
        }
    }
    
    return lista; 
}

// Imprimir Lista
void imprimirLista (Lista lista){
    for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {
        printf("%d\t", temporal->dato); 
    }
    printf("\n"); 
}

// Insertar nodos en orden ascendente
Lista insertarEnOrden (Lista lista, int dato){
    Nodo nuevo = malloc (sizeof(struct nodo));  
    if (nuevo != NULL){
        nuevo->dato = dato; 
        nuevo->siguiente = NULL;  
        
        Lista anterior = NULL;
	    Lista temporal = lista;

        //buscamos en donde poner el dato
        while(temporal != NULL && nuevo -> dato > temporal -> dato){
            anterior = temporal; 
            temporal = temporal -> siguiente; 
        } 
        //insertar un nuevo nodo al principio de la lista
        if(anterior == NULL){
            nuevo -> siguiente = lista;
            *lista = *nuevo;
        } 
        else {
            anterior -> siguiente = nuevo;
            nuevo -> siguiente = temporal;
        }

    }
    return lista; 
}

// Ordenar imita el funcionamiento del metodo de ordenacion burbuja, aplicado a listas ligadas 
Lista ordenarLista (Lista lista) {

    Lista actual = lista, siguiente; 
    int temporal; 

    while (actual->siguiente != NULL) {            
        siguiente = actual->siguiente;       

        while (siguiente != NULL) {    

            if (actual->dato > siguiente->dato) {
                temporal = siguiente->dato;
                siguiente->dato = actual ->dato; 
                actual->dato = temporal; 
            }
            siguiente = siguiente->siguiente;
        }

        actual = actual->siguiente; 
        siguiente = actual->siguiente; 
    } 
    return lista; 
}

// Insertar en una determinada osición 
Lista insertarEnPosicion (Lista lista, int dato, int posicion){
    Nodo nuevo = malloc (sizeof(struct nodo));  
    if (nuevo != NULL){
        nuevo->dato = dato; 
        nuevo->siguiente = NULL;  
        
        Lista anterior = NULL;
	    Lista temporal = lista;

        //buscamos en donde poner el dato
        int i = 1; 
        while(temporal != NULL && i != posicion){
            anterior = temporal; 
            temporal = temporal -> siguiente; 
            i++; 
        } 

        //insertar un nuevo nodo al principio de la lista
        if(anterior == NULL){
            nuevo -> siguiente = lista;
            *lista = *nuevo;
        } 
        else {
            anterior -> siguiente = nuevo;
            nuevo -> siguiente = temporal;
        }
    }
    return lista; 
}

// Calcular promedio. 
int promedioLista (Lista lista) {
    int sumatoria = 0, cantidad = 0; 
    for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {
        sumatoria +=  temporal->dato; 
        cantidad++; 
    }
    return sumatoria/cantidad; 
}

// Liberar lista 
void liberarLista (Lista lista) {
    if (lista != NULL){
        free(lista); 
    }
}