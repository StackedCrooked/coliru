#include <cstddef>
#include <tuple>

typedef std::tuple<int, char*, int, long> foo_t;

template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>> {
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>> {
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

#include <iostream>

int main() {
    std::cout << "Index<char, foo_t> = " << Index<char, foo_t>::value << std::endl;
}