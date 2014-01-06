#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>
#include <string>
#include <typeinfo>

#include <stdio.h>
#include <stdlib.h>

long long arr[2];
long long xyz(int from, int to, int i);
long long array[200000];
long long xyz2(int from, int to, int i);

long long foo(){return 141;}

int main(){
	arr[0] = -4;
	arr[1] = 5;
	xyz(0, 1, 0);
	printf("\n\n");
	xyz2(0, 1, 0);
	return 0;
}

long long xyz2(int from, int to, int i){
	if(from==to){
		return arr[to];
	}else{
		int mid = (from+to)/2;
		array[i*2+1] = xyz2(from, mid, i*2+1);
		array[i*2+1] = foo();
		printf("%d %d\n", (i*2)+1, i);
		return 100000;
	}
}

long long xyz(int from, int to, int i){
	if(from==to){
		return arr[to];
	}else{
		int mid = (from+to)/2;
		array[i*2+1] = xyz(from, mid, i*2+1);
		//stsuffix[i*2+1] = foo();
		printf("%d %d %d\n",array[i*2+1], (i*2)+1, i);
		return 100000;
	}
}