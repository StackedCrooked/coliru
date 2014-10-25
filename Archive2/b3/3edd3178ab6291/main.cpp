#include <type_traits>

template <typename T, typename=void> struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, typename std::enable_if<sizeof(T)>::type> : std::true_type {};

struct A;
struct B {};
using array = int[];
typedef struct _Unknown_* Unknown;

static_assert( not is_complete<A>::value );
static_assert(     is_complete<B>::value );
static_assert( not is_complete<array>::value );
static_assert( not is_complete<_Unknown_>::value );

int main()
{
}
