#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    const int n = 1000;
	int y[n];
	int sum;
	int a = 51;
	for(int i=0; i<n; i++) y[i] = rand();

	sum = 0;	
	for(int i=0; i<n; i++) {
		sum = (sum%a + y[i]%a)%a;
	}
	printf("sum %d\n", sum);
	
	sum = 0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0; i<n; i++) {
		sum += y[i]%a;
	}
	sum%=a;
	printf("sum %d\n", sum);
}