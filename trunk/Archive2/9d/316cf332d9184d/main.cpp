#include <functional>
#include <iostream>
using std::placeholders::_1;

static int count = 0;

int binary_function(int a, int b) { 
    std::cout << "count: " << count++ << " a = " << a << ", b = " << b << std::endl;
    return a + b; 
    }

int main()
{
   auto f = std::bind(binary_function, std::bind(binary_function, _1, 2), 3);
   std::cout << f(3) << std::endl; // -> 7
}