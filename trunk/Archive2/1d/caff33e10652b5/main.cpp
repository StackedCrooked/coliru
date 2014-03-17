#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

template <typename T>
auto add(T const& val) { return val; }

template <typename T1, typename T2, typename ...Ts>
auto add(T1 const& t1, T2 const& t2, Ts const&... ts) {
  return t1 + add(t2, ts...);
}

int main() {
  auto sum1 = add(1, 2.0, 3.0f);
  auto sum2 = add(6, 5.0, 4.0, 3);
  auto sum3 = add(std::string("Hello "), "World!");
  cout << sum1 << endl;
  cout << sum2 << endl;
  cout << sum3 << endl;
}