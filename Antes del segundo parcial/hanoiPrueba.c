/* Torre de Hanoi - Version Iterativa  
Jazmin Gamarra 
29/04/2022 
*/
#include <stdio.h>
#include<stdlib.h>
#include <math.h>

// ESTRUCTURA 
typedef struct pila {
  int disco;
  int numMovimientos; 
  struct pila *siguiente;
} PILA;


// PROTOTIPO 
    void TorreHanoi (int n); 
    PILA * InicializacionTorres(int n, PILA *torre);  
    PILA * agregar (PILA * pila, int disco, int numMovimientos); 
    PILA* eliminarUltimo(PILA *torre);     
    void mover (int disco, PILA * origen, PILA * destino); 
    void opcionesMover (int disco); 
    int buscarDiscoEnMovimiento (int mov, int n); 
    void imprimir (PILA *torre) ; 
// GLOBALES 
    #define FALSE 0
    #define TRUE 1
    PILA *torre1 = NULL; 
    PILA *torre2 = NULL; 
    PILA *torre3 = NULL; 

// MAIN 
int main() { 
    TorreHanoi(4); 
}

// TORRE DE HANOI 
void TorreHanoi (int n) {
   
    torre1 = InicializacionTorres(n, torre1); // cargo todos los discos en la primera torre 
    int discoEnMovimiento, mov; 

     

    /*El numero minimo de movimientos necesarios para resolver el problema es (2 ^ n)-1 veces 
    Por ejemplom, con 3 discos el nro minimo de pasos es 
    (2 ^ 3) - 1 = 7 pasos.           */
    int minimoPasos = (pow(2,n)-1); 
    printf("\nEl numero minimo de pasos es: %d",minimoPasos);

    for (mov = 1; mov < minimoPasos ; mov++) { 
        // imprimo las tres torres 
        printf("\n \n      Torre 1 \n");imprimir(torre1); 
        printf("\n - - - - - - - - -\n      Torre 2 \n");imprimir(torre1);
        printf("\n - - - - - - - - -\n      Torre 2 \n");imprimir(torre1); 


        // imprimo nro de movimientos 
        printf("\n ---------------------------------------------  \n  Mov n. %d :", mov); 
        if (mov % 2 == 1){
            discoEnMovimiento = 1;
        } else {
            discoEnMovimiento = buscarDiscoEnMovimiento(mov, n);
        }
        opcionesMover (discoEnMovimiento); 
         
    }
}


/*Agrega nodos a la pila que va a dar seguimiento a las posiciones de los discos */
PILA * agregar (PILA * pila, int disco, int numMovimientos){
    PILA *nuevoNodo = NULL; 
    nuevoNodo = malloc(sizeof(PILA));
    if (nuevoNodo != NULL){
        nuevoNodo->disco = disco;
        nuevoNodo->numMovimientos = numMovimientos; 
        nuevoNodo->siguiente = pila;
        pila = nuevoNodo; 
    } else {
        printf("Error en la asignacion de memoria del dato '%d'", disco); 
    }
    return pila; 
}  

PILA* eliminarUltimo(PILA *torre) {
    if (torre != NULL) {
        PILA *temporal = torre;
        torre =torre->siguiente;
        if (temporal != NULL){
            free(temporal);
        }
    }
    return torre; 
}

PILA * InicializacionTorres(int n, PILA *torre) {
    int i; 
    // pongo todos los discos en la primera torre 
    for (i=n; i>0; i--) {
        torre = agregar(torre, i, 0);  
    }
    // cerar el campo de movimiento anterior
    PILA *temporal = torre;
    while (temporal != NULL) {
        temporal->numMovimientos = 0;
        temporal = temporal->siguiente;
    }
    return torre; 
}


/*Se sabe que cada disco se mueve por primera vez en el movimiento 2 a la n-1
y que luego se mueve cada 2 a la n movimientos
Por eso en mi struct almaceno en que movimiento se movio cada disco por ultima vez y recibo eso como parametro 
De esa manera doy seguimiento al flujo de movimiento de los discos */

int buscarDiscoEnMovimiento (int mov, int n) {
    int disco, movsAnteriores; 
   
    for (disco=1; disco<n; disco++) {
        // busco en q torre está 
       
        if (torre1->disco == disco) {
            movsAnteriores = torre1->numMovimientos;
            torre1->numMovimientos = mov; 
        } else if (torre2->disco == disco) {
            movsAnteriores = torre2->numMovimientos;
            torre2->numMovimientos = mov; 
        } else if (torre3->disco == disco) {
            movsAnteriores = torre3->numMovimientos;
            torre3->numMovimientos = mov; 
        } 
        
        printf("recibo %d y %d", mov, movsAnteriores);

        // caso primer movimiento
        if (movsAnteriores == 0) {  
            if (pow(2, disco-1) == mov) {
            printf("retorna %d", disco); 
            return disco; 
            } 
        }
        if (movsAnteriores != 0) { 
            if ((movsAnteriores + pow(2, disco)) == mov)  { 
                printf("retorna %d", disco); 
                return disco;       
            }
        }   
    }
}

void opcionesMover (int disco) { 
    
    printf (" Mover disco %d de ", disco); 

    if (disco % 2 == 1) {
            if (disco == (torre1)->disco) { 
                torre2 = agregar(torre2, torre1->disco, torre1->numMovimientos); 
                torre1 = eliminarUltimo(torre1);
                printf("1 -> 2"); 
            }
            else if (disco == (torre2)->disco) {
                torre3 = agregar(torre3,  torre2->disco, torre2->numMovimientos); 
                torre2 = eliminarUltimo(torre2);
                printf("2 -> 3"); 
            }
            else if (disco == (torre3)->disco) {
                torre1 =  agregar(torre1,  torre3->disco, torre3->numMovimientos); 
                torre3 = eliminarUltimo(torre3); 
                printf("3 -> 1"); 
            } 
    }
    if (disco % 2 == 0) {
        if (disco == (torre1)->disco) {
                torre3 = agregar(torre3, torre1->disco, torre1->numMovimientos); 
                torre1 = eliminarUltimo(torre1);
                printf("1 -> 3"); 
            }
            else if (disco == (torre2)->disco) {
                torre1 = agregar(torre1, torre2->disco, torre2->numMovimientos); 
                torre2 = eliminarUltimo(torre2); 
                printf("2 -> 1"); 
            }
            else if (disco == (torre3)->disco) {
                torre2 = agregar(torre2, torre3->disco, torre3->numMovimientos); 
                torre3 = eliminarUltimo(torre3);
                printf("3 -> 2"); 
            } 
    }
        printf("\n ---------------------------------------------"); 

} 


void imprimir (PILA * torre) {
     
  PILA *temporal = torre;
  while (temporal != NULL) {
    printf("\n      - %d  -", temporal->disco);
    temporal = temporal->siguiente;
  }

}