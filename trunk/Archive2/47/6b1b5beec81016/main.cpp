#include <stdio.h>
#include <stdint.h>
#include <omp.h>
#include <math.h>

int is_prime(uint64_t n)
{
    uint64_t p;
    if (!(n & 1) || n < 2 ) return n == 2;

    /* comparing p*p <= n can overflow */
    for (p = 3; p <= n/p; p += 2)
        if (!(n % p)) return 0;
    return 1;
}

int is_prime2(uint64_t n)
{
    uint64_t p;
    if (!(n & 1) || n < 2 ) return n == 2;

    /* comparing p*p <= n can overflow */
    for (p = 3; p*p <= n; p += 2)
        if (!(n % p)) return 0;
    return 1;
}

int is_prime3(uint64_t n)
{
    uint64_t p;
    if (!(n & 1) || n < 2 ) return n == 2;

    /* comparing p*p <= n can overflow */
    uint32_t cut = sqrt((double)n);
    for (p = 3; p <= cut; p += 2)
        if (!(n % p)) return 0;
    return 1;
}

int is_prime4(uint64_t n)
{
    uint64_t p;
    int ret = -1;
    if (!(n & 1) || n < 2) return n == 2;

    /* comparing p*p <= n can overflow */
    p = 1;
    do {
		p += 2;
        if (p > n / p) ret = 1; /* Let's return latter outside the loop. */
        else if (!(n % p)) ret = 0;		
    } while (ret < 0);
    return ret;
}

int is_prime5(uint64_t n)
{
    uint64_t p;
	int test = 0;
    if (!(n & 1) || n < 2 ) return n == 2;

    /* comparing p*p <= n can overflow */
    for (p = 3; !test; p += 2) {
		if(p>n/p) test = 1;
        if (!(n%p)) test = 1;
	}
    return test;
}



int main() {
    //uint64_t x = ((uint64_t)1<<63) - 25;
    uint64_t x = ((uint64_t)1<<56) - 5;
    int prime = false;
    double dtime;
    
    dtime = omp_get_wtime();
    prime = is_prime(x);
    dtime = omp_get_wtime() - dtime;
    printf("%d %f\n", prime, dtime);
    prime = false;
    /*
    dtime = omp_get_wtime();
    prime = is_prime2(x);
    dtime = omp_get_wtime() - dtime;
    printf("%d %f\n", prime, dtime);
    prime = false;
    
    dtime = omp_get_wtime();
    prime = is_prime3(x);
    dtime = omp_get_wtime() - dtime;
    printf("%d %f\n", prime, dtime);
    prime = false;

	dtime = omp_get_wtime();
    prime = is_prime4(x);
    dtime = omp_get_wtime() - dtime;
    printf("%d %f\n", prime, dtime);
    prime = false;
	*/
	dtime = omp_get_wtime();
    prime = is_prime5(x);
    dtime = omp_get_wtime() - dtime;
    printf("%d %f\n", prime, dtime);
    prime = false;
}