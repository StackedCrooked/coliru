#include <iostream>
using namespace std;

template <typename T>
struct X
{
    const T t;
    
    X(T t = T()):t(t) { cout << "X\n"; }
};

struct H
{
    H() { cout << "H\n"; }
    H(const H&) { cout << "H&\n"; }
    H(H&&) { cout << "H&&\n"; }
};

int main()
{
    H h;
    X<H> x0 (h);
    X<H> x1 (std::move(h));
    X<H> x2;
    X<H> x3 {H()};
    return 0;
}
