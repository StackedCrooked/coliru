#include <iostream>
#include <iomanip>


// increment x until it is divisible by n
int align(int x, int n) 
{
    auto r = x % n;
    return x + bool(r) * (n - r);
}