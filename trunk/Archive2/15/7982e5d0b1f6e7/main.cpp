#include <iostream>
#include <utility>

template<class T> void test(T&& a){ std::cout << "T&&\n"; }
template<class T> void test(T& a){ std::cout << "T&\n"; }

template<class T> void foo(T&& my_t){
    test(my_t);
}

template<class T> void foo_with_forward(T&& my_t){
    test(std::forward<T>(my_t));
}

int main() {
    int x;
    std::cout << "Without std::forward";
    foo(x);
    foo(1);
    std::cout << "-----------\n";
    std::cout << "With std::forward";
    foo_with_forward(x);
    foo_with_forward(1);
}