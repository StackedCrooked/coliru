#include <type_traits>
#include <utility>

void foo(int);

template <typename...> struct pack {}; // To be potentially introduced in C++1Z

template <typename, typename, typename=void>
struct Exists_impl : std::false_type {};

template <typename R, typename... Args>
struct Exists_impl<R, pack<Args...>,
  std::enable_if_t<std::is_same<decltype(foo(std::declval<Args>()...)), R>::value>>
    : std::true_type {};

template <typename R, typename... Args>
using Exists = Exists_impl<R, pack<Args...>>;

static_assert( Exists<void, int>{} );
static_assert( Exists<void, long>{} );
static_assert( !Exists<float, long>{} );
static_assert( !Exists<void>{} );

int main()
{
}
