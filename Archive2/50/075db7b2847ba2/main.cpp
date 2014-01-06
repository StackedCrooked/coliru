#include <iostream>

void testConstantExpressions() {

  constexpr double x0 = 1.0;
  constexpr double y0 = 2.0;
  constexpr double z0 = 4.0;
  constexpr double w0 = x0 / (y0 / z0);
  std::cout << w0 << std::endl;

  constexpr double x1 = 1.0;
  constexpr double y1 = 2.2;
  constexpr double z1 = 4.0;
  constexpr double w1 = x1 / (y1 / z1);
  std::cout << w1 << std::endl;

  constexpr double x2 = 1.0;
  constexpr double y2 = 4.0;
  constexpr double z2 = 2.3;
  constexpr double w2 = x2 / (y2 / z2);
  std::cout << w2 << std::endl;

}
int main()
{
    testConstantExpressions();
}