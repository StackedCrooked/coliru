#include <tuple>
#include <iostream>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>

struct Foo1 {
    int foo() const { return 42; }
};

struct Foo2 {
    int bar = 0;
    int foo() { bar = 24; return bar; }
};

int main() {
    using namespace std;
    using namespace boost;

    Foo1 foo1;
    Foo2 foo2;

    fusion::for_each(tie(foo1, foo2),
        [](auto &foo) {
            cout << foo.foo() << endl;
        }
    );

    cout << "foo2.bar after mutation: " << foo2.bar << endl;
}