#include <iostream>
#include <string>
#include <vector>

struct A {
    A(int i) : i(i) { i++; std::cout << "CTOR i: " << i << std::endl; }
    
    int i;
};

int main()
{
    A d(5);
    std::cout << "Actual i: " << d.i << std::endl;
}
