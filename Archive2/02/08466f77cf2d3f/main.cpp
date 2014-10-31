#include <cassert>

int clash_g = 333;

struct G {
  int clash_g = -332;
  void fn() { assert(clash_g + ::clash_g == 1); }
};

int main() {

  int clash_l = 333;

  struct L {
    int clash_l = -332;
    void fn() { assert(clash_l +   clash_l == -664); } // 666 instead of 1
  };

  G().fn(); L().fn();
}