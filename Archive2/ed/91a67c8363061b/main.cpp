#include <utility>
#include <tuple>

template <std::size_t... Inds>
struct index_sequence {
    static constexpr std::size_t size()
#ifdef CXX1Y
      const
#endif
    { return sizeof...(Inds); }
};

template <std::size_t N, std::size_t... Inds>
struct help_index_seq {
    typedef typename help_index_seq<N-1, N-1, Inds...>::type type;
};

template <std::size_t... Inds>
struct help_index_seq<0, Inds...> {
    typedef index_sequence<Inds...> type;
};

template <std::size_t N>
using make_index_sequence = typename help_index_seq<N>::type;

class SomeClass {
public:
    template <typename... Types>
    explicit SomeClass(Types&& ... args) {}
};

template <typename Tuple, std::size_t... Inds>
SomeClass help_make_SomeClass(Tuple&& tuple, index_sequence<Inds...>)
{
    return SomeClass(std::get<Inds>(std::forward<Tuple>(tuple))...);
}

template <typename Tuple>
SomeClass make_SomeClass(Tuple&& tuple)
{
    return help_make_SomeClass(std::forward<Tuple>(tuple),
        make_index_sequence<std::tuple_size<Tuple>::value>());
}

#include <string>

int main() {
    std::tuple<int, std::string, char> t( 1, "hi", 'x' );
    SomeClass obj = make_SomeClass(std::move(t));
}
