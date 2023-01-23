/*
Escribir una función recursiva que calcule el
cociente de la división entera de n entre m, siendo 
m y n dos números enteros positivos recursivamente.

Jazmin Gamarra 
22/6/22
*/

#include <stdio.h>
#include <stdlib.h>

// Constantes
#define n 1025 
#define m 4   
int division(int dividendo, int divisor, int cociente); 

int main (){

    printf("\n Se dividira: %d / %d ",n,m); 
    int resultado; 
    resultado = division(n,m,0); 
    printf("\n El cociente es: %d", resultado); 
} 

int division(int dividendo, int divisor, int cociente) {
    if (divisor*cociente == dividendo) {
        printf("\n No hay resto");
        return cociente; 
    } else if (divisor*cociente > dividendo){
            cociente -= 1; 
            printf("\n El resto es: %d", dividendo-(divisor*cociente)); 
            return cociente; 
    }  else {
        division(dividendo, divisor, cociente+1); 
    }
}