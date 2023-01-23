#include <stdio.h>
#include <stdlib.h>

// STRUCT  
typedef struct nodo {
	int dato; 
	struct nodo * siguiente; 
} NODO; 

// PROTOTIPOS 
NODO* CrearNodo (int dato); 
int InsertarInicio (NODO **cabeza, int dato); 
int InsertarFinal (NODO **cabeza, int dato); 
void ImprimirLista (NODO *cabeza); 
int  EstaVacia (NODO *cabeza); // si una lista esta vacia el .siguiente de la cabeza es null. Esta funcion verifica si una lista etsa vcia (no tiene elementos)
int ExisteElemento (NODO *cabeza, int dato); 

// MAIN 
int main () {

	NODO *cabeza = NULL ; 
	int aux; 

	InsertarInicio (&cabeza, 5); 
	InsertarFinal (&cabeza, 6);
	InsertarFinal (&cabeza, 7);
	
	ImprimirLista (cabeza); 
	
	// para comprobar si un elemento existe o no en la lista
	aux = ExisteElemento(cabeza, 1); 
	if (aux == 1) 
		printf ("\nLa lista esta vacia");
	else 
		printf ("\nLa lista NO esta vacia");
	

	// para comprobar si esta vacia o no
	aux = EstaVacia (cabeza); 
	if (aux == 1) 
		printf ("\nEl elemento esta en la lista");
	else 
		printf ("\nEl elemento NO esta en la lista");
	
	return 0;
}

// CREAR NODO 
NODO* CrearNodo (int dato) {
	
	NODO *nuevo = NULL; 
	nuevo = (NODO *) malloc (sizeof(NODO)); 
	
	if (nuevo != NULL ) { // con eso comprobamos que se haya podido reservar el espacio 
		nuevo->dato = dato; 
		nuevo->siguiente = NULL; 
	}
	return nuevo; 
}

// INSERTAR AL INICIO  
int InsertarInicio (NODO **cabeza, int dato) {
	NODO *nuevo = NULL; 
	nuevo = CrearNodo (dato); 
	
	if (nuevo != NULL ) {	
		nuevo->siguiente = *cabeza; 
		*cabeza = nuevo; 
		return 1; 
	}
	return 0; 
}

// INSERTAR AL FINAL 
int InsertarFinal (NODO **cabeza, int dato) {
	
	NODO *nuevo = NULL, *aux = *cabeza; 
	nuevo = CrearNodo (dato); 
	
	if (nuevo != NULL ) {	
	
		// recorremos la lista ligada buscando el ultimo elemento; el que tiene .siguiente en NULL 
		while (aux->siguiente != NULL ) {
			aux = aux->siguiente;  
		}
		aux->siguiente = nuevo; 
		return 1; 	
	}
	return 0; 
}

// IMPRIMIR LISTA 
void ImprimirLista (NODO *cabeza) {
	
	NODO *aux = cabeza; 

	while (aux != NULL) {
		printf("%d", aux->dato); 
		aux = aux->siguiente; 
	}
}

// SI LA LISTA ESTA VACIA el .siguiente de la cabeza es null. Esta funcion verifica si una no tiene elementos 

int  EstaVacia (NODO *cabeza) {
	
	if (cabeza == NULL) {
		return 1; 
	}
	return 0; 
}

// BUSCAR ELEMENTOS 
int ExisteElemento (NODO *cabeza, int dato) {
	
	NODO *aux = cabeza; 
	
	while (aux != NULL) {
		if (aux->dato == dato) {
			return 1; 
		}
		aux = aux -> siguiente; 
	}
	return 0; 
}


















