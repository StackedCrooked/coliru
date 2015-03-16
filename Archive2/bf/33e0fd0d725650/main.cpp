#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int hatar=64;
    int t[64],i,zs,kerdes=20; /*hatar= az összes kérdés száma, kerdes a kiválasztandó kérdések száma*/
	for(i=0;i<hatar;t[i]=++i);
	for(i=hatar;i>0;i--){
		zs=rand()%i;
		t[i-1]^=t[zs];
		t[zs]^=t[i-1];
		t[i-1]^=t[zs];
	}
	for(i=0;i<kerdes;i++)
		printf("%d ",t[i]+1);
	return 0;
}