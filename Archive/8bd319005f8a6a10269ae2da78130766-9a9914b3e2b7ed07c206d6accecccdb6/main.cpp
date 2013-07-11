#include <tuple>
#include <type_traits>

template<unsigned i> struct Element;

template<> struct Element<0> {typedef int type;};
template<> struct Element<1> {typedef float type;};
template<> struct Element<2> {typedef double type;};

namespace detail
{
    template<int... Is>
    struct seq { };

    template<int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

    template<int... Is>
    struct gen_seq<0, Is...> : seq<Is...> { };

    template<int... Is>
    std::tuple<typename Element<Is>::type...> make_element_tuple(seq<Is...>);
}

template<int N>
using MakeElementTuple = 
    decltype(detail::make_element_tuple(detail::gen_seq<N>()));

int main()
{
    static_assert(
        std::is_same<
            MakeElementTuple<3>, 
            std::tuple<int, float, double>
        >::value, "!");
}
