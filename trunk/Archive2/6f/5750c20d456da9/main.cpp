#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

extern "C" void cholesky_dll(double *A, double *L, int n);

void gemm_ATA(double *A, double *C, int n) {
    for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			double sum = 0;
			for(int k=0; k<n; k++) {
				sum += A[i*n+k]*A[j*n+k];
			}
			C[i*n+j] = sum;
		}
	}
}


double *cholesky(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);
 	
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (i+1); j++) {
            double s = 0;
            for (int k = 0; k < j; k++) {
                s += L[i * n + k] * L[j * n + k];
			}
            L[i * n + j] = (i == j) ? sqrt(A[i * n + i] - s) : (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
	}
    return L;
}

double *cholesky3(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);
 	
	for (int j = 0; j <n; j++) {
		//#pragma omp parallel for
		for (int i = j; i <n; i++) {
            double s = 0;
            for (int k = 0; k < j; k++) {
                s += L[i * n + k] * L[j * n + k];
			}
            L[i * n + j] = (i == j) ? sqrt(A[i * n + i] - s) : (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
	}
    return L;
}

double inner_sum(double *li, double *lj, int n) {
	double s = 0;
	for (int i = 0; i < n; i++) {
		s += li[i]*lj[i];
	}
	return s;
}

double inner_sum3(double *li, double *lj, int n) {
	double s1 = 0, s2 = 0, s3 = 0;
	int i;
	for (i = 0; i < (n &(-3)); i+=3) {
		s1 += li[i]*lj[i+0];
		s2 += li[i+1]*lj[i+1];
		s3 += li[i+2]*lj[i+2];
	}
	double sum = 0;
	for(;i<n; i++) sum += li[i]* lj[i+0];
	sum += s1 + s2 + s3;
	return sum;
}

double *cholesky4(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);
 	
	for (int j = 0; j <n; j++) {
		
		double s = 0;
        for (int k = 0; k < j; k++) {
			s += L[j * n + k] * L[j * n + k];
		}
		L[j * n + j] = sqrt(A[j * n + j] - s);
		#pragma omp parallel for
		for (int i = j+1; i <n; i++) {
            double s = 0;
            for (int k = 0; k < j; k++) {
                s += L[i * n + k] * L[j * n + k];
			}
            L[i * n + j] = (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
	}
    return L;
}

double *cholesky5(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);
 	
	for (int j = 0; j <n; j++) {
		double s = inner_sum(&L[j * n], &L[j * n], j);
		L[j * n + j] = sqrt(A[j * n + j] - s);
		#pragma omp parallel for schedule(static, 8)
		for (int i = j+1; i <n; i++) {
            double s = inner_sum(&L[j * n], &L[i * n], j);
            L[i * n + j] = (1.0 / L[j * n + j] * (A[i * n + j] - s));
        }
	}
    return L;
}

double *cholesky2(double *A, int n) {
    double *L = (double*)calloc(n * n, sizeof(double));
    if (L == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++) {
		double s = 0;
        for (int k = 0; k < i; k++) {
            s += L[k * n + i] * L[k * n + i];		
		}
		L[i * n + i] = sqrt(A[i * n + i] - s);
		#pragma omp parallel for
		for (int j = i+1; j < n; j++) {		
            double s = 0;
            for (int k = 0; k < i; k++) {
                s += L[k * n + i] * L[k * n + j];
				
			}
            L[i * n + j] = (1.0 / L[i * n + i] * (A[i * n + j] - s));			
        }
	}
	
    return L;
}

void show_matrix(double *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%2.5f ", A[i * n + j]);
        printf("\n");
    }
}
 
int main() {
    int n = 3;
	
    double m1[] = {25, 15, -5,
                   15, 18,  0,
                   -5,  0, 11};
    double *c1 = cholesky(m1, n);
    show_matrix(c1, n);
    free(c1);
 
    n = 4;
    double m2[] = {18, 22,  54,  42,
                   22, 70,  86,  62,
                   54, 86, 174, 134,
                   42, 62, 134, 106};
 
	
	printf("\n");	
	double *c2 = cholesky4(m2, n);
    show_matrix(c2, n);
	free(c2);
	
	n = 1000;
	double *m3 = (double*)malloc(sizeof(double)*n*n);
	for(int i=0; i<n; i++) {
		for(int j=i; j<n; j++) {
			double element = 1.0*rand()/RAND_MAX;
			m3[i*n+j] = element;
			m3[j*n+i] = element;

		}
	}
	double *m4 = (double*)malloc(sizeof(double)*n*n);
	gemm_ATA(m3, m4, n); //make a positive-definite matrix
	printf("\n");
	//show_matrix(m4,n);

	double dtime;
	
	double *c3 = cholesky4(m4, n); //warm up OpenMP
	free(c3);

	dtime = omp_get_wtime();
	c3 = cholesky(m4, n);
	dtime = omp_get_wtime() - dtime;
	printf("dtime %f\n", dtime);

	dtime = omp_get_wtime();
	double *c4 = cholesky5(m4, n);
	dtime = omp_get_wtime() - dtime;
	printf("dtime %f\n", dtime);
	printf("%d\n", memcmp(c3, c4, sizeof(double)*n*n));
	//show_matrix(c3,n);
	printf("\n");
	//show_matrix(c4,n);
	//for(int i=0; i<100; i++) printf("%f %f %f \n", m4[i], c3[i], c4[i]);
	/*

	double *l = (double*)malloc(sizeof(double)*n*n);
	dtime = omp_get_wtime();
	cholesky_dll(m3, l, n);
	dtime = omp_get_wtime() - dtime;
	printf("dtime %f\n", dtime);
	*/
	//printf("%d\n", memcmp(c3, c4, sizeof(double)*n*n));
	//for(int i=0; i<100; i++) printf("%f %f %f \n", m3[i], c3[i], c4[i]);

	//free(c3);
	//free(c4);
	//free(m3);
	
    return 0;
	
}