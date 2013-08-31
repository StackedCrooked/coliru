#include <complex>
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <future>

int main() 
{
    for (struct { int i; double j; } x = {0,0};  x.i < 10; ++x.i, x.j+=.1)
    {
        std::cout << x.i << " " << x.j << '\n';
    }
}