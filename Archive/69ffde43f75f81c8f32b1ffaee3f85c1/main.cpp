#include <iostream>

template <typename Out, typename In>
Out f(In x) { std::cout << "f<Out, In>(" << x << ")\n"; return x; }

template <typename T>
T f(T x) { std::cout << "f<T>(" << x << ")\n"; return x; }


int main() {
    f(42);
    f<float>(42);
}