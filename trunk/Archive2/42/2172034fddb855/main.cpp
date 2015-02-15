#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int N,R,i,j,l=0,c=0,k=0,s=0;
	int a;
	char pilha[1000];
	scanf("%d %d",&N,&R);
	for(i=0;i<R;i++){
		scanf("%d",&a);
		pilha[a]='.';
	}
	
	while(l!=0){
		for(s=0;s<R;s++){
			if(pilha[s]=='.'){
				if(s-1>=0){
					pilha[s--]='.';
				}
				if(s+1<R){
				pilha[s++]='.';
				}
				s=s+2;
			}
			
		}
		
		for(j=0;j<R;j++){
		if(pilha[j]=='.'){
			c++;
		}
		}
	if(c==R-1){
		printf("%d\n",k);
		c=0;
	}
	
	}
	
	
	
	
	
	
	
	
	
	
	return 0;
}
