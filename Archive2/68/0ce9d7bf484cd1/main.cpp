#include <iostream>
using namespace std;
int main(){
    int array[1002][1002];
    int cases, height, width, i, j, k, max, total;
	cin >> cases;
	for(i=0; i<cases; ++i){
		cin >> height>> width;
	   for(j=0; j<height; ++j){
		   for(k=0; k<width; ++k){
		   	cin >> array[j][k];
		   }
	   }
	   max = array[height-1][width-1];
	   for(j=0; j<height; ++j){
		 for(k=0; k<width; ++k){
				 total = 0;
				 for(int l=j; l<height; l++){
					 for (int g=k; g<width; g++){
						 total += array[l][g];
					 }
				 }
				 if(total>max)
				 max = total;
		 
		 }
	   }
	   cout << max;
	   
   }
	return 0;
}