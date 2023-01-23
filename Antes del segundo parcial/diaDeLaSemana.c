#include <stdio.h>
#include <stdlib.h>

#define ANHO 2020 
int diaDeLaSemana (int d, int m); 

    int main(){
    int d,m;
    printf("Introduce un dia de la semana en numero: ");
    scanf("%d",&d);
    printf("Introduce un mes en numero: ");
    scanf("%d",&m);

    d = diaDeLaSemana(d,m); 
        // imprimo nomas pa saber 
        switch(d)
        {
            case 0:
                printf("Domingo\n");
                break;
            case 1:
                printf("Lunes\n");
                break;
            case 2:
                printf("Martes\n");
                break;
            case 3:
                printf("Miercoles\n");
                break;
            case 4:
                printf("Jueves\n");
                break;
            case 5:
                printf("Viernes\n");
                break;
            case 6:
                printf("Sabado\n");
                break;
        }

}

int diaDeLaSemana (int d, int m) {
    int bisiesto[]={0,3,4,0,2,5,0,3,6,1,4,6}; // 2008 fue bisiesto :p
    m=bisiesto[m-1];
    d=(((ANHO-1)%7)+((((ANHO-1)/4)-((3*(((ANHO-1)/100)+1))/4))%7)+m+(d%7))%7;
    return d; 
}