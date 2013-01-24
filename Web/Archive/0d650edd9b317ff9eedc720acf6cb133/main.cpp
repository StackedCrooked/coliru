#include <iostream>


int main()
{
   int array[] = {1,2,3,4};

for (int a : array) for (int b : array) if (a != b) std::cout << a << b << '\n';
}