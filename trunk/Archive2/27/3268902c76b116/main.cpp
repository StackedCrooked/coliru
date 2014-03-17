#include <emmintrin.h>
#include <stdio.h>

double dot_simple(  int n, double *a, double *b ){
    double dot = 0;
    for (int i=0; i<n; i++){ 
        dot += a[i]*b[i];
    }
    return dot;
}

/*
double dot_SSE(  int n, double *a, double *b ){
    const int VECTOR_SIZE = 4;
    typedef double double4 __attribute__ ((vector_size (sizeof(double) * VECTOR_SIZE)));
    double4 sum4 = {0};
    double4* a4 = (double4 *)a;
    double4* b4 = (double4 *)b;
    for (int i=0; i<n; i++){ 
        sum4 += *a4 * *b4 ;
        a4++; b4++;
        //sum4 += a4[i] * b4[i];
    }
    union {  double4 sum4_; double sum[VECTOR_SIZE]; };
    sum4_ = sum4;
    return sum[0]+sum[1]+sum[2]+sum[3];
}
*/

double dot_SSE(int n, double *a, double *b ) {
    __m128d sum2 = _mm_set1_pd(0.0);
	int i;
	for(i=0; i< (n & (-2)); i+=2) {
		__m128d a2 = _mm_loadu_pd(&a[i]);
		__m128d b2 = _mm_loadu_pd(&b[i]);
		sum2 = _mm_add_pd(_mm_mul_pd(a2, b2), sum2);
	}
	double out[2];
	_mm_storeu_pd(out, sum2);
	double dot = out[0] + out[1];
	for(;i<n; i++) dot +=a[i]*b[i]; 
	return dot;
}

double dot_double2(int n, double *a, double *b ) {
    typedef double double2 __attribute__ ((vector_size (16)));
	double2 sum2 = {};
	int i;
    double2* a2 = (double2*)a;
    double2* b2 = (double2*)b;
	for(i=0; i<(n/2); i++) {
	    sum2 += a2[i]*b2[i];
	}
	double dot = sum2[0] + sum2[1];
	for(i*=2;i<n; i++) dot +=a[i]*b[i]; 
	return dot;
}

double dot_double2_unroll2(int n, double *a, double *b ) {
    typedef double double2 __attribute__ ((vector_size (16)));
    double2 sum2_v1 = {};
    double2 sum2_v2 = {};
	int i;
    double2* a2 = (double2*)a;
    double2* b2 = (double2*)b;
	for(i=0; i<n/4; i++) {       
	    sum2_v1 += a2[2*i+0]*b2[2*i+0];
        sum2_v2 += a2[2*i+1]*b2[2*i+1];
	}
	double dot = sum2_v1[0] + sum2_v1[1] + sum2_v2[0] + sum2_v2[1];
	for(i*=4;i<n; i++) dot +=a[i]*b[i]; 
	return dot;
}

double dot_double4(int n, double *a, double *b ) {
    typedef double double4 __attribute__ ((vector_size (32)));
    double4 sum4 = {};
	int i;
    double4* a4 = (double4*)a;
    double4* b4 = (double4*)b;
	for(i=0; i<n/4; i++) {       
	    sum4 += a4[i]*b4[i];
	}
	double dot = sum4[0] + sum4[1] + sum4[2] + sum4[3];
	for(i*=4;i<n; i++) dot +=a[i]*b[i]; 
	return dot;
}

int main() {
	const int n = 101;
	double a[n];
	double b[n];
	for(int i=0; i<n; i++) {a[i] = i; b[i] = i;};
	printf("%f %f %f %f %f\n", dot_simple(n, a, b), dot_SSE(n, a, b), dot_double2(n,a,b), dot_double2_unroll2(n,a,b),dot_double4(n,a,b));
}