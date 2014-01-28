#include <iostream>

using std::cout;
using std::endl;

template<bool C>
class X
{
public:
    X() {}
    X(const X& other) {}
    X(X&& other) {}

    template<bool C2>
        X(const X<C2>& other) { cout << "X(const X<C2>& other)" << endl; }
    template<bool C2>
        X(X<C2>&& other) { cout << "X(X<C2>&& other)" << endl; }

    template<class F>
        X(F f) { cout << "X(F f)" << endl; }
};

int main()
{
    X<true> t;
    X<false> f(std::move(t));
}
