/*Cree una estructura para almacenar los datos de un alumno con los siguientes campos
	cedula
	nombreAlumno
	nombreAsignatura
	fechaNacimiento (DD-MM-AAAA)
	notasParciales[3]
	notasFinales[2]

	Defina un estado para los casos en que no se rinde un tercer parcial (por alcanzar firma) y un estado por el cual ya no se rinde el segundo final por haber aprobado la materia.
	Cargue cada uno de los datos desde la entrada estándar (teclado) a excepción del nombre de la asignatura que es una constante con el valor "Algoritmica II".
	Utilice alias para todos los tipos de datos, ya sean simples o estructurados.
	Dada la estructura cargada proceda a calcular:
	Si se tiene o no firma.
	La nota final atendiendo la escala de calificaciones actual.
*/
#include <stdio.h> 
#define K 20 // longitud de las cadenas 
#define CANT_ALU 2 
typedef struct {
	long cedula; 
	char nombreAlumno[K]; 
	struct fecha {
		int dia, mes, ano; 
	}fechaNacimiento; 
	int notasParciales[3];
	int notasFinales[2];
	int tercerParcial; 
	int NOTA_FINAL;  
	
}REGISTRO;

int main () {
	
	REGISTRO alumnos[CANT_ALU]; // se declara el vector alumnos como variable de tipo REGISTRO 
	cargarDatos(&alumnos); 	// se leen los datos y se imprime la nota final 
	
	
	
} 

void cargarDatos (REGISTRO *ptr_alumnos) {
	
	int i, j, aux; 
	for (i=0; i<CANT_ALU; i++) {
		
		printf ("\n Introduzca la cedula del alumno: ");
			scanf("%ld", &(ptr_alumnos+i)->cedula ); 
		
		printf ("\n Introduzca el nombre del alumno: ");
			scanf("%s", (ptr_alumnos+i)->nombreAlumno ); 
		
		printf ("\n Introduzca la fecha de nacimiento en formato dd-mm-aaaa: ");
			scanf("%d-%d-%d", &(ptr_alumnos+i)->fechaNacimiento.dia, &(ptr_alumnos+i)->fechaNacimiento.mes, &(ptr_alumnos+i)->fechaNacimiento.ano  );
		
		for (j=0; j<2; j++) {
			printf ("\n Introduzca el puntaje del #%d parcial: ", j+1); 
				scanf("%d", &(ptr_alumnos+i)->notasParciales[j] );
		}
		
	// caso tercer parcial: se rinde un parcial y un final y ambos deben sumar 100. La nota siempre sera 2 sino se recursa
			
			if (((ptr_alumnos+i)->notasParciales[0] + (ptr_alumnos+i)->notasParciales[1])<100 ) {
				
				printf("\nLa suma de parciales es menor a 100. El alumno %s rindio un tercer parcial. ",  (ptr_alumnos+i)->nombreAlumno );
					printf("\nIngrese la nota del tercer parcial: ");
						scanf("%d", &(ptr_alumnos+i)->notasParciales[2] );
					
					printf("\nIngrese la nota del examen final: ");
						scanf("%d", &(ptr_alumnos+i)->notasFinales[1] );
						
						int tercerParcial = 1; // centinela para saber si rindio tercer parcial
						
						aux = (ptr_alumnos+i)->notasFinales[1] + (ptr_alumnos+i)->notasParciales[2]; 
			
							if (aux>100) {							// si hace mas de 100 pasa con 2  sino recursa 
								(ptr_alumnos+i)->NOTA_FINAL=2;  	
							} else {	
								(ptr_alumnos+i)->NOTA_FINAL=1;  
							}
						printf("\nLa nota final es %d", (ptr_alumnos+i)->NOTA_FINAL);
			}
			 
	// caso regular: si la suma es mayor a 100 se rinden ambos finales 
			
			if (((ptr_alumnos+i)->notasParciales[0] + (ptr_alumnos+i)->notasParciales[1]) > 100 ) {
				
					printf("\nIngrese la nota del primer final: ");
						scanf("%d", &(ptr_alumnos+i)->notasFinales[0] );
					
					printf("\nIngrese la nota del segundo final: ");
						scanf("%d", &(ptr_alumnos+i)->notasFinales[1] );
						
					int tercerParcial = 0; 		
					
						/* Escala de nota final: 
						90% es 5 
						80% es 4 
						70% es 3 
						60% es 2 
						*/

					
					aux = ((ptr_alumnos+i)->notasFinales[0]+(ptr_alumnos+i)->notasFinales[1]) /2; 
					if (aux<60) {
						(ptr_alumnos+i)->NOTA_FINAL=1;   
					}
					if ((aux>=60)&&(aux<70)) {
						(ptr_alumnos+i)->NOTA_FINAL=2;   
					}
					if ((aux>=70)&&(aux<80)) {
						(ptr_alumnos+i)->NOTA_FINAL=3;   
					}
					if ((aux>=80)&&(aux<90)) {
						(ptr_alumnos+i)->NOTA_FINAL=4;   
					}
					if (aux>=90) {
						(ptr_alumnos+i)->NOTA_FINAL=5;   
					}	
					printf("\nLa nota final es %d \n \n ", (ptr_alumnos+i)->NOTA_FINAL);

			} 
	}	
}

