#include <stdio.h>
#include <math.h>

int main(void){
  
      float i,h=0.5,s=-6.0,e=6.0;
  	long double y1,y2,x1,x2,A=0.0,I;

  	for(i=s;i<=e;){
    	x1=i;
    	x2=i+h;
    	y1=exp(-x1*x1);
    	y2=exp(-x2*x2);
    	A=A+h*(y1+y2)/2.0;
    	i=i+h;
  	}

	I=sqrt(M_PI);
  	printf("A=%.16Lf\n",A);
	printf("I=%.16Lf\n",I);
	printf("|delta|=%.16Lf\n",fabsl(I-A));

  	return(0);
}