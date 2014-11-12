#include <stdio.h>
#include <emmintrin.h>                 // SSE2
#include <omp.h>

inline void 
    __attribute__ ((gnu_inline))        
    __attribute__ ((aligned(16))) mult2by2B(        
            const double* __restrict A,
            const double* __restrict B,
            double* __restrict C
        )

    {

    register __m128d xmm0, xmm1, xmm2, xmm3, xmm4;
    xmm0 = _mm_load_pd(C);
    xmm1 = _mm_load1_pd(A);
    xmm2 = _mm_load_pd(B);
    xmm3 = _mm_load1_pd(A + 1);
    xmm4 = _mm_load_pd(B + 2);
    xmm1 = _mm_mul_pd(xmm1,xmm2);
    xmm2 = _mm_add_pd(xmm1,xmm0);
    xmm1 = _mm_mul_pd(xmm3,xmm4);
    xmm2 = _mm_add_pd(xmm1,xmm2);
    _mm_store_pd(C,xmm2);

    xmm0 = _mm_load_pd(C + 2);
    xmm1 = _mm_load1_pd(A + 2);
    xmm2 = _mm_load_pd(B);
    xmm3 = _mm_load1_pd(A + 3);
    //xmm4 = _mm_load_pd(B + 2);
    xmm1 = _mm_mul_pd(xmm1,xmm2);
    xmm2 = _mm_add_pd(xmm1,xmm0);
    xmm1 = _mm_mul_pd(xmm3,xmm4);
    xmm2 = _mm_add_pd(xmm1,xmm2);
    _mm_store_pd(C + 2,xmm2);
}

int main() {
  double A[4], B[4], C[4];
  int maxiter = 10000000;
  //int maxiter = 1000000000;
  double dtime;
  dtime = omp_get_wtime();
  for(int i = 0; i < maxiter; i++){
        mult2by2B(A,B,C);
        C[0] = 0.0; C[1] = 0.0; C[2] = 0.0; C[3] = 0.0;
  }
  dtime = omp_get_wtime() - dtime;
  printf("%f %f %f %f\n", C[0], C[1], C[2], C[3]);
  //gflops = (double) (2.0*n*n*n)/time3/1.0e9*maxiter;
  printf("time %f\n", dtime);
}