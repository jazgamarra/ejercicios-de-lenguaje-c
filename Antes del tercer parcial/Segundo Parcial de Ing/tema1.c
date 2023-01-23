/*Gonzalo Cristaldo
5278949 - IEN */
#include <stdio.h> 
#include <stdlib.h> 

int main (){
	int N, i, j; 
	printf("\nIngrese el orden de la mapa (al ser una matriz simetrica se leera solo un numero):  ") ; 
	scanf("%d", &N); 
	
	int mapa[N][N]; 
	
// Carga del mapa con random 
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
		mapa[i][j]= (rand() % 10)+1; 			
	    } 
    }
	
// Impresión del mapa original 
	printf("\nEste es el mapa \n\n"); 
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			printf("%d\t", mapa[i][j]); 
		
	    }
		printf("\n\n"); 
	}

    int f,c,x,y; 
    fflush(stdin);

    printf("\nIngrese la ciudad de inicio en este formato -> i,j (posiciones de 1 a N) "); 
	scanf("%d,%d", &f, &c); 
    printf("\nIngrese la ciudad de destino en este formato -> i,j (posiciones de 1 a N) "); 
	scanf("%d,%d", &x, &y); 

	printf("\nEstas son las posiciones de inicio y fin: \n\n");  
	for (i=0; i<N; i++){
		for (j=0; j<N; j++){ 
			if (((i==f)&&(j==c))||((x==i)&&(y-1==j))) {
                printf("X\t"); 
            } else {
                printf("%d\t", mapa[i][j]);
            }
		
	    }
		printf("\n\n"); 
	}

    // calculo del camino directo (haciendo una L)
    int camino = 0; 

    f=f-1; c=c-1; x=x-1; y=y-1; // mi matriz inicia desde cero 

    while (f != x || c != y ) { 

        if (f > x && c == y ) { 
            camino = camino + mapa [f] [c] ; 
            f-- ; 
        }
        else if (f > x && c ==  y ) { 
            camino = camino + mapa [f] [c] ; 
            f-- ; 
            c ++ ;
        } 
        else if (f > x &&c > y ) { 
            camino = camino + mapa [f] [c] ; 
            f-- ; 
            c-- ; 
        } 
        else if (f < x && c == y ) { 
            camino =  camino + mapa [f] [c] ; 
            f++ ; 
        } 
        else if (f < x && c < y ) { 
            camino = camino + mapa [f] [c] ; 
            f++ ; 
            c ++ ; 
        } 
        else if (f< x && c > y ) { 
            camino = camino + mapa [f] [c] ; 
            f++ ; 
            c-- ; 
        }
        else if (f == x && c > y ) { 
            camino =  camino + mapa [f] [c] ; 
            c-- ; 
            
        }
        else if (f == x && c < y ) { 
            camino = camino + mapa [f] [c] ; 
            c++ ;
        }

    }
        printf("\n El camino mas corto es %d: ", camino); 
}