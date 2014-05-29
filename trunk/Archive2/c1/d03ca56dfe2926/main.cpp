#include <iostream>

class U {
public:
    U() : imPrivate{ 42 } { /* */ }

    template <typename T>
    void foo(const T&) { /* DEFINICIA */ }

    int expose() { return imPrivate; }

private:
    int imPrivate;
};

namespace {
    struct HACK{

    };
}

template <>
void U::foo(const HACK&) {
    imPrivate = 666; // WTF?!
}

void hackMe()
{
    U x{};
    std::cout << x.expose() << std::endl;
    x.foo(HACK{});
    std::cout << x.expose() << std::endl;
}

int main() {
    hackMe();
}