#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
   boost::multiprecision::cpp_int factorial = 1;
   for(unsigned int n = 2; n <= 100; ++n)
   {
       factorial *= n;
       if(n > 16)
           std::cout << n << "! = " << factorial << '\n';
   }
}
