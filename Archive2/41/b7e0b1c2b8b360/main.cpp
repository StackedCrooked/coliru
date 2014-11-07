#include <iostream>
#include <type_traits>

template<class T> void f(T) { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main() {
    extern int x[];
    f(x);
    return 0;
}