#include <type_traits>
#include <iostream>

template<typename T>
struct test;

template<typename T>
struct test {
    template<typename U = T, typename std::enable_if<std::is_floating_point<U>::value, int>::type = 0>
    static void print(const T& u) {
        std::cout << "float " << u << '\n';
    }
    
    template<typename U = T, typename std::enable_if<std::is_integral<U>::value, int>::type = 0>
    static void print(const T& u) {
        std::cout << "int: " << u << '\n';
    }
    
    template<typename U = T, typename std::enable_if<std::is_class<U>::value, int>::type = 0>
    static void print(const T& u) {
        std::cout << "class\n";
    }
};

struct stuff {};

template<>
struct test<stuff> {
    static void print(const stuff& t) {
        std::cout << "stuff\n";
    }
};

struct tag {};

int main() {
    test<int>::print(10);
    test<float>::print(10);
    test<stuff>::print(stuff{});
    test<tag>::print(tag{});
}