#include <iostream>
#include <vector>

template <class T>
class C
{
public:
    typedef char c;
    typedef double d;

    int fun();

    static c testFun( decltype(&C::fun) ) {return c();} 
    static d testFun(...) { return d(); }
};

int main() {
    C<int>::testFun(0); // Why no ambiguity?
}