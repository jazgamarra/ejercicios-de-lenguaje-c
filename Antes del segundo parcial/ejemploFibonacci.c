/* Secuencia de Fibonacci  */
#include <stdio.h> 

int main() {
    int fibonacci (int f); 
    int resultado, i; 

    for (i=1; i<=8; i++) {
        resultado = fibonacci(i); 
        printf("\n %d ", resultado); 
    }
    
}
int fibonacci(int dato) {
    if ((dato == 0) || (dato == -1)) 
        return 1; 

     else 
        return fibonacci(dato-1) + fibonacci(dato-2); 
    
}