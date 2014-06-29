#include <iostream>
#include<iomanip>
using namespace std;
int main(){
    int array[1000][1000];
	int cases, height, width, i, j, k;
	cin >> cases;
	for(i=0; i<cases; ++i){
		cin >> height>> width;
	   for(j=0; j<height; ++j){
		   for(k=0; k<width; ++k){
		   	cin >> array[j][k];
		   }
	   }
   }
	return 0;
}