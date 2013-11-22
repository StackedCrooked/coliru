#include <iostream>
#include <utility>
#include <functional>
#include <memory>
using namespace std;

template <typename C>
struct G
{
    const C c;
    G(const C& c):
        c(c)
    {
    }
};

template <typename C>
G<C> make_G(const C& c)
{
    return {c};
}

struct F
{
};
struct H
{
};

// HERE
G<F> make_f()
{
    return make_G(F{});
}

// AND HERE
G<H> make_h()
{
    return make_G(H{});
}

int main() {

	return 0;
}