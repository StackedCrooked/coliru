#include <type_traits>

template <class T>
using is_scoped_enum = std::integral_constant<bool, !std::is_convertible<T,int>{}
                                                  && std::is_enum<T>{}>;

enum e {};
enum class e2 {};

static_assert( is_scoped_enum<e2>::value, "" );
static_assert( !is_scoped_enum<e>::value, "" );
static_assert( !is_scoped_enum<int>::value, "" );

int main() {}
