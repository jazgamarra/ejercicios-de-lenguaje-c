#include<stdio.h>
#define N 100

int *ptrMatriz;
int n,leido;
int mayFila[N];
int mayColumna[N];
int primValRes,maxLis;
int cFil;
int cCol;
 
void hallarMayores(int i, int j,int mayor,int tipo){
    if (j >= 0 && j < n && i >= 0 && i < n){
		if(tipo==0){
			if(*(ptrMatriz+i*n+j)>mayor){
				mayor = *(ptrMatriz+i*n+j);
			}
			j++;
	        hallarMayores(i, j,mayor,tipo);
		}else{
			if(*(ptrMatriz+i*n+j)>mayor){
				mayor = *(ptrMatriz+i*n+j);
			}
			i++;
	        hallarMayores(i, j,mayor,tipo);			
		}
    }else{
		if(tipo==0){
	    	mayColumna[i]=mayor;
		}else{
    		mayFila[j]=mayor;
		}
	}
}

void imprimirVect(int arr[],int i){
    if (i < n){
		printf("%d\t",arr[i]);
		i++;
        imprimirVect(arr, i);
    }
}


int existe(int arr1[],int i,int num){
    if (i < n){
		if(arr1[i]==num+1){
			return arr1[i];
		}
		i++;
        existe(arr1,i, num);
    }else{
	    return -1;
	}
}

int buscarLista(int i,int e,int cele){
    if (i < n){
		int f = existe(mayFila,0,e);
		int c = existe(mayColumna,0,e);
		if(f!=-1){
			return buscarLista(i,f,cele+1);
		}else if(c!=-1){
			return buscarLista(i,c,cele+1);
		}else{
			return cele;
		}
	}		
}

void recoVect(int arr[],int i){
    if (i < n){
    	int val = buscarLista(0,arr[i],1);
		primValRes = (primValRes>val)?primValRes:arr[i];
		maxLis = (maxLis>val)?maxLis:val;
		i++;
        recoVect(arr, i);
    }
}



void obtenerLista(int i,int e,int cele){
    if (i < n){
		printf("%d ",e);
		int f = existe(mayFila,0,e);
		int c = existe(mayColumna,0,e);
		if(f!=-1){
			obtenerLista(i,f,cele+1);
		}else if(c!=-1){
			obtenerLista(i,c,cele+1);
		}
	}		
}

int main(){
	//debemos definir siempre n 
	n=4;
	int matriz[4][4] = {{15, 2,12, 8},
						{ 1,14,10, 5},
						{ 8, 9, 3,16},
						{11, 8, 6, 7}};
	cFil=0;
	cCol=0;
	primValRes=14;
	ptrMatriz = &matriz[0][0];
	if(n>2 && n<=100){
		hallarMayores(0,0,0,0);
		hallarMayores(1,0,0,0);
		hallarMayores(2,0,0,0);
		hallarMayores(3,0,0,0);
		hallarMayores(0,0,0,1);
		hallarMayores(0,1,0,1);
		hallarMayores(0,2,0,1);
		hallarMayores(0,3,0,1);
		imprimirVect(mayFila,0);
		printf("\n");
		imprimirVect(mayColumna,0);
		printf("\n");
		recoVect(mayFila,0);
		recoVect(mayColumna,0);
		obtenerLista(0,primValRes,1);
	}else{
		printf("La matriz no cumple con las reglas impuestas 2<N<=100\n");
	}
}

/*
void leerMat(int i,int j){
    if (j >= 0 && j < n && i >= 0 && i < n){
		scanf("%d",(ptrMatriz+i*n+j));
        if (j == n - 1){
            j = 0;
            i++;
        }else
            j++;
        leerMat(i, j);
    }
}

void printMat(int i, int j){
    if (j >= 0 && j < n && i >= 0 && i < n){
		printf("%d\t",*(ptrMatriz+i*n+j));
        if (j == n - 1){
            j = 0;
            i++;
            printf("\n");
        }else
            j++;
        printMat(i, j);
    }
}

*/