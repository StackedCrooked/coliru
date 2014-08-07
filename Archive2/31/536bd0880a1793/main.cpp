#include <cstddef>
#include <iomanip>
#include <iostream>
#include <utility>

template<std::size_t N>
struct string_literal
{
    char data[N];
};

template<std::size_t N1, std::size_t N2, std::size_t... Ind1, std::size_t... Ind2>
constexpr auto add(string_literal<N1> lhs, string_literal<N2> rhs,
                   std::index_sequence<Ind1...>, std::index_sequence<Ind2...>)
    -> string_literal<N1+N2>
{
    return { lhs.data[Ind1]... , rhs.data[Ind2]... };
}

template<std::size_t N1, std::size_t N2>
constexpr auto operator+(string_literal<N1> lhs, string_literal<N2> rhs)
    -> string_literal<N1+N2>
{
    using Indices1 = std::make_index_sequence<N1>;
    using Indices2 = std::make_index_sequence<N2>;
    return add(lhs, rhs, Indices1(), Indices2());
}


template<char C1, char C2>
constexpr auto process()
    -> string_literal<1>
{
    return { 16 * (C1 - '0') + (C2 - '0') };
}

template<char C1, char C2, char... Rest,
         typename = std::enable_if_t< (sizeof...(Rest) > 0), void >>
constexpr auto process()
    -> string_literal<sizeof...(Rest)/2 + 1>
{
    return process<C1, C2>() + process<Rest...>();
}

template<char... Chars>
auto operator "" _hex()
    -> string_literal<sizeof...(Chars)/2>
{
    return process<Chars...>();
}

int main()
{
    auto src = 653467740035_hex;
    for (const auto &ch : src.data)
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << (unsigned)ch << '\n';
}
