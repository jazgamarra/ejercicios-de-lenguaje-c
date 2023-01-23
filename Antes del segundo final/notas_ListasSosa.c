/*
Listas enlazadas - Plantilla del Prof. Gustavo Sosa 

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
     
// Función Principal.
int main (){ 
    Lista lista = NULL; 
    lista = insertarNodo(lista, 10); 
    lista = insertarNodo(lista, 20); 
    lista = insertarNodo(lista, 30); 
    imprimirLista(lista);
    lista = borrarNodo(lista, 10); 
    imprimirLista(lista);
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
        printf("%4d", temporal->dato); 
    }
}