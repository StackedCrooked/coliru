#include <iostream>

int naive_socks(int n, int m) 
{
    int day = 0;
    while(n > 0) {
        //morning
        ++day;
        --n;
        //afternoon
        if (day % m == 0)
            ++n;
    }
    return day;
}

int code_test(int n, int m) 
{
    int day = 0;
    while(n>0)
    {
        day=day+n;
        n=n/m;  
    }
    return day;
}

int main() {
    for(int n=2; n<6; ++n) {
        for(int m=2; m<6; ++m) {
            std::cout << n << '\t' << m << '\t' << naive_socks(n,m) << '\t' << code_test(n,m) << '\n';
        }
    }
    return 0;
}
