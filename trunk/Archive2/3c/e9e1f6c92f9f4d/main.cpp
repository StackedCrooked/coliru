#include <exception>
#include <cstdio>
#include <cstdlib>

void func() {
  if ((std::rand() % 10000000) < 1) {
    throw std::exception();
  }
}

int main() {
  int wins = 0;
  int fails = 0;
  for (int i = 0; i != 100000000; ++i) {
    try {
      func();
      func();
      func();
      ++wins;
    } catch(const std::exception&) {
      ++fails;
    }
  }
  std::printf("wins:%d fails:%d\n", wins, fails);
}
