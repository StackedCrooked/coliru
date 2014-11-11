#include <iostream>

template <class S, class C, typename = void>
struct is_streamable : ::std::false_type { };

template <class S, class C>
struct is_streamable<S,
  C,
  decltype(::std::declval<S&>() << ::std::declval<C const&>(), void())
> : ::std::true_type
{
};

struct stream
{
    void operator<<(int) {}
};

int main()
{
    static_assert(is_streamable<stream, int>::value, "!");
    static_assert(!is_streamable<stream, stream>::value, "!");
}
