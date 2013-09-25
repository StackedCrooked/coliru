#include <cstddef>
#include <tuple>
#include <type_traits>
#include <iostream>

template<size_t... Ns>
struct indices {
    typedef indices< Ns..., sizeof...( Ns ) > next;
};

template<size_t N>
struct make_indices {
    typedef typename make_indices< N - 1 >::type::next type;
};

template<>
struct make_indices< 0 > {
    typedef indices<> type;
};

template<size_t N>
struct MyFoo {};

template< size_t N >
struct Foos {

    template<typename>
    struct Helper;

    template<size_t... Ns>
    struct Helper<indices<Ns...>> {
        typedef std::tuple< MyFoo<Ns>... > type;
    };

    typedef typename
    Helper<typename make_indices<N>::type>::type type;
};

int main()
{
    Foos<3>::type foos;
    std::cout << std::is_same<
        decltype(foos),
        std::tuple<MyFoo<0>, MyFoo<1>, MyFoo<2>> >::value;
}
