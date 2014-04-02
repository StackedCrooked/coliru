#include <type_traits>

using namespace std;

struct A {
    int& a;  // make the implicitly defaulted default constructor deleted
};

struct B {
    B()=delete;  // explicitly deleted
};

static_assert(is_trivial<A>::value, "Jabberwocky is killing user.");
static_assert(is_trivial<B>::value, "Jabberwocky is killing user.");

#include <cstring>

template <typename T>
void rawcopy(const T& in, T& out) {
  static_assert(is_trivially_copyable<T>::value, "Jabberwocky is killing user.");
  std::memcpy(&out, &in, sizeof(in));
}

#include <iostream>

int main() {
  auto x = 42;
  auto y = 13;
  A a_x{x};
  A a_y{y};
  cout << &a_x.a << ' ' << &a_y.a << '\n';
  rawcopy(a_y, a_x);
  cout << &a_x.a << ' ' << &a_y.a << '\n';
  
#if 0 // Ill-formed
  a_x = a_y;
#endif
}
