#define _SCL_SECURE 0
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>

struct timer
{
    clock_t start;
    timer()
    {
        start=clock();
    }
    ~timer()
    {
        double t=static_cast<double>(clock()-start)/CLOCKS_PER_SEC;
        printf("%lf\n", t);
    }
};

int main()
{
    const size_t len=(1<<28);   
    {
        timer t;
        int *d=new int[len];
        printf("%d\n",d[len-1]);//prevent compiler from optimizing away 
                                //useless allocation and deallocation
        delete[] d;
    }
    {
        timer t;
        int *d=(int *)malloc(len*sizeof(int));
        printf("%d\n", d[len-1]);
        free(d);
    }

    {
        timer t;
        std::vector<int> d;
        d.reserve(len);
        printf("%d\n", d[len-1]);
    }
    {
        timer t;
        int *d=(int *)calloc(len, sizeof(int));
        printf("%d\n", d[len-1]);
        free(d);
    }

    return 0;
}