#include <iostream>
#include <functional>
#include <algorithm>

std::pair<int, int> get_traffic_configuration(int mps)
{
  std::vector<std::pair<int, int>> ts;
  for (int i = 2; i < 1000; ++i)
  {
    int period = std::max(mps / i, 10);
    int tick_per_min = 60000 / period;
    int mpt = mps * 60 / tick_per_min;

    ts.emplace_back(std::make_pair(mpt, period));
  }

  auto p = min_element(begin(ts), end(ts), [=] (std::pair<int, int> a, std::pair<int, int> b) {
      return std::abs(mps * 60 - a.first * 60000 / a.second) < std::abs(mps * 60 - b.first * 60000 / b.second);
  });

  return *p;
}

int main()
{
  auto f = [] (int i)
  {
    auto v1 = get_traffic_configuration(i);
    std::cout << "(" << v1.first << ", " << v1.second << ") :" << std::abs(i - v1.first * 1000 / v1.second)  << std::endl;
  };

  f(162);
  f(340);
  f(299);
}
