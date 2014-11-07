#include <iostream>

template<typename T>
struct print;

template<typename T>
struct print<T[]> {
    static void f() {
        std::cout << "print\n";
    }
};

template<typename T>
struct print<T*> {
    static void f() {
        std::cout << "no\n";
    }
};

int main() {
    print<int[]>::f();
}