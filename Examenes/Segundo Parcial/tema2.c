#include <stdio.h> 

#define N 4// es el numero de filas y columnas de mi matriz, puse como constante para usar el ejemplo D: 

// PROTOTIPADO
    int recorrerMatriz ( int i, int j, int matriz[N][N], int numeroBuscado); 
    int buscarMayorFila(int i, int  j, int matriz[N][N], int mayor) ; 
    int buscarMayorColumna(int i, int  j, int matriz[N][N], int mayor); 
    int busquedaMenor(int i, int j, int menor, int matriz[N][N]); 
    void recursionPrincipal ( int matriz [N][N], int menor, int centinela); 

int main () {

	int matriz[N][N] = {15,2,12,8,1,14,10,5,8,9,3,16,11,8,6,7}; // Se asume que el array ya se encuentra cargado en memoria.

    int menor = busquedaMenor(0, 0, matriz[0][0], matriz); 

    recursionPrincipal (matriz, menor, 0); 
	// recorrerMatriz(0, 0, matriz, 0, 0);
}

/* PARA IMPRIMIR LA SECUENCIA DEBO  
        1. Buscar el menor entre los mayores (guardo en dato)
        2. Buscar imprimir dato+1 y si no hay 

        3. Volver a empezar con dato +1 
        4. Si hay, buscar dato +1 +1 

        5. Si no hay, volver al paso 3

        Centinela = si centinela = -1, es pq no se encontro en la matriz el nro siguiente (menor + 1)
                    si centinela = 1 es pq existe el nro (?)
*/

//////
void recursionPrincipal ( int matriz [N][N], int dato, int centinela) {
    if (centinela == 1) {
        printf("%d  ", dato); 
        centinela = recorrerMatriz(0, 0, matriz, dato+1);  // busca el siguiente dato si existe o non 
    } else if (centinela == -1)  { 
        recursionPrincipal(matriz, dato+1, centinela); // comienza la busqueda desde el siguiente dato 
    }
    
}

int recorrerMatriz ( int i, int j, int matriz [N][N], int numeroBuscado) { 
	if (i==(N-1) && j==(N-1) ){ 
		return 0; 
	} else  {

        // printf("\n Fila %d Columna %d MayorFila %d, MayorColumna %d" , i, j, buscarMayorColumna(0, j, matriz, 0),  buscarMayorFila(i, 0, matriz, 0)); 

        if (buscarMayorColumna(0, j, matriz, 0) == numeroBuscado) {
            return 1 ; 
        }
        if (buscarMayorFila(i, 0, matriz, 0)== numeroBuscado) {
            return 1 ; 
        }
		
        // recorrer 
		if (i < (N-1)) { 
			recorrerMatriz(i+1, j, matriz, numeroBuscado);  
		} 
        if (i == (N-1)) {
			printf("\n\n"); 
            recorrerMatriz(0, j+1, matriz, numeroBuscado); 
        }
	}
}

int buscarMayorFila(int i, int  j, int matriz[N][N], int mayor) {
    if (j == N) {
        return mayor; 
    } else {
        if (matriz[i][j]>mayor) {
            mayor = matriz[i][j]; 
        }
        buscarMayorFila(i, j+1, matriz, mayor); 
    }
}

int buscarMayorColumna(int i, int  j, int matriz[N][N], int mayor) {
    if (i == N) {
        return mayor; 
    } else {
        if (matriz[i][j]>mayor) {
            mayor = matriz[i][j]; 
        }
        buscarMayorColumna(i+1, j, matriz, mayor); 
    }
}

int busquedaMenor(int i, int j, int menor, int matriz[N][N]) {

    if (i==N && j==N){ 
		return menor; 
	} else  {
		if (matriz[i][j]<menor) {
            menor = matriz[i][j]; 
        }
		if (i<N) {
			busquedaMenor( i+1, j, menor, matriz); 
		}
		if (i == N) {
			busquedaMenor( 0, j+1, menor, matriz);  
		}
	}

}