#include <iostream>
#include <vector>
#include <map>



enum struct Color
{
  Red,
};

int main()
{
  std::map<Color, std::vector<int>> m;
  m[Color::Red] = {1,2,3,4};

  std::cout << m[Color::Red].at(3) << '\n';
}
