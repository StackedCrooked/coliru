#include <array>
#include <iostream>
#include <vector>
#include <tuple>

namespace detail
{
    template <template <int> class Z, typename Seq> struct tuple_Z;


    template <template <int> class Z, std::size_t ... Is> struct tuple_Z<Z, std::index_sequence<Is...>>
    {
        using type = std::tuple<Z<Is>...>;
    };

    template <typename X, std::size_t N, typename Tuple, std::size_t ... Is>
    constexpr std::array<X*, N> make_X_Array(Tuple& t, std::index_sequence<Is...>)
    {
        return {{(&std::get<Is>(t))...}};
    }

}


template<int N>
struct Q {
    struct X {
        virtual ~X() {}
        virtual int v() = 0;
    };
    template<int i>
    struct Z : X {
        virtual int v() { return i; }
    };

    Q() : Xs(detail::make_X_Array<X, N>(Zs, std::make_index_sequence<N>())) {}

    typename detail::tuple_Z<Z, typename std::make_index_sequence<N>>::type Zs;
    std::array<X*, N> Xs = detail::make_X_Array<X, N>(Zs, std::make_index_sequence<N>());
};



int main()
{
    Q<4> q;
    
    for (auto* x : q.Xs) {
        std::cout << x->v() << std::endl;   
    }
    
}
