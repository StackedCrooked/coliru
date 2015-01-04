#include <type_traits>

void foo(int);

template <typename...> struct pack {}; // To be potentially introduced in C++1Z

template <typename, typename, typename=void>
struct Exists : std::false_type {};

template <typename R, typename... Args>
struct Exists<R, pack<Args...>,
  std::enable_if_t<std::is_same<decltype(foo(std::declval<Args>()...)), R>{}>>
    : std::true_type {};

static_assert(Exists<void, int>::value, "");
static_assert(!Exists<void, void>::value, "");
static_assert(!Exists<void, char*>::value, "");
static_assert(!Exists<int, void>::value, "");
static_assert(!Exists<int, int>::value, "");
static_assert(!Exists<int, char*>::value, "");

int main()
{

}
