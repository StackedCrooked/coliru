#include <stdlib.h>

#define N_TIMES     600000
#define ARRAY_SIZE   10000

int main (void)
{
    double  *array = (double*)calloc(ARRAY_SIZE, sizeof(double));
    double  sum = 0;
    int     i;

    for (i = 0; i < N_TIMES; i++) {

        int     j;

        for (j = 0; j < ARRAY_SIZE; j++) {
            sum += array[j];
            }
        }

    return 0;
}
