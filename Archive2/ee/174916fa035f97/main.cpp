#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void transpose(double *A, double *B, int n) {
    int i,j;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			B[j*n+i] = A[i*n+j];
		}
	}
}

void gemm(double *A, double *B, double *C, int n) 
{	
	int i, j, k;
	for (i = 0; i < n; i++) { 
		for (j = 0; j < n; j++) {
			double dot  = 0;
			for (k = 0; k < n; k++) {
				dot += A[i*n+k]*B[k*n+j];
			} 
			C[i*n+j ] = dot;
		}
	}
}

void gemm_omp(double *A, double *B, double *C, int n) 
{	
	#pragma omp parallel
	{
		int i, j, k;
		#pragma omp for
		for (i = 0; i < n; i++) { 
			for (j = 0; j < n; j++) {
				double dot  = 0;
				for (k = 0; k < n; k++) {
					dot += A[i*n+k]*B[k*n+j];
				} 
				C[i*n+j ] = dot;
			}
		}
		
	}
}

void gemmT(double *A, double *B, double *C, int n) 
{	
	int i, j, k;
	double *B2;
	B2 = (double*)malloc(sizeof(double)*n*n);
    transpose(B,B2, n);
	for (i = 0; i < n; i++) { 
		for (j = 0; j < n; j++) {
			double dot  = 0;
			for (k = 0; k < n; k++) {
				dot += A[i*n+k]*B2[j*n+k];
			} 
			C[i*n+j ] = dot;
		}
	}
	free(B2);
}

void gemmT_omp(double *A, double *B, double *C, int n) 
{	
	double *B2;
	B2 = (double*)malloc(sizeof(double)*n*n);
    transpose(B,B2, n);
	#pragma omp parallel
	{
		int i, j, k;
		#pragma omp for
		for (i = 0; i < n; i++) { 
			for (j = 0; j < n; j++) {
				double dot  = 0;
				for (k = 0; k < n; k++) {
					dot += A[i*n+k]*B2[j*n+k];
				} 
				C[i*n+j ] = dot;
			}
		}
		
	}
	free(B2);
}

int main() {
	int i, n;
	double *A, *B, *C, dtime;

	n=512;
	A = (double*)malloc(sizeof(double)*n*n);
	B = (double*)malloc(sizeof(double)*n*n);
	C = (double*)malloc(sizeof(double)*n*n);
	for(i=0; i<n*n; i++) { A[i] = rand()/RAND_MAX; B[i] = rand()/RAND_MAX;}

	dtime = omp_get_wtime();
	gemm(A,B,C, n);
	dtime = omp_get_wtime() - dtime;
	printf("%f\n", dtime);

	dtime = omp_get_wtime();
	gemm_omp(A,B,C, n);
	dtime = omp_get_wtime() - dtime;
	printf("%f\n", dtime);

	dtime = omp_get_wtime();
	gemmT(A,B,C, n);
	dtime = omp_get_wtime() - dtime;
	printf("%f\n", dtime);

	dtime = omp_get_wtime();
	gemmT_omp(A,B,C, n);
	dtime = omp_get_wtime() - dtime;
	printf("%f\n", dtime);
    
    return 0;

}