#include <iostream>
#include <vector>

template <int...> struct pack {};

template <int I, int... Is>
struct make_index_sequence
{
    using type = typename make_index_sequence<I-1, I-1, Is...>::type;
};

template <int... Is>
struct make_index_sequence<0, Is...> { using type = pack<Is...>; };

template <class Pack = typename make_index_sequence<3>::type>
struct X;

template <int... Is>
struct X<pack<Is...>>
{
    static void f(std::vector<int>& v)
    {
        auto l{0, (v[Is]++, 0)...};
        (void)l;
    }
};

int main()
{
    std::vector<int> v(3);
    X<>::f(v);
    for (auto i : v)
        std::cout << i << " ";
}