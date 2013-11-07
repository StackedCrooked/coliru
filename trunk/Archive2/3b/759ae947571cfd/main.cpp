#include <stdio.h>
#include <omp.h>
#include <immintrin.h> //AVX
//#include <nmmintrin.h>                 // SSE4.2

void scan(float a[], float s[], int n) {
    float sum = 0;
	for (int i = 0; i<n; i++) {
		sum += a[i];
		s[i] = sum;
	}
}
float comparef(float *a1, float *a2, const int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		float diff = a1[i] - a2[i];
		if (diff < 0) diff *= -1;
		//if (diff != 0) printf("i %d, a1[i] %f, a2[i] %f\n", i, a1[i], a2[i]);
		sum += diff;
	}
	return sum;
}

inline __m128 scan_SSE4(__m128 x) {
	x = _mm_add_ps(x, _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(x), 4))); // shift left 4 bytes while shifting in zeros
	x = _mm_add_ps(x, _mm_shuffle_ps(_mm_setzero_ps(), x, 0x40)); //shift left 8 bytes while shifting in zeros
	//x = _mm_add_ps(x, _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(x), 8)));
	return x;
}

void scan_SSE(float *a, float *s, const int n) {
	__m128 offset = _mm_setzero_ps();
	for (int i = 0; i < n; i+=4) {
		__m128 x = _mm_load_ps(&a[i]);
		__m128 out = scan_SSE4(x);
		out = _mm_add_ps(out, offset);
		_mm_store_ps(&s[i], out);
		offset = _mm_shuffle_ps(out, out, _MM_SHUFFLE(3, 3, 3, 3));
	}
}

float pass1_SSE(float *a, float *s, const int n) {
	__m128 offset = _mm_setzero_ps();
	#pragma omp for schedule(static) nowait
	for (int i = 0; i < n / 4; i++) {
		__m128 x = _mm_load_ps(&a[4 * i]);
		__m128 out = scan_SSE4(x);
		out = _mm_add_ps(out, offset);
		_mm_store_ps(&s[4 * i], out);
		offset = _mm_shuffle_ps(out, out, _MM_SHUFFLE(3, 3, 3, 3));
	}
	float tmp[4];
	_mm_store_ps(tmp, offset);
	return tmp[3];
}

inline void pass2_SSE(float *s, __m128 offset, const int n) {
	#pragma omp for schedule(static)
	for (int i = 0; i<n/8; i++) {
		__m128 tmp1 = _mm_load_ps(&s[8 * i]);
		tmp1 = _mm_add_ps(tmp1, offset);
		__m128 tmp2 = _mm_load_ps(&s[8 * i + 4]);
		tmp2 = _mm_add_ps(tmp2, offset);
		_mm_store_ps(&s[8 * i], tmp1);
		_mm_store_ps(&s[8 * i + 4], tmp2);
	}
}

void scan_omp_SSEp2(float a[], float s[], int n) {
	float *suma;
	#pragma omp parallel
	{
		const int ithread = omp_get_thread_num();
		const int nthreads = omp_get_num_threads();
		#pragma omp single
		{
			suma = new float[nthreads + 1];
			suma[0] = 0;
		}
		float sum = 0;
		#pragma omp for schedule(static) nowait
		for (int i = 0; i<n; i++) {
			sum += a[i];
			s[i] = sum;
		}
		suma[ithread + 1] = sum;
		#pragma omp barrier
		#pragma omp single
		{
			float tmp = 0;
			for (int i = 0; i<(nthreads + 1); i++) {
				tmp += suma[i];
				suma[i] = tmp;
			}
		}
		__m128 offset = _mm_set1_ps(suma[ithread]);
		pass2_SSE(s, offset, n);
	}
	delete[] suma;
}

void scan_omp_SSEp2_SSEp1(float a[], float s[], int n) {
	float *suma;
	#pragma omp parallel
	{
		const int ithread = omp_get_thread_num();
		const int nthreads = omp_get_num_threads();
		#pragma omp single
		{
			suma = new float[nthreads + 1];
			suma[0] = 0;
		}		
		suma[ithread + 1] = pass1_SSE(a, s, n);
		#pragma omp barrier
		#pragma omp single
		{
			float tmp = 0;
			for (int i = 0; i<(nthreads + 1); i++) {
				tmp += suma[i];
				suma[i] = tmp;
			}
		}
		__m128 offset = _mm_set1_ps(suma[ithread]);
		pass2_SSE(s, offset, n);
	}
	delete[] suma;
}

int main() {
	const int n = 8 * 1 << 14;
	float *a = (float*)_mm_malloc(sizeof(float)*n, 64);
	float *s1 = (float*)_mm_malloc(sizeof(float)*n, 64);
	float *s2 = (float*)_mm_malloc(sizeof(float)*n, 64);
	for (int i = 0; i < n; i++) a[i] = 1.0f*i;
	for (int i = 0; i < n; i++) s1[i] = 0;
	for (int i = 0; i < n; i++) s2[i] = 1.0f*i*(i + 1) / 2;

	double dtime;
	const int repeat = 10000;

	dtime = omp_get_wtime();
	for (int i = 0; i < repeat; i++)
		scan_SSE(a, s1, n);
	dtime = omp_get_wtime() - dtime;
	printf("SSE: dtime %f, error %f\n", dtime, comparef(s1, s2, n));
	for (int i = 0; i < n; i++) s1[i] = 0;

	dtime = omp_get_wtime();
	for (int i = 0; i < repeat; i++)
		scan(a, s1, n);
	dtime = omp_get_wtime() - dtime;
	printf("sequential: dtime %f, error %f\n", dtime, comparef(s1, s2, n));
	for (int i = 0; i < n; i++) s1[i] = 0;
	
	dtime = omp_get_wtime();
	for (int i = 0; i < repeat; i++)
		scan_omp_SSEp2(a, s1, n);
	dtime = omp_get_wtime() - dtime;
	printf("omp SSEp2: dtime %f, error %f\n", dtime, comparef(s1, s2, n));
	for (int i = 0; i < n; i++) s1[i] = 0;

	dtime = omp_get_wtime();
	for (int i = 0; i < repeat; i++)
		scan_omp_SSEp2_SSEp1(a, s1, n);
	dtime = omp_get_wtime() - dtime;
	printf("omp SSEp2 SSEp1: dtime %f, error %f\n", dtime, comparef(s1, s2, n));
	for (int i = 0; i < n; i++) s1[i] = 0;	
}