#include <type_traits>
#include <vector>

struct is_tbase_of_impl
{
    struct err {};

    template <template <class...> class T>
    static err test(...);

    template <template <class...> class T, template <class...> class U, class... Args>
    static T<Args...> test(U<Args...>*);
};

template <template <class...> class T, class U>
using is_tbase_of
    = typename std::is_same< decltype(is_tbase_of_impl::test<T>((U*)0)), U >::type;

template <template <class...> class T>
struct quote
{
    template <class... U>
    using type = T<U...>;
};

using QVec = quote<std::vector>;

template <class...> struct S {};
template <class...> struct S2_ { using type=S2_; };
template <class...Ts> using S2=typename S2_<Ts...>::type;

template <> struct S2_<int, void> { using type=S<int>; };

struct foo:S<int> {};


static_assert( !is_tbase_of< std::vector, std::is_integral<int>  >::value, "" );
static_assert(  is_tbase_of< std::vector, std::vector<int>       >::value, "" );
static_assert(  is_tbase_of< QVec::type,  std::vector<int>       >::value, "" );
static_assert( !is_tbase_of< std::vector, S<int, int, int>       >::value, "" );
static_assert( !is_tbase_of< S2,          S2<int, void>          >::value, "" );

int main()
{
}