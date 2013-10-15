unsigned long long int recursive(int year, int a, int b, int m){
    if(year==1)
        return 0;
    else
        return (a*recursive(year-1,a,b,m)+b+year)%m;
}

unsigned long long int iterative(int year, int a, int b, int m){
    unsigned long long r = 0;
    for (int i=2; i<=year; ++i)
        r = (a*r+b+i) % m;

    return r;
}

#include <cassert>
#include <cstdlib>

int main()
{
    // 20000 test cases ought to be enough for anybody
    for (int i = 1; i< 20000; ++i)
    {
        auto a = rand()%31;
        auto b = rand()%37;
        auto m = rand()%97 + 1;

        assert(recursive(i, a, b, m) == iterative(i, a, b, m));
    }
}
