#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

double f1(double x){
    return x * 1.7;
}

template <typename F, int N>
void calc (double (&a)[N], double (&b)[N], F f) {
    std::transform(a, a+N, b, f);
}

int main()
{
    double a[] = { 0,1,2,3,4,5,6,7,8,9 };
    const int N = sizeof(a)/sizeof(a[0]);

    //transform a to b
    double b[N];
    calc(a, b, f1);

    for(double* it=b; it!=b+N; ++it)
        std::cout << *it << " ";
}
