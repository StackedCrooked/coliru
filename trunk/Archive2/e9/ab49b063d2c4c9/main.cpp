#include <functional>
#include <iostream>
using std::placeholders::_1;

int binary_function(int a, int b) { return a + b; }

int main()
{
   auto f = std::bind(binary_function, std::bind(binary_function, _1, 2), 3);
   std::cout << f(2) << std::endl; // -> 7
}