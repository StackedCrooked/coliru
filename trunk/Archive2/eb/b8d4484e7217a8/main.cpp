#include <tuple>
#include <boost/fusion/adapted/std_pair.hpp>

int main() {
  int a; int b;
  std::tie(a, b) = std::make_pair(1, 42);
  return b;
}