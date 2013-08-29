#include <iostream>
#include <limits>
#include <cmath>

#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_dec_float;
typedef boost::multiprecision::number<cpp_dec_float<100>> ScalarType;

int main()
{
   ScalarType a = 3200;
   ScalarType b = 2345;
   using std::log;
   ScalarType x = log(a/b);
   ScalarType y = log(a) - log(b);
   ScalarType e = x - y;

   std::cout << std::numeric_limits<ScalarType>::max_digits10 << '\n';
   std::cout << std::setprecision(std::numeric_limits<ScalarType>::max_digits10);
   std::cout << x << '\n';
   std::cout << y << '\n';
   std::cout << e << '\n';

   std::cout << std::numeric_limits<ScalarType>::digits10 << '\n';
   std::cout << std::setprecision(std::numeric_limits<ScalarType>::digits10);
   std::cout << x << '\n';
   std::cout << y << '\n';
   std::cout << e << '\n';

   return 0;
}

