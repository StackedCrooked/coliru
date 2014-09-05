#include <iostream>
namespace A {
    class X {
        int i;
        friend void f(X x) { std::cout << x.i << '\n'; }
    public:
        X():i(101){}
    };
}

int main()
{
    A::X x;
    f(x);
}