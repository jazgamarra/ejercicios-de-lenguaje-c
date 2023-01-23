/*
Jazmin Gamarra 
Desarrollado con el compañero Manu Sosa 
*/

#include<stdio.h>
#include <math.h>
#define PI 3.14
double Carga_de_Dato(double *n, double *a, double *b);
double Sumatoria(double n, double a, double b);
double Productoria1(double n, double a);
double Productoria2(double n, double a);
double Coseno(double n, double b);
double Valor_de_X(double n, double a, double b);
void Imprimir();
int main(void)
{
    double n;
    double a,b,x, valorDeX=0;
    Carga_de_Dato(&n,&a,&b);
    Sumatoria(n, a,b);
    Productoria1(n,a);
    Productoria2(n,a);
    Coseno(n,b);
    valorDeX=Valor_de_X(n, a,b);
    Imprimir(valorDeX);
    
    
}
double Carga_de_Dato(double *n, double *a, double *b)
{
    printf("Cantidad de repeticiones: ");
    scanf("%lf", &*n);
    printf("Valor de a: ");
    scanf("%lf", &*a);
    printf("Valor de b:");
    scanf("%lf", &*b);
}
double Sumatoria(double n, double a, double b)
{
    double sumatoria=0;
    for(int i=1;i<=n ; i++)
    {
        sumatoria+=pow((a-b),i)-3;
    }
    return sumatoria;
}
double Productoria1(double n, double a)
{
    double productoria=1;
    for(int i=2; i<=n-1 ; i++)
    {
        productoria*=(2+a*(i-1));
    }
    return productoria;
   
}
double Productoria2(double n, double a)
{
    double productoria2=1;

    for(a=1; a<=n; a++)
    productoria2*=a;
    return productoria2;
   
}
double Coseno(double n, double b)
{
    double coseno=0;
    coseno=((2*b-1)*PI)/2*n;
    if(coseno < 0){
        coseno*=-1;
    }
    return coseno;
}
double Valor_de_X(double n, double a, double b)
{
    double x=0;
    x=((Sumatoria(n,a,b)+n)/Productoria1(n,a))+(pow(2,n-1)*Productoria2(n,a))-cos(Coseno(n,b));
    return x;
}
void Imprimir(double valorDeX)
{
    printf("El valor de x es: %lf", valorDeX);
}