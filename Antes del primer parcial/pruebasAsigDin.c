  #include <stdio.h> 
  #include <stdlib.h> 
  #define N 3 



  int main () {
  	
  	int *ptr1 = NULL; 					 
  	ptr1=calloc(N, sizeof(int)); 
  	
  	if (ptr1 != NULL) {
  		
  		imprimirVector1(ptr1); 
  	
	  } else {
	printf("error"); 
	return -1; 
	  }
  	
  }
  
 void imprimirVector1 (int V[]) {
 	int i;  
 	for (i=0; i<N; i++) {
 		printf("%d	", V[i]); 
	 }
 
 }
 
 
