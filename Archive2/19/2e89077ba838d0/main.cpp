#include <iostream>
#include <array>
#include <cstddef>
#include <utility>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>

typedef boost::mpl::list<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>::type types;

constexpr std::array<std::size_t, 10> offsets{0, 1, 2, 3, 5, 8, 10, 11, 16, 20};
constexpr std::array<std::size_t, 10> offset_types{0, 0, 0, 1, 2, 1, 0, 4, 3, 4};
constexpr std::array<uint8_t, 100> bytes{};

template <int N>
void op()
{
    typename boost::mpl::at_c<types, offset_types[N]>::type result
        = reinterpret_cast<typename boost::mpl::at_c<types, offset_types[N]>::type>(bytes[offsets[N]]);
}

template <std::size_t... Is>
void loop(std::index_sequence<Is...>)
{
    using ignore = int[];
    (void)ignore{ 0, (op<Is>(), 0)... };
}

int main()
{
    loop(std::make_index_sequence<offsets.size()>{});
}
