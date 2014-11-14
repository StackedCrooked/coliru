#include <type_traits>

template <class, class=void>
struct is_scoped_enum : std::false_type {};

template <class T>
struct is_scoped_enum<T, typename std::enable_if<std::is_enum<T>::value && !std::is_convertible<T, typename std::underlying_type<T>::type>::value>::type> : std::true_type {};

enum e {};
enum class e2 {};

static_assert( is_scoped_enum<e2>::value, "" );
static_assert( !is_scoped_enum<e>::value, "" );

int main()
{
}
