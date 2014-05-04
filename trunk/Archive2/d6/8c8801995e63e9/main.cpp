#include<omp.h>
#include<stdio.h>

int test, result;
#pragma omp threadprivate(test, result)

void add(void)
{
    result = result + test;
}

int main(void)
{
    int i, test2;
#pragma omp parallel for private(i) 
    for (test2 = 0; test2 < 5; test2++) {
        test = test2;
        result = 0;
        for (i = 1; i < 100; i++) {
            add();
        }
        printf("Result in %dth test is: %d\n", test, result);
    } //End of parallel region
    return 0;
}