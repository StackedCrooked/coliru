#include <cmath>
#include <type_traits>

#if __cplusplus >= 201103

namespace {
    template<int>
    std::true_type test();
    template<int v>
    auto constexpr_log2_test(std::nullptr_t) -> decltype(test<(std::log2(v), 0)>());
    //                                          ^adopts the return type of test
    template<int>
    auto constexpr_log2_test(...) -> std::false_type;
}

template<typename T>
struct has_constexpr_log2 : decltype(constexpr_log2_test<2>(nullptr)) {};

/*
#ifdef __clang__
    static_assert(!has_constexpr_log2<int>::value, "clang");
#else// __GNUC__
    static_assert(has_constexpr_log2<int>::value, "gcc");
#endif
*/

//uses a constexpr std::log2 if available (e.g. gcc4.7+)
template<typename T, typename = typename std::enable_if<has_constexpr_log2<T>::value>::type >
constexpr std::size_t int_log(const T & val) {
    return val == 0 ? 0 : std::log2(val);
}

//custom tail recursive constexpr log implementation
template<typename T, typename = typename std::enable_if<!has_constexpr_log2<T>::value>::type>
constexpr T int_log(const T & val, const T & base = 2, const T & res = 0) {
    return val < base ? res : int_log(val/base, base, res+1);
}

#else//no c++11

template<typename>
struct has_constexpr_log2 {
    static const bool value = false;
};

constexpr std::size_t int_log(const std::size_t val, const std::size_t base = 2, const std::size_t res = 0) {
    return val < base ? res : int_log(val/base, base, res+1);
}

#endif

#include <cstdint>

/* http://aggregate.org/MAGIC/#Log2%20of%20an%20Integer */
uint32_t ones32(uint32_t x) {
/* 32-bit recursive reduction using SWAR...
   but first step is mapping 2-bit values
   into sum of 2 1-bit values in sneaky way
*/
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return(x & 0x0000003f);
}

uint32_t log2uint32(uint32_t x) {

    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);

    return(ones32(x >> 1));
}

#if defined(__i386) || defined(_M_IX86) || defined(__x86_64__) || defined(_M_X64)

std::size_t asm_log2(const std::size_t x) {
    if (x == 0) {
        return 0;
    }
    std::size_t y;
    asm("bsr %1, %0" : "=r"(y) : "r" (x));
    return y;
}

#endif

template<typename = typename std::enable_if<sizeof(std::size_t) == 8>::type>
std::size_t gnu_asm_log2(const std::size_t x) {
    if (x == 0) {
        return 0;
    }
    return sizeof(std::size_t)*8-1 - __builtin_clzll(x);
}

std::size_t while_log2(std::size_t x) {
    std::size_t bitcount = 0;
    while (x >>= 1) {
        ++bitcount;
    }
    return bitcount;
}

std::size_t rec_bit_log2(const std::size_t x, const std::size_t bitcount = 0) {
    return x == 0 ? bitcount : rec_bit_log2(x >> 1, bitcount+1);
}

#include <chrono>
#include <functional>

std::size_t measure(std::function<void()> fkt) {
    auto start = std::chrono::high_resolution_clock::now();

    fkt();

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

void log2_test() {
    std::cout << __cplusplus << '\n';
    std::cout << std::boolalpha;
    std::cout << "has_constexpr_log2: " << has_constexpr_log2<int>::value << '\n';
    for (size_t i = 1; i < 100; ++i) {
        auto a = int_log(i);
        auto b = log2uint32(i);
        auto c = asm_log2(i);
        auto d = gnu_asm_log2(i);
        assert(a == b && a == c && a == d);
    }
    #define print(desc, func) \
        std::cout << desc;\
        for (size_t i = 0; i < 100; ++i) {\
            std::cout << static_cast<std::size_t>(func(i)) << ' ';\
        }\
        std::cout << '\n';
    print("log2uint32:   ", log2uint32);
    print("int_log:      ", int_log);
    print("asm_log2:     ", asm_log2);
    print("gnu_asm_log2: ", gnu_asm_log2);
    print("while_log2:   ", while_log2);
    print("log2:         ", std::log2);
    std::cout << std::endl;

    const int iterations = 50000000;
    std::array<std::vector<std::size_t>, 6> results;
    for (auto & vec : results) {
        vec.resize(iterations);
    }
    #define calc(desc, j, func)\
        std::cout << desc << measure([&]{\
            for (std::size_t i = 0; i < iterations; ++i) {\
                results[j][i] = static_cast<std::size_t>(func(i));\
            }\
        }) << '\n';
    calc("log2uint32:   ", 0, log2uint32);
    calc("int_log:      ", 1, int_log);
    calc("asm_log2:     ", 2, asm_log2);
    calc("gnu_asm_log2: ", 3, gnu_asm_log2);
    calc("while_log2:   ", 4, while_log2);
    calc("log2:         ", 5, std::log2);
}