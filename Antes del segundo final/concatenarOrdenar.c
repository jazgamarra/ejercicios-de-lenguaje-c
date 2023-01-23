/*
Concatenar y ordenar listas :)
Jazmin y Manu  
26/06/22
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
    Lista concatenar(Lista lista1, Lista lista2); 
    Lista ordenarLista (Lista lista); 

int main () {
    Lista lista1 = NULL; 
    lista1 = insertarNodo(lista1, 5); 
    lista1 = insertarNodo(lista1, 2); 
    lista1 = insertarNodo(lista1, 1);

    Lista lista2 = NULL; 
    lista2 = insertarNodo(lista2, 6); 
    lista2 = insertarNodo(lista2, 9); 
    lista2 = insertarNodo(lista2, 7);

    printf("\n Lista 1: ");
    imprimirLista(lista1); 
    printf("\n Lista 2: ");
    imprimirLista(lista2); 

    Lista lista3; 
    lista3 = concatenar(lista1, lista2); 

    printf("\n Lista 3: ");
    imprimirLista(lista3); 

    printf("\n Lista 3 ordenada: ");
    lista3 = ordenarLista(lista3); 
    imprimirLista(lista3); 
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

// Imprimir Lista
void imprimirLista (Lista lista){
    for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {
        printf("%3d", temporal->dato); 
    }
    printf("\n"); 
}

// Concatena dos listas recibidas por valor 
Lista concatenar(Lista lista1, Lista lista2){
    Lista concatenada = NULL ; 
    concatenada = lista1; 
    
    Lista aux = lista1; ; 
    while (aux->siguiente != NULL){
        aux = aux->siguiente; 
    }
    aux->siguiente = lista2; 
    return concatenada; 
}

// Ordenar imita el funcionamiento del metodo de ordenacion burbuja, aplicado a listas ligadas 
Lista ordenarLista (Lista lista) {

    Lista actual = lista; 
    Lista siguiente; 
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