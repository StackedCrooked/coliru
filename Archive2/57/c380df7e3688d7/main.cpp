#include <iostream>

using namespace std;

template<typename T>
struct my_constant
{
  static const constexpr T value = 42;
};

int main()
{
  constexpr double  value = my_constant<double>::value;
}
