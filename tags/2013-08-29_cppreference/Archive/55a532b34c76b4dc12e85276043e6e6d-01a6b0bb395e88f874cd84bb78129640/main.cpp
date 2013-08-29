#include <type_traits>

template<class From, class To>
struct is_convertible{
  static void foo(To);
  template<class F>
  static auto test(int) -> decltype(foo(std::declval<F>()), std::true_type{});
  template<class>
  static auto test(...) -> std::false_type;

  static constexpr bool value = decltype(test<From>(0))::value;
};

static_assert(std::is_convertible<int, double>::value, "std, true");
static_assert(is_convertible<int, double>::value, "own, true");

static_assert(!std::is_convertible<int, int*>::value, "std, false");
static_assert(!is_convertible<int, int*>::value, "own, false");

int main(){}