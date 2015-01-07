#include <immintrin.h>

extern "C" void product32x32_avx(double *a, double *b, double *c, int n) 
{
    for(int i=0; i<n; i++) {	
		__m256d t1 = _mm256_loadu_pd(&c[i*n +  0]);
		__m256d t2 = _mm256_loadu_pd(&c[i*n +  4]);
		__m256d t3 = _mm256_loadu_pd(&c[i*n +  8]);
		__m256d t4 = _mm256_loadu_pd(&c[i*n + 12]);
		__m256d t5 = _mm256_loadu_pd(&c[i*n + 16]);
		__m256d t6 = _mm256_loadu_pd(&c[i*n + 20]);
		__m256d t7 = _mm256_loadu_pd(&c[i*n + 24]);
		__m256d t8 = _mm256_loadu_pd(&c[i*n + 28]);
		for(int k=0; k<n; k++) {
			__m256d a1 = _mm256_set1_pd(a[k*n+i]);
			
			__m256d b1 = _mm256_loadu_pd(&b[k*n+0]);
			t1 = _mm256_sub_pd(t1,_mm256_mul_pd(a1,b1));
			
			__m256d b2 = _mm256_loadu_pd(&b[k*n+4]);
			t2 = _mm256_sub_pd(t2,_mm256_mul_pd(a1,b2));

			__m256d b3 = _mm256_loadu_pd(&b[k*n+8]);
			t3 = _mm256_sub_pd(t3,_mm256_mul_pd(a1,b3));

			__m256d b4 = _mm256_loadu_pd(&b[k*n+12]);
			t4 = _mm256_sub_pd(t4,_mm256_mul_pd(a1,b4));

			__m256d b5 = _mm256_loadu_pd(&b[k*n+16]);
			t5 = _mm256_sub_pd(t5,_mm256_mul_pd(a1,b5));

			__m256d b6 = _mm256_loadu_pd(&b[k*n+20]);
			t6 = _mm256_sub_pd(t6,_mm256_mul_pd(a1,b6));

			__m256d b7 = _mm256_loadu_pd(&b[k*n+24]);
			t7 = _mm256_sub_pd(t7,_mm256_mul_pd(a1,b7));

			__m256d b8 = _mm256_loadu_pd(&b[k*n+28]);
			t8 = _mm256_sub_pd(t8,_mm256_mul_pd(a1,b8));
		}
		_mm256_storeu_pd(&c[i*n +  0], t1);
		_mm256_storeu_pd(&c[i*n +  4], t2);
		_mm256_storeu_pd(&c[i*n +  8], t3);
		_mm256_storeu_pd(&c[i*n + 12], t4);
		_mm256_storeu_pd(&c[i*n + 16], t5);
		_mm256_storeu_pd(&c[i*n + 20], t6);
		_mm256_storeu_pd(&c[i*n + 24], t7);
		_mm256_storeu_pd(&c[i*n + 28], t8);
	}
}

extern "C" void product64x64_avx(float *a, float *b, float *c, int n) 
{
	for(int i=0; i<n; i++) {	
		__m256 t1 = _mm256_loadu_ps(&c[i*n +  0]);
		__m256 t2 = _mm256_loadu_ps(&c[i*n +  8]);
		__m256 t3 = _mm256_loadu_ps(&c[i*n + 16]);
		__m256 t4 = _mm256_loadu_ps(&c[i*n + 24]);
		__m256 t5 = _mm256_loadu_ps(&c[i*n + 32]);
		__m256 t6 = _mm256_loadu_ps(&c[i*n + 40]);
		__m256 t7 = _mm256_loadu_ps(&c[i*n + 48]);
		__m256 t8 = _mm256_loadu_ps(&c[i*n + 56]);
		for(int k=0; k<n; k++) {
			__m256 a1 = _mm256_set1_ps(a[k*n+i]);
			
			__m256 b1 = _mm256_loadu_ps(&b[k*n+0]);
			t1 = _mm256_sub_ps(t1,_mm256_mul_ps(a1,b1));
			
			__m256 b2 = _mm256_loadu_ps(&b[k*n+8]);
			t2 = _mm256_sub_ps(t2,_mm256_mul_ps(a1,b2));

			__m256 b3 = _mm256_loadu_ps(&b[k*n+16]);
			t3 = _mm256_sub_ps(t3,_mm256_mul_ps(a1,b3));

			__m256 b4 = _mm256_loadu_ps(&b[k*n+24]);
			t4 = _mm256_sub_ps(t4,_mm256_mul_ps(a1,b4));

			__m256 b5 = _mm256_loadu_ps(&b[k*n+32]);
			t5 = _mm256_sub_ps(t5,_mm256_mul_ps(a1,b5));

			__m256 b6 = _mm256_loadu_ps(&b[k*n+40]);
			t6 = _mm256_sub_ps(t6,_mm256_mul_ps(a1,b6));

			__m256 b7 = _mm256_loadu_ps(&b[k*n+48]);
			t7 = _mm256_sub_ps(t7,_mm256_mul_ps(a1,b7));

			__m256 b8 = _mm256_loadu_ps(&b[k*n+56]);
			t8 = _mm256_sub_ps(t8,_mm256_mul_ps(a1,b8));
		}
		_mm256_storeu_ps(&c[i*n +  0], t1);
		_mm256_storeu_ps(&c[i*n +  8], t2);
		_mm256_storeu_ps(&c[i*n + 16], t3);
		_mm256_storeu_ps(&c[i*n + 24], t4);
		_mm256_storeu_ps(&c[i*n + 32], t5);
		_mm256_storeu_ps(&c[i*n + 40], t6);
		_mm256_storeu_ps(&c[i*n + 48], t7);
		_mm256_storeu_ps(&c[i*n + 56], t8);
	}
}

extern "C" void product32x32_avxf(float *a, float *b, float *c, int n) 
{
	for(int i=0; i<n; i++) {	
		__m256 t1 = _mm256_loadu_ps(&c[i*n +  0]);
		__m256 t2 = _mm256_loadu_ps(&c[i*n +  8]);
		__m256 t3 = _mm256_loadu_ps(&c[i*n + 16]);
		__m256 t4 = _mm256_loadu_ps(&c[i*n + 24]);		
		for(int k=0; k<n; k++) {
			__m256 a1 = _mm256_set1_ps(a[k*n+i]);
			
			__m256 b1 = _mm256_loadu_ps(&b[k*n+0]);
			t1 = _mm256_sub_ps(t1,_mm256_mul_ps(a1,b1));
			
			__m256 b2 = _mm256_loadu_ps(&b[k*n+8]);
			t2 = _mm256_sub_ps(t2,_mm256_mul_ps(a1,b2));

			__m256 b3 = _mm256_loadu_ps(&b[k*n+16]);
			t3 = _mm256_sub_ps(t3,_mm256_mul_ps(a1,b3));

			__m256 b4 = _mm256_loadu_ps(&b[k*n+24]);
			t4 = _mm256_sub_ps(t4,_mm256_mul_ps(a1,b4));			
		}
		_mm256_storeu_ps(&c[i*n +  0], t1);
		_mm256_storeu_ps(&c[i*n +  8], t2);
		_mm256_storeu_ps(&c[i*n + 16], t3);
		_mm256_storeu_ps(&c[i*n + 24], t4);
	}
}
