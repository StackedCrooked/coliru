#include <tuple>

template <typename...Ts>
constexpr std::tuple<Ts...> foo(Ts&&...ts) {
  return std::tuple<Ts...>{std::forward<Ts>(ts)...};
}

int main() {
  struct X {};
  struct Y {};
  X x;
  Y y;
  static_assert(std::is_same<decltype(foo(1,x,std::move(y))),std::tuple<int,X&,Y>>(),
                "Jabberwocky is killing user.");
}
