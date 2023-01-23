/* Dada una matriz cuadrada de orden N (N >= 5) cuyos elementos son números enteros positivos ó
negativos, se solicita la identificación y eliminación (liberación de memoria) de aquellas regiones
contiguas de 2x2 donde la suma de los valores sea igual a cero. El contorno irregular de la matriz
resultante será únicamente del lado derecho por lo que el desplazamiento cíclico siempre será en
dirección opuesta. Finalmente, establezca un mecanismo de restauración de la matriz con un uso
mínimo de la memoria 

Jazmin Gamarra 
8/06/2022
Me rindo en la parte de realloc xd 
*/ 

#include <stdio.h>
#include <stdlib.h>

#define N 7 

// estructura
typedef struct elementosEliminados {
	int i,j; 
}ElemElim; 

// prototipos 
	int ** cargarMatriz (int **mat) ;
	void imprimirMatriz (int **mat) ;
	void condicionCero(int **mat, int *filas) ;  
	void errorMemoria (); 
	int * inicializarCampos(int *campos); 
	void redimensionar (int **mat, int *nroFilas, int fila, ElemElim *elementos); 
	int * inicializarVectorTemporal(int *temp, int **mat, int nroFilas, int fila); 

int main () {
	// declaro la matriz como matriz a punteros y la inicializo cargando los valores del ejemplo 
	int **matriz;
	matriz = cargarMatriz(matriz); 
 	imprimirMatriz(matriz);
	
	// declaro un vector que me ayudará con las filas de la matriz dentada 
    int *camposDeCadaFila; 
	camposDeCadaFila = inicializarCampos(camposDeCadaFila); 

	// llamo a mi funcion que buscara que se cumpla la condicion indicada en el ejercicio
 	condicionCero(matriz, camposDeCadaFila); 
}

/* Subrutina para cargar la matriz del ejercicio a la matriz en notacion de punteros */
	int ** cargarMatriz (int **mat) {
		int matriz[N][N] = {1,2,3,6,8,-1,-2,7,0,-5,0,-7,-1,9,0,1,5,-3,-1,7,-16,8,
				-2,1,3,-9,1,8,6,-5,-3,-1,5,1,-5,5,1,-2,-5,4,8,-2,0,0,-5,-2,3,1,9}; 
		int i, j;  
		mat = malloc(N*sizeof(int*)); 
		if (mat != NULL ){
			// Ciclo FOR - Filas 
			for (i=0; i<N; i++){
				mat[i]=malloc(sizeof(int)*N);
				if (mat != NULL){
					// Ciclo FOR - Columnas 
					for (j=0; j<N; j++){ 
						*(*(mat+i)+j) = matriz[i][j];  
					}
				} else 
				errorMemoria(); 
			}	
		} else {
			errorMemoria(); 
		}
		return mat; 
	}

/* Subrutina para la impresion de la matriz*/
	void imprimirMatriz (int **mat) {
		int i, j; 
		printf("    "); 
		for (j=0; j<N; j++){ 
				printf("_____%d", j); 
		}
		printf("\n"); 

		for (i=0; i<N; i++){
			printf("\n %d |", i); ; 
			for (j=0; j<N; j++){ 
				printf("%6d", *(*(mat+i)+j)); 
			}
			printf("\n "); ; 
		}	
	}

/* Imprime un mensaje de error y finaliza el programa en caso de que no se haya podido 
reservar el espacio en memoria */
	void errorMemoria (){
		printf("Error en el almacenamiento de la memoria. "); 
		exit (-1); 
	}

/* La idea que tuve al usar este vector es que me facilite el numero de campos que posee 
cada fila, al ser una matriz dentada La inicializo con el valor de N ya que antes de la 
subrutina "CondicionCero" o "Redimensionar", es una matriz cuadrada. */
	int * inicializarCampos(int *campos) {
		campos = malloc(sizeof(int)*N); 
		if (campos != NULL){
			for (int i=0; i<N; i++) {
				*(campos+i) = N; 
			}
		} else {
			errorMemoria(); 
		}
		return campos; 
	}

/* Compara en que secciones se cumple la condicion indicada, imprime la posicion del primer
elemento de la submatriz 2x2 a eliminar y llama a "redimensionar" que se encargara de eliminarla =)
*/
	void condicionCero(int **mat, int *filas) {

		// estructura temporal para los elementos eliminados 
		ElemElim *elementos; 
		elementos = malloc(4*sizeof(ElemElim)); 
		if (elementos == NULL) {
			errorMemoria(); 
		}

		for (int i=0;i<N;i++) {
			for (int j=0;j<*(filas+i);j++)  {
				if (( *(*(mat+i)+j)  +  *(*(mat+i+1)+j)  +  *(*(mat+i)+j+1)  +  *(*(mat+i+1)+j+1) ) == 0) {
					printf("\n-> Se cumple la condicion en %d,%d",i,j); 

					/* Decidi cargar los valores de i y j en vez del valor del campo para evitar errores, 
					por ejemplo si existiese el mismo numero en la misma fila para que no se elimine dos veces
					como ocurrira haciendo una comparacion por valores. Ya que cada posicion en una matriz es unica. 
					*/
					elementos[0].i = i; 
					elementos[0].j = j; 

					elementos[1].i = i+1; 
					elementos[1].j = j; 

                    redimensionar(mat, &filas[i], i, elementos); 

					elementos[0].i = i; 
					elementos[0].j = j+1; 

					elementos[1].i = i+1; 
					elementos[1].j = j+1; 

                    redimensionar(mat, &filas[i], i, elementos); 

				}
			} 
		}
	}

/* Redimensiona las filas, una fila a la vez (por eso para borrar una submatriz 2x2 se le llama dos veces)
- carga los valores de la fila en un vector temporal 
- redimensiona el vector correspondiente a la fila ->(mat[fila]) 
- carga los datos que no han sido eliminados 
*/
    void redimensionar (int **mat, int *nroFilas, int fila, ElemElim *elementos) {

        int *temp; 
		temp = inicializarVectorTemporal(temp, mat, *nroFilas, fila); 

		*nroFilas = *nroFilas - 2; 
		mat[fila] =(int *) realloc(mat[fila] , *nroFilas); 

		if (mat!=NULL){
			int contadorFilas = 0; 
			for (int contadorVecTemp=0; contadorVecTemp<*nroFilas; contadorVecTemp++) {
				for (int contadorElementos = 0; contadorElementos<2; contadorElementos++) {
					if (elementos[contadorElementos].j == contadorVecTemp){
						*(*(mat+fila)+contadorFilas) = *(temp+contadorVecTemp); 
						contadorFilas++; 
					}
				}
			}
		} else {
			errorMemoria(); 
		}
		// Para ver qlq me carga en la fila lol 
		printf("\n Fila: "); 
			for (int i=0; i<*nroFilas; i++) {
				printf ("+ %d", *(*(mat+fila)+i)); 
			}  


    }

	int * inicializarVectorTemporal(int *temp, int **mat, int nroFilas, int fila){

		temp = malloc(sizeof(nroFilas)); 
		if (temp != NULL ){
			for (int i=0; i<nroFilas; i++) {
				*(temp+i) = *(*(mat+fila)+i); 
			}  
		} else {
			errorMemoria(); 
		}
		return temp; 
	}