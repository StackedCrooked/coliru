#include <tuple>
struct A : public std::tuple<int, double> {};

int main() {
  A t;
  int i;
  double j;
  std::tie(i,j)=t;
}
