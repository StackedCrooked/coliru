#include <array>

template<unsigned TimesEight, unsigned Remainder>
struct select_builtin_impl;

template<unsigned BitCount>
struct select_builtin;

template<unsigned N> struct builtin
{
    using type = typename select_builtin<8*N>::type;
};

template<> struct builtin<1> { using type = uint8_t ; };
template<> struct builtin<2> { using type = uint16_t; };
template<> struct builtin<4> { using type = uint32_t; };
template<> struct builtin<8> { using type = uint64_t; };

template<unsigned TimesEight, unsigned Remainder>
struct select_builtin_impl;

template<> struct select_builtin_impl<1, 0> : builtin<1> {};
template<> struct select_builtin_impl<2, 0> : builtin<2> {};
template<> struct select_builtin_impl<4, 0> : builtin<4> {};
template<> struct select_builtin_impl<8, 0> : builtin<8> {};

template<unsigned TimesEight>
struct select_builtin_impl<TimesEight, 0u>
{
    using type = std::array<uint8_t, TimesEight>;    
};

template<unsigned TimesEight, unsigned Remainder>
struct select_builtin_impl : select_builtin_impl<TimesEight + 1, 0> {};

template<unsigned BitCount>
struct select_builtin : select_builtin_impl<BitCount / 8, BitCount % 8> {};

int main()
{
    using u8 = typename builtin<1>::type;
    using mac = typename select_builtin<48>::type;
    using ip = typename select_builtin<32>::type;
    using ip6 = typename select_builtin<128>::type;
    using vlanprio = typename select_builtin<3>::type;
}