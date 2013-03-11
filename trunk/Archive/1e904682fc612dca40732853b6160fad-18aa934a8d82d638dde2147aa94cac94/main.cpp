#include <iostream>
#include <type_traits>

template<int N, typename = void>
struct fizzbuzz {
    static void print() {
        std::cout << N << '\n';
    }
};

template<unsigned N>
struct fizzbuzz<N, typename std::enable_if<N % 3 == 0 && N % 15 != 0>::type> {
    static void print() {
        std::cout << "fizz\n";
    }
};

template<unsigned N>
struct fizzbuzz<N, typename std::enable_if<N % 5 == 0 && N % 15 != 0>::type> {
    static void print() {
        std::cout << "buzz\n";
    }
};

template<unsigned N>
struct fizzbuzz<N, typename std::enable_if<N % 15 == 0>::type> {
    static void print() {
        std::cout << "fizzbuzz\n";
    }
};

template<unsigned N, unsigned M>
struct sequence {
    static void run() {
        fizzbuzz<N>::print();
        sequence<N + 1, M>::run();
    }
};

template<unsigned M>
struct sequence<M, M> {
    static void run() {
        fizzbuzz<M>::print();
    }
};

int main() {
    sequence<1, 100>::run();
}
