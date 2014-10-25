#include <type_traits>

template <typename T, typename=void> struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, typename std::enable_if<sizeof(T)>::type> : std::true_type {};

struct A;
struct B {};
using array = int[];
typedef struct Unknown_* Unknown; // Removed the first _ as it causes UB

static_assert( not is_complete<A>::value );
static_assert(     is_complete<B>::value );
static_assert( not is_complete<array>::value );
static_assert( not is_complete<Unknown_>::value );

int main()
{
}
