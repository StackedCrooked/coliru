#include <utility>
#include <tuple>
#include <iostream>

template <int N, typename T = std::make_index_sequence<N>>
struct Q;

template <int N, std::size_t... Is>
struct Q<N, std::index_sequence<Is...>>
{
    struct X
    {
        virtual int v() = 0;
    };
    
    template <int i>
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
