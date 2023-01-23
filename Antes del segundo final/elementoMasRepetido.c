/*Escribir una función que decida si una matriz cuadrada de orden n es mayoritaria. “una matriz
cuadrada de orden n se dice que es mayoritaria, si existe un elemento en la matriz cuyo número
de repeticiones sobrepasa a la mitad de n*n. El tratamiento debe hacerse con punteros

Jazmin Gamarra 
25/06/22
*/

#include <stdio.h>
#include <stdlib.h>

// Estructuras. 
    struct nodo {
        int dato, cant; 
        struct nodo *siguiente; 
    };  

    typedef struct nodo *Nodo; 
    typedef struct nodo *Lista; 

// Constantes. 
    #define N 5
    #define VERDADERO 1
    #define FALSO 0 

// Prototipos 
    void imprimirMatriz(int **matriz, int m, int n);
    int ** reservarEspacioMatriz(int ** matriz, int filas, int columnas);
    int ** cargarMatriz(int **matriz, int m, int n); 
    Lista insertarNodo (Lista, int); 
    void imprimirLista (Lista lista); 
    Lista recorrerLista (Lista lista, int dato); 
    Lista recorrerBuscarRepetidos (int ** matriz, Lista lista); 
    void imprimirLista (Lista lista); 
    void resultadosFinales (Lista lista); 

int main (){
    int ** matriz = NULL; 
    matriz = reservarEspacioMatriz(matriz, N, N); 
    matriz = cargarMatriz (matriz, N, N); 
    imprimirMatriz(matriz, N, N);

    Lista lista = NULL; 
    lista = recorrerBuscarRepetidos(matriz, lista); 
    imprimirLista(lista); 
    resultadosFinales(lista); 
}

// Se reserva el espacio para la matriz 
int ** reservarEspacioMatriz(int ** matriz, int filas, int columnas){
    matriz = (int **) malloc (sizeof(int *)*filas);

    for (int j = 0; j < columnas; j++){
        *(matriz+j) = (int*) malloc (sizeof(int)*columnas);
    }

    if (matriz == NULL){
        printf("\n ERROR EN LA ASIGNACION DE LA MEMORIA "); 
        exit(-1); 
    } 

    return matriz; 
}

// Se imprime la matriz 
void imprimirMatriz(int **matriz, int m, int n) {
    printf("\n------------------------------------"); 
    printf("\n Impresion de la matriz"); 
    printf("\n------------------------------------"); 
    for (int i = 0; i < m; i++){
        printf("\n"); 
        for (int j = 0; j < n; j++){
            printf("%4d",  *(*(matriz+i)+j)); 
        }
    }
}

// Se carga la matriz
int ** cargarMatriz(int **matriz, int m, int n) {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            *(*(matriz+i)+j) = i+j; 
        }
    }
    return matriz; 
} 

// Se inserta un elemento en la lista enlazada 
Lista insertarNodo(Lista lista, int dato) {
    Nodo nuevo = malloc (sizeof(struct nodo)); 
    if (nuevo != NULL){
        nuevo->dato = dato; 
        nuevo->cant = 1; 
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

// Se recorre la lista enlazada y se suma una repeticion si el numero esta cargado, si no, se carga un nuevo nodo
Lista recorrerLista (Lista lista, int dato){
    int existe = FALSO; 
   
    return lista; 
}

// Se recorre la matriz y por cada dato leido se compara si ya existe o no en la lista enlazada 
Lista recorrerBuscarRepetidos (int ** matriz, Lista lista){
    int existe = FALSO; 
     for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            existe = FALSO; 
             for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {
                if (temporal->dato == matriz[i][j]) {
                    temporal->cant += 1; 
                    existe = VERDADERO;
                } 
            }
            if (existe == FALSO){
                lista = insertarNodo(lista, matriz[i][j]); 
            }
        }
    }
    return lista; 
}

//Impresion de la lista enlazada 
void imprimirLista (Lista lista){
    printf("\n------------------------------------"); 
    printf("\nCuantas veces se repite cada numero"); 
    printf("\n------------------------------------"); 
    printf("\n     Numero   Cantidad"); 
    for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {
        printf("\n%8d  %8d", temporal->dato, temporal->cant); 
    }
}

void resultadosFinales (Lista lista) {
    int masRepetido = -1, cantRepeticiones = 0; 

    // Recorremos una vez para ver cual es el que se repite mas veces 
    for (Lista temporal = lista; temporal != NULL; temporal=temporal->siguiente) {

        if (temporal->cant > cantRepeticiones) {
            masRepetido = temporal->dato; 
            cantRepeticiones = temporal->cant; 
        }
    }
    
    printf("\n\nEl numero que mas se repite es %d (%d veces)", masRepetido, cantRepeticiones); 
    
    // Verificamos si se cumple la condicion "sobrepasa a la mitad de n*n"
    if (cantRepeticiones > (N*N)/2){
        printf("\nEs una matriz mayoritaria. El numero se repite mas de %d veces", (N*N)/2); 
    } else {
        printf("\nNo es una matriz mayoritaria "); 
    }
}
