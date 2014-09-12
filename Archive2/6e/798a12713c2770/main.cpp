#include <iostream>
    template<class...T> void foo(T&&...) {std::cout << "...T\n";}
    template<class T> void foo(T&&) {std::cout << "T\n";}
    int main() {
      foo(3);
    }
