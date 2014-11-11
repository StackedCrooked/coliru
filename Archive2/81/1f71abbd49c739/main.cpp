#include <type_traits>

template <class S, class C, typename = void>
struct is_streamable : ::std::false_type { };

template <class S, class C>
struct is_streamable<S,
  C,
  decltype(void(sizeof(decltype(::std::declval<S&>() <<
    ::std::declval<C const&>()))))
> : ::std::true_type
{
};

int main()
{
    static_assert( is_streamable<int, int>::value );
    static_assert( !is_streamable<int, void>::value );
    static_assert( !is_streamable<long, void*>::value );
}