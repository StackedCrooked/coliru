#include <type_traits>

template <class, class=void>
struct is_scoped_enum : std::false_type {};

template <class T>
struct is_scoped_enum<T, std::enable_if_t<!std::is_convertible<T, int>{}>>
    : std::is_enum<T> {};

enum e {};
enum class e2 {};

static_assert( is_scoped_enum<e2>::value, "" );
static_assert( !is_scoped_enum<e>::value, "" );
static_assert( !is_scoped_enum<int>::value, "" );

int main() {}
