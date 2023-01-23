/*Correcciones del profe: 
x- No se sigue las convenciones para el uso de la variable N 
x- Posibles efectos colaterales con la variable global N 
- Para ordenar le vector se pudo haber utilizado qsort 
x- No se devuelven las estadisticas mediante una funcion como se solicita 
- Para la mediana no se tiene en cuenta si es par o impar 
x- No se verifica el resultado de malloc ni se controla lo enviado al free 

Correcciones mias: 
x- Prototipado 
- Moda de una manera mas eficiente
x- La funcion estadisticas llama a las funciones y imprime los resultados 

POR HACER 
Mediana y moda*/

#include <stdio.h>
#include <stdlib.h> 

// PROTOTIPOS 
	int *cargarDatos(int *vector, int *indice); 
	void imprimirVector (int *vector, int *indice); 
	void estadisticas (int *vector, int *indice); 
		float mediaAritmetica (int *vector, int *indice); 
		int moda (int *vector, int *indice); 

// MAIN 
int main () { 

	int *vector, *indice; 
	vector = cargarDatos(vector, indice); 

	printf("\nEl vector ingresado es = "); 
	imprimirVector(vector, indice); 

	estadisticas (vector, indice); 
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
la funcion cargarDatos compone un ciclo while que mientras el usuario no introduzca el centinela 0, continuará redimensionando el vector para 
poder seguir cargando datos enteros.
 */
int *cargarDatos(int *vector, int *indice) {

	// iniciamos el contador en cero y asignamos espacio a vevctor con malloc asi despues podemos redimensionarlo con malloc  
	int i=0;  vector = malloc(sizeof(int)); 
	*(vector) = 7; // Asigno un numero distinto a cero para asegurar que entre la while  

	// si se logro reservar el espacio con malloc ... 
	if (vector != NULL) {

		// Ciclo while: leerá nuevos datos mientras != 0 
		while (*(vector+i-1) != 0 || i==0 ) { // se compara de esta manera porque queremos que compare con el valor de antes de aumentar el contador 
			
			vector = realloc(vector, (i+1)*sizeof(int));
			
			// si se logro redimensionar el vector... 
			if (vector != NULL) {

				// carga de datos 
				printf("\nPor favor ingrese un numero: "); 
				scanf("%d", (vector+i)); 
				printf("\nEl dato es %d ", *(vector+i)); 

			} else {
				printf("\nError en la asignacion de memoria. Intente mas tarde "); 
			}
			i++; 
		}
	}
	*indice = i-1; // hacemos -1 para omitir el cero y que no se guarde 
	return vector;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
La funcion imprimirVector imprime el vector que sea recibido como parámetro */
void imprimirVector (int *vector, int *indice) {

	int i; 	
	for (i=0; i<*indice; i++) {
		printf("  %d  |", *(vector+i)); 
	}
}

void estadisticas (int *vector, int *indice) {

	printf("\nLa media aritmetica es: %2f", mediaAritmetica(vector, indice)); 
	printf("\nLa moda es: %d", moda(vector, indice)); 

}

float mediaAritmetica (int *vector, int *indice) {
	float mediaArit = 0; 
	int i; 
	for (i=0; i<*indice; i++) {
		mediaArit = mediaArit+ *(vector+i); 
	}
	mediaArit=mediaArit / *indice; 
	return mediaArit; 
}
int moda (int *vector, int *indice) {

	typedef struct { 
		int dato; 
		int ocurrencia; 
	} STRUCT_MODA; 

	STRUCT_MODA *moda; 
	moda = (STRUCT_MODA*) malloc (*indice * sizeof(STRUCT_MODA)); // voy a reservar mas espacio del que necesito pero voy a liberar desp 
	
	int i; int j; int contadorAuxiliar = 0; 

	
	for (i=0; i<*indice; i++) {
		for (j=0; j<contadorAuxiliar; j++) {
			
		 }  
	}

		for (i=0; i<*indice; i++) {
		printf("Dato %d Ocurrencia %d", (moda+i)->dato,(moda+i)->ocurrencia ); 
}
}