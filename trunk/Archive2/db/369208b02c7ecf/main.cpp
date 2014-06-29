#include <iostream>
using namespace std;
int main(){
    int array[2000][2000];
	int cases, height, width, i, j, k;
	cin>> cases>> height>> width;
	for(i=0; i<cases; ++i){
	   for(j=0; j<height; ++j){
		   for(k=0; k<width; ++k){
		   	cin>> array[j][k];
		   }
	   }
   }
	return 0;
}