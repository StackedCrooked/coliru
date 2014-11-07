#include <iostream>
#include <type_traits>

template<typename T>
void f();

template<typename T>
void f() {
    // you're some library author bob and you want to accept template types that are arrays
    static_assert(std::extent<T>::value <= 5, "...");
    static_assert(std::is_array<T>::value, "...");
    // now these assertions hold and you can make your array
    T x = { 1, 2, 3, 4, 5 };
    for(auto&& i : x) {
        std::cout << i << ' ';
    }
    std::cout << '\n' << __PRETTY_FUNCTION__ << '\n';
    // good thing the standard isn't an asshole about this
}

int main() {
    int x[4] = {};
    using y = int[];
    f<decltype(x)>();
    f<y>();
}