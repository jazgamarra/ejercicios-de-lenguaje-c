#include<stdio.h>
#include<stdlib.h>

//Convenciones
//Se varia el tamaño del pergamino
//Por defecto se encuentra asignado el mismo tamaño que el ejemplo
#define TAMANHO_PERGAMINO 6

//Existencia y No existencia
#define TRUE 1
#define FALSE 0

//Datos estructurados
typedef struct{
    short a[TAMANHO_PERGAMINO][TAMANHO_PERGAMINO];
    short nroApocalip;
    short cantRepeticiones;
}Pergamino;

typedef struct{
    short fila;
    short columna;
}Posicion;

typedef struct{
    short valor;
    Posicion pos;
}Resultado;

/*Prototipados*/
Resultado esApocaliptico(Pergamino *,Resultado,short,short,short);
void cargarPergamino(Pergamino *);
void mostrarPergamino(Pergamino *);
/*Funcion Principal*/
int main(void) {
    Pergamino p;
    Resultado r;
    p.nroApocalip = 6;
    p.cantRepeticiones = 3;
    //Habilitando la siguiente sección es posible buscar cualquier numero dentro del pergamino
    /*printf("Ingrese el numero que desea buscar: ");
    scanf("%hd",&p.nroApocalip);
    printf("Ingrese las veces que se repite '%hd'\n de manera sucesiva para que sea un Nro Apocaliptico\n",p.nroApocalip);
    scanf("%hd",&p.cantRepeticiones);*/

    cargarPergamino(&p); //Carga del Pergamino
    mostrarPergamino(&p);//Se muestra el pergamino ya cargado
    r = esApocaliptico(&p,r,0,TAMANHO_PERGAMINO-1,0); //Se busca el numero apocaliptico
    //Se muestran los resultados
    printf("Valor: %d\n",r.valor);
    printf("Posicion: %d.%d\n",r.pos.fila,r.pos.columna);
    return 0;
}

/*Funciones*/

//Funcion Recursiva esApocaliptico
/*OBS:
    1- i,j: son los indices del arreglo

    2- if (n == (per->cantRepeticiones-1))
        Se utiliza la expresión cantRepeticiones-1 ya que el contador comienza en 0*/

Resultado esApocaliptico(Pergamino *per,Resultado res, short i, short j, short n) {
    if (per->a[i][j] == per->nroApocalip) { //Se verifica si en la posicion existe un NRO_APOCALIPTICO
        if (n == (per->cantRepeticiones-1)) { //Cuando el NRO_APOCALIPTICO es encontrado de manera consecutiva
            res.valor = TRUE;
            res.pos.fila = i-(per->cantRepeticiones-1); //Se asigna la posicion de fila inicial
            res.pos.columna = j+(per->cantRepeticiones-1); //Se asigna la posicion de columna inicial
            return res; //Se retorna el resultado
        }else
            //Llamada recursiva, n+1 ya que se encontró el NRO_APOCALIPTICO
            esApocaliptico(per,res,i+1,j-1,n+1);
    }else{
        if (i < TAMANHO_PERGAMINO) { //Se verifica que la función hasta el NRO_COLUMNAS y NRO_FILAS definidas
            //LLamada recursiva a la siguiente posicion
            esApocaliptico(per,res,i+1,j-1,0);
        }else{ //En caso de recorrer todo el Pergamino sin encontrar el NRO_APOCALIPTICO
            res.valor = FALSE;  
            res.pos.fila = FALSE;
            res.pos.fila = FALSE;
            return res; //Se retorna el resultado negativo
        }
    }
}


void cargarPergamino(Pergamino *per) {
    for (short i = 0; i < TAMANHO_PERGAMINO; i++) {
        for (short j = 0; j < TAMANHO_PERGAMINO; j++) {
            printf("[%d][%d]: ",i,j);
            scanf("%hd",&per->a[i][j]);
        }
        printf("\n");
    }
}

void mostrarPergamino(Pergamino *per) {
    for (short i = 0; i < TAMANHO_PERGAMINO; i++) {
        for (short j = 0; j < TAMANHO_PERGAMINO; j++) {
            printf("%hd ",per->a[i][j]);
        }
        printf("\n");
    }
}
