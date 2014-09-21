#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <algorithm>
#include <iostream>

int main()
{
  unsigned long long a[] = { 1, 2, 3, 4 };
  unsigned long long b[] = { 5, 6, 7, 8 };
  std::transform(a, a+4, b, a, (boost::lambda::_1 + boost::lambda::_2));
  for (int i=0; i<4; ++i)
    std::cout << a[i] << ", ";
  std::cout << std::endl;

  return 0;
}