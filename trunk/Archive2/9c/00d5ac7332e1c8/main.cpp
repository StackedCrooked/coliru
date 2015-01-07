#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <float.h>

#include "instrset.h"

#ifdef _WIN32
    #define ADDAPI __declspec(dllexport)
#else
    #define ADDAPI
#endif

extern "C" void product32x32_fma(double *a, double *b, double *c, int n);
extern "C" void product32x32_avx(double *a, double *b, double *c, int n);
extern "C" void product32x32_sse(double *a, double *b, double *c, int n);
extern "C" void product64x64_fma(float *a, float *b, float *c, int n);
extern "C" void product64x64_avx(float *a, float *b, float *c, int n);
extern "C" void product64x64_sse(float *a, float *b, float *c, int n);

void product_dispatch(double *a, double *b, double *c, int n); 
void product_dispatch(float *a, float *b, float *c, int n); 

void (*fp_f)(float* a, float *b, float *c, int n) = product_dispatch;
void (*fp_d)(double* a, double *b, double *c, int n) = product_dispatch;

template <typename Type>
void triangle(Type *A, int n) {
    for (int j = 0; j < n; j++) {
		Type s = 0;
		for(int k=0; k<j; k++) s+= A[k*n+j]*A[k*n+j];
		//if((A[j * n + j] - s)<0) printf("asdf3 j %d, %f %f\n", j, A[j * n + j] - s, sqrt(A[j * n + j] - s));
		A[j*n+j] = sqrt(A[j*n+j] - s);
		Type fact = 1.0/A[j*n+j];
		for (int i = j+1; i<n; i++) {
			Type s = 0;
			for(int k=0; k<j; k++) s+=A[k*n+i]*A[k*n+j];
            A[j*n+i] = fact * (A[j*n+i] - s);
        }
	}
}

template <typename Type>
void block(Type *A, Type *B, int n) {	
	for (int j = 0; j <n; j++) {
		Type fact = 1.0/B[j*n+j];	
		for (int i = 0; i<n; i++) {
			Type s = 0;
			for(int k=0; k<j; k++) {
				s += A[k*n+i]*B[k*n+j];
			}
            A[j*n+i] = fact * (A[j*n+i] - s);
        }
	}
}

template <typename Type>
void product_bt(Type *A, Type *C, int n) {
	for(int i=0; i<n; i++) {
		for(int j=i; j<n; j++) {
			Type sum = 0;
			for(int k=0; k<n; k++) {
				sum += A[k*n+i]*A[k*n+j];
			}
			C[i*n+j] -= sum;	
		}
	}
}

template <typename Type>
void product_bb(Type *A, Type *B, Type *C, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			Type sum = 0;
			for(int k=0; k<n; k++) {
				sum+=A[k*n+i]*B[k*n+i];
			}
			C[j*i+j] -= sum;
		}
	}
}

template <typename Type>
void reorder(Type *A, Type *B, int n, int bs) {
	int nb = n/bs;
	int stride = bs*bs;
	//printf("%d %d %d\n", bs, nb, stride);
	#pragma omp parallel for schedule(static)
	for(int i=0; i<nb; i++) {
		for(int j=0; j<nb; j++) {
			for(int i2=0; i2<bs; i2++) {
				for(int j2=0; j2<bs; j2++) {
					B[stride*(nb*i+j) + bs*j2+i2] = A[n*bs*i + j*bs + n*i2 + j2];
				}
			}
		}
	}
}

template <typename Type>
void reorder_inverse(Type *A, Type *B, int n, int bs) {
	int nb = n/bs;
	int stride = bs*bs;
	//printf("%d %d %d\n", bs, nb, stride);
	#pragma omp parallel for schedule(static)
	for(int i=0; i<nb; i++) {
		for(int j=0; j<nb; j++) {
			for(int i2=0; i2<bs; i2++) {
				for(int j2=0; j2<bs; j2++) {
					B[n*bs*i + j*bs + n*i2 + j2] = A[stride*(nb*i+j) + bs*j2+i2];
				}
			}
		}
	}
}

