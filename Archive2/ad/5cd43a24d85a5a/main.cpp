#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
 
typedef unsigned long long ULL;
 
#define MOD 1000000993
 
#define N 111111
#define PRIME_NUM 10544
 
 
ULL primes[PRIME_NUM];
 
 
int is_prime(ULL n)
{
    ULL max_divisor, divisor;
 
    if (n < 2)
        return 0;
    if (n == 2 || n == 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    max_divisor = (ULL)sqrt(n);
    divisor = 5;
    while (divisor <= max_divisor)
    {
        if (n % divisor == 0 || n % (divisor + 2) == 0)
            return 0;
        divisor += 6;
    }
 
    return 1;
}
 
ULL powmod(int what, int pow, int mod)
{
    ULL res = 1, cur = what;
    while (pow) {
        if (pow & 1)
            res = (ULL)res * cur % mod;
        cur = (ULL)cur * cur % mod;
        pow >>= 1;
    }
    return res;
}
 
ULL solve(int n, int k)
{
    int ind;
    int e_max;
    int e_res;
    int e;
 
    ULL d_prev = 1;
    ULL b_prev = 1;
    ULL s = 1;
 
    for (ind = 0; ind < PRIME_NUM; ind++)
    {
        e_max = (int)(log(n) / log(primes[ind]));
        e_res = 0;
 
        for (e = 1; e <= e_max; e++)
            if ((ULL)(k/pow(primes[ind],e)) + (ULL)((n - k)/pow(primes[ind],e)) != (ULL)(n/pow(primes[ind],e)))
                e_res++;
 
        if (e_res != 0)
        {
            s = ((s % MOD) + ((d_prev % MOD) * ((primes[ind] - b_prev - 1) % MOD) % MOD) % MOD) % MOD;
            s = ((s % MOD) + ((d_prev % MOD) * powmod(primes[ind], e_res, MOD)) % MOD) % MOD;
            b_prev = primes[ind];
            d_prev = ((d_prev % MOD) * powmod(primes[ind], e_res, MOD)) % MOD;
        }
    }
 
    s = ((s % MOD) + ((n - b_prev) * (d_prev % MOD)) % MOD) % MOD;
 
    return s;
}
 
int main() {
    
    int i;
    int ind = 0;
    int r;
    ULL answer = 0;
        ULL* part_results;
 
 
    for (i = 1; i <= N; i++ )
    {
        if (is_prime(i))
        {
            primes[ind++] = (ULL)i;
        }
    }
   
    part_results = (ULL*) malloc(omp_get_max_threads() * sizeof(ULL));
 
 #pragma omp parallel for reduction(+:answer)
    for (r = 0; r < omp_get_max_threads() - 1; r++)
    {
        answer = ((answer % MOD) + (2 * (solve(N, r) % MOD)) % MOD) % MOD;
    }
    answer %= MOD;
    
    free(part_results);
    printf("Answer is: %llu\n", answer);
 
    return 0;
}