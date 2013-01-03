#include <memory>
#include <array>
#include <tuple>
#include <iostream>

using std::cout;
using std::endl;

enum E { ZERO, ONE, TWO };

int main()
{
    E e(E(0));
    
    int g = 44;
    
    E d(E(g));
}