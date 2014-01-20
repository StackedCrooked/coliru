#include <utility>
#include <vector>
#include <iostream>

template<typename T, typename... Tail>
constexpr std::initializer_list<T> make_range(T&& head, Tail&&... tail)
{
  return {std::forward<T>(head), std::forward<T>(tail)...};
}

void test(std::vector<int> x)
{
  for(auto y : x)
  {
      std::cout << y << std::endl;
  }
}

int main()
{
  test(make_range(1, 2, 3));
}
