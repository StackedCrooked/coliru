#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>


int main() {
    unsigned int *a= new unsigned int[100000000];
    unsigned int v = 0xaabbccdd;
    timeb start, end;

    ftime(&start);
    clock_t start_cycle = clock();

    for (register int i=0; i<100000000; i++) {
      a[i] += v;
    }   

    clock_t end_cycle = clock();
    ftime(&end);

    printf ("elapsed time: %d ms\n", ((end.time - start.time)*1000 + 
                                       end.millitm - start.millitm));
    printf ("cycles: %d\n", end_cycle - start_cycle);

    delete a;
    return end_cycle - start_cycle;
}