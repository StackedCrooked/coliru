#include <stdio.h>

struct X {
  const int& member;
  X() : member(9) { }
};

int main() {
  X x;
  printf("%d\n", x.member);
  const int& local = 3;
  printf("%d\n", x.member);
}
