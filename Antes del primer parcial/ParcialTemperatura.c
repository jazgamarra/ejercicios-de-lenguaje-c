/*Implemente un programa que permita al usuario registrar la temperatura minima, la maxima y la fecha correspondiente a dicha jornada en el formato dd-mm-aaaa. 
Se debera brindar la opcion de seguir cargando la lista de registros como asi estas opciones: 

ingrese una opcion 
- agregar registro 
- eliminar registro // nuse como hacer sin lista enlazada 
- listar registros
- imprimir estadisticas 
- salir  

estadisticas 
- temperatura promedio 
- mayor variabilidad entre la minima y maxima temperatura 
- el dia mas caluroso y el mas frio 

se debe llevar a cabo a traves de asignacion dinamica de memoria*/ 
  
  
  /* ----------------------------------------------------------
  NOTA: 
  Para que quede mejor le faltaria una validacion para que la maxima no sea menor q la minima, una validacion para que las temperaturas no sean absurdamente altas, validacion para que las fechas tengan años razonables etc. 
  No termine la parte de estadisticas pq me canse xd 
  Jazmin Gamarra 
  29/03/2022 
    ----------------------------------------------------------*/
  
  #include <stdio.h> 
  #include <stdlib.h>
  
  #define TRUE 1
  #define MAXIMO 60
  #define MINIMO -80
  
  int N; // longitud del vector de registros 
  
typedef struct {
	float tempMinima; 
  	float tempMaxima; 
  	struct f{
  		int dia,mes,ano; 
	  }fecha; 
  } REGISTRO ; 
  
void agregarRegistro(REGISTRO *ptr1) {
  printf("\n\tIngrese la fecha de hoy en el formato dd-mm-aaaa: "); 
  	scanf("%d-%d-%d", &(ptr1+N-1)->fecha.dia, &(ptr1+N-1)->fecha.mes, &(ptr1+N-1)->fecha.ano); 
  printf("\n\tIngrese la temperatura minima de hoy: "); 
  	scanf("%f", &(ptr1+N-1)->tempMinima); 
  printf("\n\tIngrese la temperatura maxima de hoy: "); 
 	 scanf("%f", &(ptr1+N-1)->tempMaxima); 
  		
  		// valido que la temperatura maxima sea mayor a la minima ingresada para no generar errores mas adelante 
  		while ( (ptr1+N-1)->tempMaxima < (ptr1+N-1)->tempMinima) {
  			printf("\n\t ERROR: La temperatura maxima introducida es menor a la minima. Por favor, intentelo de nuevo.\n Temperatura maxima: "); 
 				scanf("%f", &(ptr1+N-1)->tempMaxima);
		  }
		
			
	
}  

void listarRegistros (REGISTRO *ptr1) {
  	printf("\nSe listaran todos los registros disponibles actualmente \n ");
	int i; 
	for (i=0; i<N-1; i++) {
		printf("\n\nRegistro del dia %d/%d/%d ", (ptr1+i)->fecha.dia, (ptr1+i)->fecha.mes, (ptr1+i)->fecha.ano); 
		printf("\n\tLa temperatura minima fue de: %.2f", (ptr1+i)->tempMinima); 
		printf("\t\tLa temperatura maxima fue de: %.2f", (ptr1+i)->tempMaxima); 			
	}			

}

void estadisticas (REGISTRO *ptr1) {
	
	//temperatura promedio 
		float promedio = 0; int i; 

		for (i=0; i<N-1; i++) { 
			promedio = promedio + (((ptr1+i)->tempMinima+(ptr1+i)->tempMaxima)/2); 
		} 
		promedio = promedio / (N-1); 
		printf ("\n\tLa temperatura promedio entre todos los registros es: %.2f", promedio);
		
	//dia mas caluroso 
		int temperatura=0, posicion; 
		for (i=0; i<N; i++) { 
			if ((ptr1+i)->tempMaxima > temperatura) {
				temperatura=(ptr1+i)->tempMaxima; 
				posicion=i; 
			}
		} 
		printf ("\n\tEl dia mas caluroso fue el %d/%d/%d con una temperatura de %d", (ptr1+posicion)->fecha.dia, (ptr1+posicion)->fecha.mes, (ptr1+posicion)->fecha.ano, temperatura);

}
  
  int main (){
		int opcion = 1; 
  		
  		
  		// inicializo mi vector de estructuras fuera del while 
  		N = 1; 
		REGISTRO *puntero;
		puntero = malloc(N * sizeof(REGISTRO)); 
	
		
  		while (opcion != 0) {
		
			printf("\n--------------------------------\nIngrese 1 si desea cargar algun registro. \n* 2 si desea listar los registros disponibles\n* 3 si desea ver las estadisticas\n0 si desea salir: \n");  
			scanf("%d", &opcion); 
				if (opcion == 0) {
				printf("\nSe cerrara el programa");  
				return -1; 
				} 
				
				if (opcion == 1) {
					agregarRegistro(puntero); 
	        		N=N+1;
					puntero=realloc(puntero, N*sizeof(REGISTRO)); // se redimensiona 
				}
				
				if (opcion == 2) {
					listarRegistros(puntero);
				} 
				if (opcion == 3) {
					estadisticas(puntero); 
				}
	
		
		
		}
  }
  
 
  

