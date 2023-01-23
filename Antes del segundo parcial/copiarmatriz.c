//realizar un codigo que copie el contenido de una matriz en otra
#include<stdio.h>
#include<stdlib.h>
//prototipado
void dimensionar(int *,int *);
int *reservar(int ,int );
void cargarMatriz(int ,int,int ** );
void imprimirMatriz(int ,int, int **);
int *copiarMatriz(int ,int ,int **,int **);

int main(void){
    int fila,columna;
    int **m1;
    int **m2;
    dimensionar(&fila,&columna);
    m1=reservar(fila,columna);
    cargarMatriz(fila,columna,m1);
    imprimirMatriz(fila,columna,m1);
    m2=reservar(fila,columna);
    copiarMatriz(fila,columna,m1,m2);
    imprimirMatriz(fila,columna,m2);
    return 0;
}

void dimensionar(int *f,int *c){
    int tmpf,tmpc;
    printf("Ingrese la cantidad de filas:");
    scanf("%d",&tmpf);
    printf("ingrese la cantidad de columnas:");
    scanf("%d",&tmpc);
    *f=tmpf;
    *c=tmpc;
}

int *reservar(int f,int c){
    int **matriz;
    int i;
    matriz=(int**)malloc(f*sizeof(int*));
    if(matriz==NULL){
        printf("La memoria no pudo ser reservada");
        exit(1);
    }
    for(i=0;i<f;i++){
        matriz[i]=(int*)malloc(c*sizeof(int));
        if(matriz[i]==NULL){
            printf("no se ha podido reservar el espacio de memoria");
            exit(1);
        }
    }
    return matriz;
}

void cargarMatriz(int f,int c,int **matriz){
    int i,j;
    printf("ingrese los valores para la matriz:");
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            scanf("%d",&matriz[i][j]);
        } 
    }
    printf("\n");
}


void imprimirMatriz(int f,int c,int **matriz){
    int i,j;
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){
            printf("%d",*(*(matriz+i)+j));
        }
    printf("\n");
    }


}

int *copiarMatriz(int f,int c,int **m1,int **m2){
    int i,j;
    printf("\nla segunda matriz es:\n");
    for(i=0;i<f;i++){
        for(j=0;j<c;j++){ 
            *(*(m2+i)+j)=*(*(m1+i)+j);
            
        }
    }

    return m2;
}