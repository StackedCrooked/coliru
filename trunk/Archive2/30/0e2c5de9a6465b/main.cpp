#include <cstdarg>

struct S {
  S() = default;
  S(const S&) {} // Not trivially copyable
  S& operator=(const S&) { return *this; }
};

void f(S s, ...) {
  va_list list;
  va_start(list, s);
  
  va_end(list);
}

int main() {
  S s;
  f(s);
}