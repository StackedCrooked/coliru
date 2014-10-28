#include <stdio.h>
#include <sys/time.h>
#include <vector>

using namespace std;

int main()
{
#define SIZE 500000

    vector<unsigned int> v;
    v.resize(SIZE);
    unsigned int * const vp = &v[0];

    // fill vector with some data
    volatile size_t i;
    for (i=0; i<SIZE; i++)
        v[i]=i;

    timeval t1, t2, t3;
    gettimeofday(&t1, NULL);

    for (int itt=0; itt<100; itt++)
        for (i=1; i<SIZE; i++)
            v[i] += v[i-1];

    gettimeofday(&t2, NULL);

    for (int itt=0; itt<100; itt++)
        for (i=1; i<SIZE; i++)
            vp[i] += vp[i-1];

    gettimeofday(&t3, NULL);

    int tdiff = (t2.tv_sec*1000000 + t2.tv_usec) - (t1.tv_sec*1000000 + t1.tv_usec);
    printf("time1: %d\n", tdiff);

    tdiff = (t3.tv_sec*1000000 + t3.tv_usec) - (t2.tv_sec*1000000 + t2.tv_usec);
    printf("time2: %d\n", tdiff);

    return 0;
}