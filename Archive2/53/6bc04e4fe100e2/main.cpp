#include <cstdio>
#include <cstdlib>

bool func() {
  if ((std::rand() % 10000000) < 1) {
    return false;
  }
  return true;
}

int main() {
  int wins = 0;
  int fails = 0;
  for (int i = 0; i != 100000000; ++i) {
    if (!func()) {
      ++fails;
      continue;
    }
    if (!func()) {
      ++fails;
      continue;
    }
    if (!func()) {
      ++fails;
      continue;
    }
    ++wins;
  }
  std::printf("wins:%d fails:%d\n", wins, fails);
}
