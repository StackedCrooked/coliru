#include <stdio.h>

class X {
 public:
  X(int x) : x_(x) {}
  ~X() {
    printf("X(%d) has be released.\n", x_);
  }

  X(X&&) = default;
  X& operator = (X&&) = default;

  X(const X&) = delete;
  X& operator = (const X&) = delete;
 private:
  int x_;
};
