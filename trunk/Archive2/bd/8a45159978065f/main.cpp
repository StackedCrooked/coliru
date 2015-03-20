#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
  std::vector<std::pair<int, int>> v;
  for (int i = 0; i != 1000; ++i) {
    v.push_back({0, 1000-i});
  }
  std::sort(v.begin(), v.end(),
            [](std::pair<int, int> l, std::pair<int, int> r) {
              return l.second < r.second;
            });
  std::cout << v.back().second << "\n";
}
