#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

/*
void foo(float *f, char*c, char c_thresh, const int n) {
    for (int i = 0; i < n; ++i) {
		if (c[i] < c_thresh) f[i] = 0.0f;
		else f[i] = 1.0f;
	} 
}

void foo2(float *f, char*c, char c_thresh, const int n) {
	for (int i = 0; i < n; ++i) {
		f[i] = (float)(c[i] >= c_thresh);
	}
}
*/
void foo3(float *f, float*c, float c_thresh, const int n) {
    for (int i = 0; i < n; ++i) {
		f[i] = (float)(c[i] >= c_thresh);
	}
}

void foo4(float *f, char*c, char c_thresh, const int n) {
    #pragma ivdep
    for ( int i = 0; i < n; ++i )
    {
        if ( c[i] < c_thresh ) f[i] = 0.0f;
        else                   f[i] = 1.0f;
    }
}

int main(void) {
	const int n = 256;
	//char c[n];
	//char c_thresh = 0;
    float cf[n];
	float cf_thresh = 0;    
	//for (int i = 0; i < n; i++) c[i] = i;
	float f1[n], f2[n] , f3[n];
	//foo(f1, c, c_thresh, n);
	//foo2(f2, c, c_thresh, n);
    foo3(f3, cf, cf_thresh, n);
	if (memcmp(f1, f2, 4*n) !=0) printf("error\n");

}