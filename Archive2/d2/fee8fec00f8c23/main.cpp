#include <iostream>
#include <x86intrin.h>
using namespace std;


int main()
{
    double x[] = {0,1,2,3,4,5,6,7};
    double y[] = {7,6,5,4,3,2,1,0};
    
    __m512d a = _mm512_load_pd(x);
    __m512d b = _mm512_load_pd(y);
    
    a = _mm512_mul_pd(a,b);
    
    _mm512_store_pd(x,a);
    
    cout << x[0] << endl;
}