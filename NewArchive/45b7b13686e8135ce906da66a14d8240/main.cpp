#include <tuple>

typedef int (*func_t)();

int number() {
  return 2;
}

double number(bool) {
  return 1.2;
}

int main() {
  // With a static_cast it compiles without any error
  // std::tuple<func_t> tup = std::make_tuple(static_cast<func_t>(number));                                                               

  std::tuple<func_t> tup{number};

   return 0;
}