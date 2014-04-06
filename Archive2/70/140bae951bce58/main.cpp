#include <iostream>

using namespace std;

struct _do { template <typename... A> _do(A&&...) { } };

template < int I >
class Foo
{
public:
    int v;
    Foo() { v = I; }
    virtual ~Foo() {}
};

template <int... I>
class Bar_impl : public Foo<I>...
{
public:
    template < int K >
    int getValue() { return Foo<K>::v; }

    template <typename F>
    void loop(F&& f) { _do{(std::forward<F>(f)(getValue<I>()), 0)...}; }
};

using Bar = Bar_impl<0,3>;

void print(int i) { std::cout << i << " "; }

int main() {
    Bar b;
    cout << b.getValue<0>() << endl; // prints 0
    cout << b.getValue<3>() << endl; // prints 3
    // cout << b.getValue<4>() << endl; // compiler error
    b.loop(print); // prints 0 3
    cout << endl;
    return 0;
}
