#include <iostream>

int foo(double a, double b){ return a+b;}
int foo(int a, double b){return a+b;}
int foo(double a, int b){return a+b;}

int main()
{
    int q=1;
    double w=2;
    
    std::cout << foo(q,q) << std::endl;
    
    return 0;
}

