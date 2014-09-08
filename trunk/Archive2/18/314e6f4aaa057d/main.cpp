#include <type_traits>

template<unsigned N, char... Args>
struct print {
#ifdef __clang__
    const int x = 1 / (sizeof...(Args) - sizeof...(Args));
#else
    enum { x = sizeof...(Args) > -1 };
#endif
};

template<bool B>
using Enable = typename std::enable_if<B, void>::type;

template<unsigned N, typename = void>
struct fizzbuzz : fizzbuzz<N - 1> {
    static constexpr auto value = print<N>{};
};

template<unsigned N>
struct fizzbuzz<N, Enable<(N % 3 == 0 && N % 5 != 0)>> : fizzbuzz<N - 1> {
    static constexpr auto value = print<N, 'f', 'i', 'z', 'z'>{};
};

template<unsigned N>
struct fizzbuzz<N, Enable<(N % 5 == 0 && N % 3 != 0)>> : fizzbuzz<N - 1> {
    static constexpr auto value = print<N, 'b', 'u', 'z', 'z'>{};
};

template<unsigned N>
struct fizzbuzz<N, Enable<(N % 5 == 0 && N % 3 == 0)>> : fizzbuzz<N - 1> {
    static constexpr auto value = print<N, 'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z'>{};
};

template<>
struct fizzbuzz<1, void> {
    static constexpr auto value = print<1>{};
};

int main() {
    fizzbuzz<20>{};
}
