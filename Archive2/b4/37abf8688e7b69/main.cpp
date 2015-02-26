
union max_align_t {
    void* p;
    long double ld;
    void(*f)(int);
    long long ll;
};

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <gmpxx.h>

void fib_old(unsigned int n){
    mpz_t a, b, t;

    mpz_init_set_ui(a, 0);
    mpz_init_set_ui(b, 1);
    mpz_init(t);
    for(; n > 1; n --){
        mpz_add(t, a, b);
        mpz_set(a, b);
        mpz_set(b, t);
    }
    mpz_out_str(stdout, 10, b);
}

void fib_new(unsigned int n){
    mpz_class a,b;
    _mpz_realloc(a.get_mpz_t(), 1000000);
    _mpz_realloc(b.get_mpz_t(), 1000000);
    b = 1;
    for(; n > 2; n -= 2){
        a += b;
        b += a;
    }
    if (n) {
        a += b; 
        mpz_out_str(stdout, 10, a.get_mpz_t());    
    } else {
        mpz_out_str(stdout, 10, b.get_mpz_t()); 
    }
}


int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: fibc <number>\n");
        return 1;
    }

    fib_old(atol(argv[1]));
    printf("\n");
    fib_new(atol(argv[1]));

    return 0;
}