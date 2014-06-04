#include <iostream>
#include <vector>
#include <algorithm>

struct foo {
  foo(int const _id) : id(_id) {}
  int id;
};

bool operator<(foo const &a, foo const &b) { return a.id < b.id; }

auto main() -> int {
  std::vector<std::vector<foo>> v{{foo(1), foo(2)}, {foo(0), foo(3)}, {foo(4), foo(9)}};
  std::sort(v.begin(), v.end());
  for(auto i : v) {
    std::cout << "{ ";
    for(auto j : i) std::cout << j.id << " ";
    std::cout << "}" << std::endl;
  }
  
  return 0;
}