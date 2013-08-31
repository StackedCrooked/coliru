#include <type_traits>

template <typename T, typename... With>
struct is_callable_with {
  typedef char _True_Type;
  typedef long _False_Type;
  
  static _True_Type   helper(decltype(std::declval<T>()(std::declval<With>()...)) *);
  static _False_Type  helper(...);
  constexpr const static bool value = sizeof(helper(nullptr)) == sizeof(_True_Type);
};

template <typename T, typename... With>
struct guess_return_type {
  typedef decltype(std::declval<T>()(std::declval<With>()...)) return_type;
};
#include <cstdio>

struct functor {
  int operator() (int, char);
};

int main(int, char **) {
  static_assert(std::is_same<typename guess_return_type<functor, int, char>::return_type, int>::value, "ooops");
  
  std::printf("%s\n", is_callable_with<functor, int, char>::value ? "true" : "false");
  std::printf("%s\n", is_callable_with<functor, int, int>::value ? "true" : "false");
  return 0;
}

