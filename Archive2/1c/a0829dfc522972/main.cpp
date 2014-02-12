#include <utility>

template<class T, int...> struct integer_sequence {};
template<class T, int N, int... Is> struct make_integer_sequence : make_integer_sequence<T, N-1, N-1, Is...> {};
template<class T, int... Is> struct make_integer_sequence<T, 0, Is...> : integer_sequence<T, Is...> {};

template<class T> void discard(T&&...) {}

template<int beg, class F, int... Is>
void magic(F f, integer_sequence<int, Is...>)
{
    discard( (f(std::integral_constant<int, beg+Is>{}), 0)... );
}

template<int beg, int end, class F>
auto magic(F f)
{
    return magic<beg>(f, make_integer_sequence<int, end-beg+1>{});
}

#include <iostream>
template<int N> void f() { std::cout << N << "\n"; }

int main()
{
    magic<1, 5>( [](auto x) { f<decltype(x)::value>(); } );
}