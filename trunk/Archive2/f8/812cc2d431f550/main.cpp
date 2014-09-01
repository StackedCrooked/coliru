#include <iostream>
#include <array>

template<int... Indices>
struct indices {
    typedef indices<Indices..., sizeof...(Indices)> next;
};

template<int Start>
struct build_indices {
    typedef typename build_indices<Start - 1>::type::next type;
};

template<>
struct build_indices<0> {
    typedef indices<> type;
};

template<int n>
using build_indices_t = typename build_indices<n>::type;

template<int first, int last, typename T>
struct foo_impl;

template<int first, int last, int... Is>
struct foo_impl<first, last, indices<Is...>>
{
    static constexpr std::array<int, sizeof...(Is)> array = { (Is + first)... };
};

template<int first, int last>
struct Foo : foo_impl<first, last, build_indices_t<(last + 1) - first>> { };

int main()
{
}