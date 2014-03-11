#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
constexpr auto diff (T x, T y) {
    return (x > y) ? (x - y) : (y - x);
}

template <typename T>
constexpr auto sqrt (T a, T eps = T(1e-15)) {
  T x[] = {a, (a + 1) / 2};
  while (diff(x[0], x[1]) > eps) {
    x[0] = x[1];
    x[1] = (x[0] + a / x[0]) / 2;
  }
  return x[1];
}

int main() {
    constexpr auto x1 = sqrt<float>(16);
    constexpr auto x2 = sqrt<float>(25);
    constexpr auto x3 = sqrt<float>(27);
    constexpr auto x4 = ::sqrt(27); // avoid std::sqrt
    cout << x1 << endl;
    cout << x2 << endl;
    cout << x3 << endl;
    cout << x4 << endl;
}