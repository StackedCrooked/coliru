#include <type_traits>

namespace std
{
    template<class T, T... vals> struct integer_sequence {};
    template<class T, class N, T... vals> struct make_integer_sequence_impl;
    template<class T, T N, T... vals>
    struct make_integer_sequence_impl<T, integral_constant<T, N>, vals...>
        : make_integer_sequence_impl<T, integral_constant<T, N-1>, N-1, vals...> {};
    template<class T, T... vals> struct make_integer_sequence_impl<T, integral_constant<T, 0>, vals...>
    {
        using type = integer_sequence<T, vals...>;
    };
    
    template<class T, T N> using make_integer_sequence = typename make_integer_sequence_impl<T, integral_constant<T, N>>::type;
}

template<typename T>
constexpr T abs(T t)
{ return t < static_cast<T>(0) ? -t : t; }

template<typename Sequence>
struct match_sequence {};

template<typename Int, Int... Ns>
struct match_sequence<std::integer_sequence<Int, Ns...>> {
    template<Int Base, Int Stride = static_cast<Int>(1)>
    using Offset = std::integer_sequence<Int, Base + Stride * Ns...>;
};

template<typename Int, Int Low, Int High>
struct integer_range {
private:
    static constexpr auto width = abs(High - Low);
    using base = std::make_integer_sequence<Int, width>;
    static constexpr bool increasing = High > Low;
    static constexpr auto stride = increasing ? static_cast<Int>(1) : static_cast<Int>(-1);

public:
    using type = typename match_sequence<base>::template Offset<Low, stride>;
};

int main()
{
    integer_range<int, -2, 5> f;
}