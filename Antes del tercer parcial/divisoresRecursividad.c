#include <stdio.h> 
 
void numDivisores(int numero, int divisor); 

int main () {
    int dato;
    printf("\n Dato: "); 
    scanf("%d", dato);   
    numDivisores(31, 1);
}

void numDivisores(int numero, int divisor){
    if (divisor <= numero){
        if((numero % divisor) == 0){
            printf("%d ", divisor);
            numDivisores(numero, divisor + 1);
        } else {
            numDivisores(numero, divisor + 1);
        }
    }
}
