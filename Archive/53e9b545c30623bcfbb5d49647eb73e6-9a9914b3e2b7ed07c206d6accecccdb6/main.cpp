#include <tuple>
#include <type_traits>

template<unsigned i> struct Element;

template<> struct Element<0> {typedef int type;};
template<> struct Element<1> {typedef float type;};
template<> struct Element<2> {typedef double type;};

template<unsigned... Is> struct seq{};
template<unsigned I, unsigned... Is>
struct gen_seq : gen_seq<I-1, I-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...>{ using type = seq<Is...>; };

template<unsigned N, template<unsigned> class TT,
  class Seq = typename gen_seq<N>::type>
struct tuple_over{};

template<unsigned N, template<unsigned> class TT, unsigned... Is>
struct tuple_over<N, TT, seq<Is...>>{
  using type = std::tuple<typename TT<Is>::type...>;
};

int main()
{
    static_assert(
        std::is_same<
            tuple_over<3, Element>::type,
            std::tuple<int, float, double>
        >::value, "!");
}
