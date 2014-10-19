#include <functional>
#include <iostream>

class Y {
 public:
  explicit Y(int x) : x_(x) {}
  bool f(int n) const { return n > x_; }

 private:
  int x_;
};
extern Y* y;

void init() { y = new Y(2); }

int main() {
  init();
  std::function<bool(int)> f = [&y](int x) -> bool { return y->f(x); };
  std::cout << f(3) << std::endl;
}
