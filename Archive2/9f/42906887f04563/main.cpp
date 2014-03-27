#include <iostream>
#include <string>
#include <vector>
#include <memory>

template <class T>
void foo(double p) {
    std::cout << (T)p;
}

int main()
{
    foo<int>(5.0);    
    return 0;
}
