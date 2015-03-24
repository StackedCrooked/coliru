
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <boost/chrono.hpp>
typedef boost::chrono::milliseconds ms;


constexpr void cycle(double& a, double& b)
{
    
    for(int i=0; i<100000000; i++) 
    {
            a = a + b;
    }
}


int main() {
    double a = 3.1415926, b = 2.718;
    int i, j;
    for(j=0; j<10; j++) {
        auto start = boost::chrono::steady_clock::now();
        cycle(a,b);
        auto end = boost::chrono::steady_clock::now();
        ms d = boost::chrono::duration_cast<ms>(end - start);
        std::cerr << d.count() << "ms" << std::endl;
    }
    printf("a = %lf\n", a);
    return 0;
}