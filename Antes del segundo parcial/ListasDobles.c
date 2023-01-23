#include <stdio.h>
#include <stdlib.h>

// ESTRUCTURAS 
    typedef struct nodo {
        int dato; 
        struct nodo * siguiente; 
        struct nodo * anterior; 
    } NODO; 

    NODO *inicio = NULL; // declaramos la cabeza y la cola como variables globales
    NODO *final = NULL; 

// PROTOTIPOS
    void Agregar ();
    void Buscar ();
    void Eliminar ();
    void Recorrer ();
    void Insertar (int dato); 
    NODO *buscarNodo (int dato); 
    void eliminarNodo (NODO *nodo); 

// MAIN - ES EL MENU 
int main () {
    int opcion = 0; // inicializo con 0 para que entre la primera vez al ciclo 

    while (opcion != 5){
        
        printf("\n1. Agregar Nuevo"); 
        printf("\n2. Buscar Elemento");
        printf("\n3. Eliminar");  
        printf("\n4. Recorrer");  
        printf("\n5. Salir");  
        printf("\nOpcion: "); 

        scanf("%d", &opcion); 

        switch (opcion) {
            case 1: 
            Agregar(); 
            break; 

            case 2: 
            Buscar(); 
            break; 

            case 3: 
            Eliminar(); 
            break; 

            case 4: 
            Recorrer(); 
            break;

            default: 
            break; 
        }

    } 
    return 0; 
}
// INSERTAR
void Insertar (int dato) {

    NODO *nuevo = (NODO*) malloc (sizeof(NODO)); 

    if (nuevo != NULL) {
        
        nuevo->dato = dato; 
        nuevo->siguiente=NULL; 
        
        if (inicio != NULL) { // si tiene elementos
            nuevo->anterior = final; 
            final->siguiente = nuevo; 
        }else{ // si no tiene elementos (es el primero)

            inicio = nuevo; 
            nuevo->anterior = NULL; 
        }
        final = nuevo; 

    }else{
        printf("No hay memoria para el nodo nuevo"); 
        exit(1); 
    }
}

// AGREGAR
void Agregar () {

    // Leemos el dato a insertar 
    printf("\nEscribe el dato que quieres agregar: "); 
    int dato; scanf("%d", &dato); 
    printf("\nEl dato es %d", dato); 

    Insertar(dato); 
}

// BUSCAR lee el dato a buscar y lo manda a buscarNodo. Imprime si se encontro o no el resultado 
void Buscar (){
    
    printf("\nEscribe el dato que quieres buscar: "); 
    int dato; scanf("%d", &dato); 

    NODO *resultado = buscarNodo (dato); 

    if (resultado != NULL) {
        printf("\nEl dato se encontro en la direccion %p", resultado); 
    }else{
        printf("\nEl dato NO se encontro ");
    }
}
// ELIMINAR: lee el dato a buscar y lo elimina
void Eliminar () {
    
    printf("\nEscribe el dato que quieres eliminar: "); 
    int dato; scanf("%d", &dato); 

    NODO *resultado = buscarNodo (dato); // buscamos el nodo para eliminarlo 

    if (resultado != NULL) {
        eliminarNodo(resultado); 
    }else{
        printf("\nEl dato no existe, por eso no puede eliminarse  ");
    }
}

// RECORRER: recorre e imprime la lista ligada 
void Recorrer (){

    printf("\nLista enlazada: "); 
    NODO *aux = inicio; 

    while (aux != NULL) {
        printf("%d - ", aux->dato ); 
        aux = aux->siguiente;
    }
}

/* BUSCAR NODO ubica el elemento y devuelve un puntero a el elemento.
 Se usa en la funcion Buscar y en la funcion Eliminar 
 Buscar = compara si es null o no para saber si existe el elemento 
 Eliminar = usa el puntero al elemento para eliminarlo */
NODO *buscarNodo (int dato){
    NODO *aux = inicio; 

    while (aux != NULL) {
        if (dato == aux->dato){
           return aux; 
        }
         aux = aux->siguiente;
    }
    return aux;
}

/*ELIMINAR NODO cambia las posiciones de los punteros para eliminar un nodo 
    Suponiendo los nodos A, B y C (que serian tres nodos seguidos)
    Sabemos que A.siguiente es B 
    Para eliminar B = A.siguiente pasa a ser &C 
    De esta manera "saltamos" el vector B y lo eliminamos de nuestra lista. 

*/
void eliminarNodo (NODO *nodo) {
    NODO *anterior = nodo->anterior; 
    NODO *siguiente = nodo->siguiente; 

    if (anterior != NULL) {
         anterior->siguiente= nodo->siguiente;  
    } else {
        inicio = siguiente; 
    }

    if (siguiente != NULL) {
        siguiente->anterior = nodo ->anterior; 
    } else {
        final = anterior ; 
    }
    free (nodo); 
}