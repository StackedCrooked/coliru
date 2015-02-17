#include <cstddef>
#include <cstdint>
#include <iostream>
#include <typeinfo>

namespace detail {
    template<std::size_t n> struct int_t;
    template<> struct int_t<8> { using type = std::int8_t; };
    template<> struct int_t<16> { using type = std::int16_t; };
    template<> struct int_t<32> { using type = std::int32_t; };
    template<> struct int_t<64> { using type = std::int64_t; };

    template<std::size_t n> struct uint_t;
    template<> struct uint_t<8> { using type = std::uint8_t; };
    template<> struct uint_t<16> { using type = std::uint16_t; };
    template<> struct uint_t<32> { using type = std::uint32_t; };
    template<> struct uint_t<64> { using type = std::uint64_t; };
}

template<std::size_t n>
using int_t = typename detail::int_t<n>::type;

template<std::size_t n>
using uint_t = typename detail::uint_t<n>::type;

int main() {
    std::cout << typeid(int_t<8>).name() << '\n';
    std::cout << typeid(int_t<16>).name() << '\n';
    std::cout << typeid(int_t<32>).name() << '\n';
    std::cout << typeid(int_t<64>).name() << '\n';
    std::cout << typeid(uint_t<8>).name() << '\n';
    std::cout << typeid(uint_t<16>).name() << '\n';
    std::cout << typeid(uint_t<32>).name() << '\n';
    std::cout << typeid(uint_t<64>).name() << '\n';
    return 0;
}