template <typename Type>
void extend_matrix(Type *A, Type *B, int n, int n2) {
	#pragma omp parallel for schedule(static)
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			B[i*n2+j] = A[i*n+j];
		}
	}
}

template <typename Type>
void extend_matrix_inverse(Type *A, Type *B, int n, int n2) {
	#pragma omp parallel for schedule(static)
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			B[i*n+j] = A[i*n2+j];
		}
	}
}

int init() {	
	int iset = instrset_detect();
	if(iset==8) {
		fp_f = product64x64_fma;
		fp_d = product32x32_fma;
	}
	else if(iset==7) {
		fp_f = product64x64_avx;
		fp_d = product32x32_avx;
	}
	else {
		fp_f = product64x64_sse;
		fp_d = product32x32_sse;
	}
    int ncores = omp_get_max_threads();
    if(hasHyperThreading()) ncores/=2;
    omp_set_num_threads(ncores);
	return iset;
}

inline void product_dispatch(float *a, float *b, float *c, int n) {
	init();
	fp_f(a,b,c,n);
}

inline void product_dispatch(double *a, double *b, double *c, int n) {
	init();
	fp_d(a,b,c,n);
}

inline void product(float *a, float *b, float*c, int bs) {
	fp_f(a,b,c,bs);
}

inline void product(double *a, double *b, double*c, int bs) {
	fp_d(a,b,c,bs);
}

template <typename Type>
void cholesky_block(Type *A, int n) {
	//const int bs = 32;
	const int bs = sizeof(Type)==4 ? 64 : 32;
	const int n2 = (n+bs-1) & -bs;
	const int nb = n2/bs;
	Type *B = (Type*)_mm_malloc(sizeof(Type)*n2*n2,64);
	Type *tmp = (Type*)_mm_malloc(sizeof(Type)*n2*n2,64);
	extend_matrix(A,tmp,n,n2);
	int stride = bs*bs;
	reorder(tmp,B,n2,bs);
	for(int j=0; j<nb; j++) {
		#pragma omp parallel for schedule(static)
		for(int i=j; i<nb; i++) {
			for(int k=0; k<j; k++) {
				product(&B[stride*(nb*j+k)],&B[stride*(nb*i+k)],&B[stride*(nb*i+j)],bs);
			}
		}
		triangle(&B[stride*(nb*j+j)], bs);
		#pragma omp parallel for schedule(static)
		for(int i=j+1; i<nb; i++) { 		
			block(&B[stride*(nb*i+j)],&B[stride*(nb*j+j)],bs);
		}			
	}
	reorder_inverse(B,tmp,n2,bs);
	extend_matrix_inverse(tmp,A,n,n2);
	_mm_free(tmp);
	_mm_free(B);
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			A[i*n+j] = 0;
		}
	}
}

template <typename Type>
void backward_solve(Type *A, Type *x, Type *y, int n) {
	for (int i = n-1; i >=0 ; i--) {
        double sum = 0.0;
        for (int j = i+1; j < n; j++) {
			sum += A[i*n+j]*y[j];      
        }
		y[i] = (x[i] - sum)/A[i*n+i];
	}
}

template <typename Type>
void forward_solve(Type *A, Type *x, Type*y, int n) {
	for (int i = 0; i <n ; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
			sum += A[i*n+j]*y[j];      
        }
		y[i] = (x[i] - sum)/A[i*n+i];
	}
}

extern "C" ADDAPI void solve(double *A, double *x, double *y, int n) {
	cholesky_block(A,n);
	double *AT = (double*)_mm_malloc(sizeof(double)*n*n,64);	
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			AT[j*n+i] = A[i*n+j];
		}
	}

	double *y1 = (double*)_mm_malloc(sizeof(double)*n,64);
	for(int i=0; i<n; i++) y1[i] = 0;
	forward_solve(A, x, y1, n);
	backward_solve(AT, y1, y, n);
	_mm_free(AT);
	_mm_free(y1);
}

