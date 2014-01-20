#include <type_traits>

struct foo {
  static auto bar() -> decltype(*this);
  using self = typename std::decay<decltype(bar())>::type;
  static_assert(std::is_same<foo,self>(),"BOOM!");
};

int main(){}
