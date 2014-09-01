#include <initializer_list>

template<int... Is> struct int_seq {};
template<int N, int... Is> struct make_int_seq : make_int_seq<N-1, N-1, Is...> {};
template<int... Is> struct make_int_seq<0, Is...> { using type = int_seq<Is...>; };

template<class Dest, class From>
auto convert_init_list(std::initializer_list<From> p, make_int_seq<100>::type)
-> std::initializer_list<Dest>
{
    throw "Maximum recursion depth exceeded";
}

template<class Dest, class From, int... Is>
constexpr auto convert_init_list(std::initializer_list<From> p, int_seq<Is...> = int_seq<>{})
-> std::initializer_list<Dest>
{
    return   sizeof...(Is) == p.size()
           ? std::initializer_list<Dest>{ *(p.begin()+Is)... }
           : convert_init_list<Dest>(p, int_seq<Is..., sizeof...(Is)>{});
}


struct A {};
struct B : A {};


void foo(std::initializer_list<A>) {}

int main()
{
    std::initializer_list<B> il = {{},{},{},{}};
    foo( convert_init_list<A>(il) );
}