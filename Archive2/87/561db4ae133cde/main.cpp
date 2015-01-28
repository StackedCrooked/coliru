#include <utility>
template <typename Tp, typename... Us>
Tp foo(Us&&... us) {
  return Tp{std::forward<Us>(us)...};
}

int main() {
  char a;
  foo<char&>(a);
  return 0;
}