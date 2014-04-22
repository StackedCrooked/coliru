#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"

void set_bit(unsigned int *set, int index){
	set[index/32] |= 1 << (index%32);
}

void clear_bit(unsigned int *set, int index){
	set[index/32] &= ~(1 << (index%32));
}

int get_bit(unsigned int *set, int index){
	return ( (set[index/32] & (1 << (index%32)) ) != 0);
}

int main(void){
	int n = 10000000;
	
	unsigned int prime_table[(n/3) / sizeof(unsigned int) +1];
	for (int i = 0; i < (n/3) / sizeof(unsigned int) +1; i++){
		prime_table[i] = 1;
	}
	
    // Sieve of Eratosthenes:
    for (int i = 5, t = 2; i*i < n; i += t, t = 6-t){
        if (get_bit(prime_table, i/3) ){
            for (int j = i*i, v = t; j < n; j += v*i, v = 6-v){
                clear_bit(prime_table, j/3);
            }
        }
    }

    printf("Numbers are: ");
    printf("2, 3, ");
    for (int i = 5, t = 2; i*i < n; i += t, t = 6-t){
        if (get_bit(prime_table, i/3)) printf("%d, ", i);
    }
    printf("\n");

}