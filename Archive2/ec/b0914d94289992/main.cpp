#include <iostream>
#include <vector>
#include <map>

enum struct Color
{
  Red,
  Blue,
};

int main()
{
  std::map<Color, std::vector<int>> m{{Color::Blue, {10,20,30}}};
  m[Color::Red] = {1,2,3,4};

  std::cout << m[Color::Red].at(3) << '\n';
  std::cout << m[Color::Blue][0] << '\n';
}
