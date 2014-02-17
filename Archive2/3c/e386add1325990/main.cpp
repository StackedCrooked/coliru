#include <type_traits>

template<typename T, T... Seq>
class integer_sequence {
public:
    using value_type = T;
    static constexpr std::size_t size() noexcept { return sizeof...(Seq); }
};

namespace __detail_integer_sequence {
    template<typename T, typename U, typename V>
    struct merge_sequence;

    template<typename T, T... LSeq, T... RSeq>
    struct merge_sequence<T, integer_sequence<LSeq...>, integer_sequence<RSeq...>> {
        using type = integer_sequence<T, LSeq..., RSeq...>;
    };

    template<typename T, T N, T... Tail>
    struct make_integer_sequence;

    template<typename T, T... Tail>

    template<typename T, T N, T... Tail>
    struct make_integer_sequence {
        using type = typename merge_sequence<T, typename std::conditional<N, typename make_integer_sequence<T, N-1, N>::type, integer_sequence<T>>::type, integer_sequence<T, Tail...>>::type;
    };
}

#include <iostream>

int main () {
    std::cout << __detail_integer_sequence::make_integer_sequence<int, 1>::type::size();
}