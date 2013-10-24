#include <assert.h>
#include <iostream>
#include <utility>

template<int>
struct get_type;

template<> struct get_type<'l'> { using type = long; };
template<> struct get_type<'i'> { using type = int; };

template<typename Literal>
constexpr auto make(Literal c) -> typename get_type<c[0]>::type
{
    return c[1];
}


template<typename T>
void print(T)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    print(make("i3"));
    print(make("l4"));
}