extern "C" ADDAPI void solvef(float *A, float *x, float *y, int n) {
	cholesky_block(A,n);
	float *AT = (float*)_mm_malloc(sizeof(float)*n*n,64);	
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			AT[j*n+i] = A[i*n+j];
		}
	}

	float *y1 = (float*)_mm_malloc(sizeof(float)*n,64);
	for(int i=0; i<n; i++) y1[i] = 0;
	forward_solve(A, x, y1, n);
	backward_solve(AT, y1, y, n);
	_mm_free(AT);
	_mm_free(y1);
}

extern "C" ADDAPI int get_iset() {
	return instrset_detect();
}

extern "C" ADDAPI void cholesky(double *A, int n) {
	cholesky_block(A,n);
}

extern "C" ADDAPI void choleskyf(float *A, int n) {
	cholesky_block(A,n);
}

extern "C" ADDAPI void cholesky_old(double *A, double *L, int n) {
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
}

inline double max(double a, double b) {
	return a>b ? a : b;
}

void find_gammaxi(double *A, int n, double &gamma, double &xi) {
	gamma = 0; xi = 0;
	for(int i=0; i<n; i++) {
		gamma = max(gamma, abs(A[i*n+i]));
		for(int j=0; j<n; j++) {
			if(j==i) continue;
			xi = max(xi, abs(A[i*n+j]));
		}
	}
}

/*
double machine_accuracy() {
	double machEps = 1.0;
    do {
       machEps /= 2.0;  
    }
    while ((double)(1.0 + (machEps/2.0)) != 1.0);
	return machEps;
}
*/

void find_deltabeta(double *A, int n, double &delta, double &beta) {
	double gamma, xi;
	double eps = DBL_EPSILON;
	find_gammaxi(A,n, gamma,xi);
	delta = eps*max(gamma+xi,1.0);
	beta = gamma;
	if(n>1) {
		beta = max(gamma, xi/sqrt(1.0*n*n-1.0)); 
	}
	beta = sqrt(max(beta,eps));
	return;
}

extern "C" ADDAPI void choleskymod(double *A, int n) {
	double delta, beta;	
	double *d = (double*)malloc(sizeof(double)*n);	
	memset(d, 0, sizeof(double)*n);
	find_deltabeta(A,n,delta,beta);	

	for(int j=0; j<n-1; j++) {
		for(int s=0; s<j; s++) {
			A[j*n+s] /= d[s];
		}
		double theta = 0.0;
		#pragma omp parallel for
		for(int i=j+1; i<n; i++) {
			double sum = 0;
			for(int s=0; s<j; s++) {
				sum += A[j*n+s]*A[i*n+s];
			}
			A[i*n+j] -= sum;
			theta = max(theta,abs(A[i*n+j]));
		}
		double thetaDivBeta = theta/beta;
		d[j] = max(max(abs(A[j*n+j]), thetaDivBeta*thetaDivBeta), delta);
		A[j*n+j] = 1.0;
		for(int i=j+1; i<n; i++) {
			A[i*n+i] -= A[i*n+j]*A[i*n+j]/d[j]; 
		}	
	}
	
	for(int s=0; s<n-1; s++) {
		A[n*n-n+s]/=d[s];
	}
	d[n-1] = max(abs(A[n*n-1]), delta);
	A[n*n-1] = 1.0;
	for(int i=0; i<n; i++) {
		d[i] = sqrt(d[i]);
		for(int j=0; j<i+1; j++) {
			A[i*n+j] *= d[j];
		}
		for(int j=i+1; j<n; j++) {
			A[i*n+j] = 0;
		}
	}
	free(d);
}
