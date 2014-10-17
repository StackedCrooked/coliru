#include <stdio.h>

int main (){
	
    int c;
    int k;
	double f;
	int i;
	
	i=0;
	printf("Eliga a que cambio de escala quiere, 1 para grados Fard, 2 para grados k\n");
	scanf("%d",&i);
	printf("Escriba el numero a converti\n");
	scanf("%d",&c);
	
	k=0;
	f=0;
	
	if(i==1){
		f=c*1.8+32;
          printf("djdjdj: %f\n", f);
          
	} else if (i==2){
		k=c+273;
          printf("djdjdj: %d\n", k);
	}
    
	
	return 0;
}

