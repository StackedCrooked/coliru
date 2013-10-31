#include <cstdio>
#include <valarray>

using namespace std;

extern void fill(valarray<int>&, valarray<int>&);

void foo()
{
    const int k = 10;
    valarray<int> va1(k);
    valarray<int> va2(k);
    
    fill(va1, va2);
    
    for(auto i =0;i<k;++i)                                                         
        printf("%d\n",(va1+va2-(va1-va2))[i]); 
}
