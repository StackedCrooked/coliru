#include <utility>
template <typename Tp, typename Us>
decltype(auto) construct(Us&& us) {
  return Tp{std::forward<Us>(us)};
}

int main() {
  char a = 'a';
  auto c = construct<char&>(a);
  return 0;
}