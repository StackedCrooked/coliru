
#include <iostream>

namespace N {
    struct S {};
}
// Remove the alias here and comment out the namespace
// for g(S&) to be called
using S = N::S;

template<class T>
void g(T&&) {
    std::cout << "generic\n";
}

template<class T>
void f(T&& value) {
    g(value);
}

void g(S&) {
    std::cout << "overload\n";
}

signed main() {
    f(S{});
    return 0;
}
