#include <cmath>
#include <iostream>

const struct PowOperator {} Pow;

struct PowInvoker
{
  int lhs;
};

PowInvoker operator< (int lhs, PowOperator)
{
  return {lhs};
}

int operator> (PowInvoker lhs, int rhs)
{
  return std::pow(lhs.lhs, rhs);
}

int main()
{
  std::cout << (2 <Pow> 3) << std::endl;
}