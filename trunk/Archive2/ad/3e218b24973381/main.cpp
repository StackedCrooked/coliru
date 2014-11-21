#include <tuple>
#include <iostream>

template <std::size_t... Is>
struct index_sequence {};

template <std::size_t N, std::size_t... Is>
struct make_index_sequence_h : make_index_sequence_h<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct make_index_sequence_h<0, Is...>
{
    using type = index_sequence<Is...>;
};

template <std::size_t N>
using make_index_sequence = typename make_index_sequence_h<N>::type;

template <int N, typename T = make_index_sequence<N>>
struct Q;

template <int N, std::size_t... Is>
struct Q<N, index_sequence<Is...>>
{
    struct X
    {
        virtual int v() = 0;
    };
    
    template<int i>
    struct Z : X
    {
        virtual int v() { return i; }
    };
    
    std::tuple<Z<Is>...> z;

    X * x[N] = { &std::get<Is>(z)... };
};

int main()
{
    Q<4> q;
    std::cout << q.x[0]->v() << std::endl;
    std::cout << q.x[1]->v() << std::endl;
}
