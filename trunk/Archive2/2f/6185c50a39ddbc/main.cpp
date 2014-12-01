#include <cmath>

template <typename T> struct comparison_traits {
  static bool equal(const T& a, const T& b) {
    return a == b;
  }

  // etc.
};

template<> struct comparison_traits<double> {
  static bool equal(const double& a, const double& b) {
    return fabs(a - b) < 1e-15; // or whatever...
  }
};

template <typename T>
class C {
  T x, y;

  public:
    C(const T& a, const T& b) : x(a), y(b) {}

    bool cmp() {
      return comparison_traits<T>::equal(x, y);
    }
};

int main() {
  // OK
  C<int> i(1, 2);
  i.cmp();

  // Now OK too...
  C<double> d(1.0, 2.0);
  d.cmp();

  return 0;
}
