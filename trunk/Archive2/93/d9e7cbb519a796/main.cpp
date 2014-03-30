
#include <iostream>

template<class... P>
void g(P&&...) {
    std::cout << "generic\n";
}

namespace A {
    template<class T>
    void f(T&& value) {
        g(value);
    }
}

// Remove the alias here and comment out namespace B
// for g(E&) to be called
namespace B {
    enum class E : unsigned {};
}
using E = B::E;

void
g(E&) {
    std::cout << "B::E\n";
}

signed
main() {
    A::f(E{});
    return 0;
}
