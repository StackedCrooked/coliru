#include <cmath>
#include <functional>
#include <iostream>

typedef double naked_real_function(double);
typedef std::function<naked_real_function> real_function;

inline real_function derivative(real_function f)
{
  return [f](double x)
  {
    static const double h=1.0E-6;
    return (f(x+h)-f(x-h))/(2*h);
  };
}

inline real_function derivative(naked_real_function* f)
{
  return derivative(real_function(f));
}

int main()
{
  auto f=derivative(derivative(std::sin));
  for(double x=0;x<2*3.14159265;x+=0.1)std::cout<<f(x)<<std::endl;
}