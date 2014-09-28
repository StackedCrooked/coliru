#include <iostream>

struct X {};

#if 1 // MEMBER_VERSION
    struct Y {
        Y(X={}) {}
        Y operator+(X) const { std::cout << __PRETTY_FUNCTION__ << "\n"; return {}; };
    };
#else
    struct Y {
        Y(X={}) {}
        friend Y operator+(Y const&, X) { std::cout << __PRETTY_FUNCTION__ << "\n"; return {}; };
    };
#endif

int main() {
    X {} + X {};
}
